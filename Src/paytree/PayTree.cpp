#include "PayTree.h"

void Node::setSecret(byte *secret)
{
	sha1::calc(secret, SHA1_SIZE, this->hash);
}

void Node::setRL(Node *right, Node *left)
{
	rgt_son = right;
	lft_son = left;
	right->setFather(this);
	left->setFather(this);
	byte concat[2 * SHA1_SIZE];
	memcpy(concat, right->hash, SHA1_SIZE);
	memcpy(concat + SHA1_SIZE, left->hash, SHA1_SIZE);
	sha1::calc(concat, 2 * SHA1_SIZE, this->hash);
}

void Node::setFather(Node *father)
{
	this->father = father;
}

byte * Node::getPublic()
{
	return this->hash;
}

PayTree::PayTree(Leafes l)
{
	size = 2 * l.size() - 1;
	height = 1;
	while (size >> height != 1)
		++height;
	INFO(height);
	INFO(size);
	nodes = new Node[size];

	int i = 0;
	for (i = 0; i < l.size(); ++i)
	{
		nodes[i].setSecret(l[i]);
		++i;
	}

	int j, l_size, pl_size;
	pl_size = 0;
	for (int level = height - 1; level >= 0; --level)
	{
		l_size = 1 << level;
		INFO("--- level ");
		INFO(l_size);
		INFO("--- p_level ");
		INFO(pl_size);
		for(j = 0; j < l_size; ++j)
		{
			INFO("node = ");
			INFO(i);
			INFO("left = ");
			INFO(2 * j + pl_size);
			INFO("right = ");
			INFO(2 * j + 1 + pl_size);
			nodes[i].setRL(&nodes[2 * j + pl_size], &nodes[2 * j + 1 + pl_size]);
			++i;
		}
		pl_size += 1 << (level + 1);
	}
	INFO("i=");
	INFO(i);
	root = &nodes[i-1];
}

PayTree::~PayTree()
{
	delete[] nodes;
}

byte *PayTree::getTBS()
{
	byte *tbs = new byte[SHA1_SIZE + 1];
	memcpy(tbs, root->getPublic(), SHA1_SIZE);
	tbs[SHA1_SIZE] = (byte)(height & 0xFF);
	return tbs;
}

void PayTree::setSign(byte *sign, int size)
{
	memcpy(St, sign, size);
}

PayPath PayTree::getPath(UsedLeafes &ul, Leafes &l)
{
	PayPath p;
	p.St = this->St;
	p.start = &this->nodes[ul.next_leaf];
	p.pub = l[ul.next_leaf];
	if (ul.start == NULL)
	{
		p.end = this->root;
		ul.start = p.start;
	}
	else
	{
		Node *ul_n, *p_n;
		ul_n = ul.start;
		p_n = p.start;
		while (ul_n->father != p_n->father)
		{
			ul_n = ul_n->father;
			p_n = p_n->father;
		}
		p.end = p_n;
	}
	p.tbs = this->getTBS();
	return p;
}

bool verifyPath(PayPath &p, RSAclass &r)
{
	Node *s = p.start;
	Node *f = s->father;
	byte check[SHA1_SIZE];
	byte concat[2 * SHA1_SIZE];
	sha1::calc(p.pub, SHA1_SIZE, check);
	if (memcmp(check, p.start->hash, SHA1_SIZE) != 0)
	{
		delete[] p.tbs;
		return false;
	}
	while (s != p.end)
	{
		memcpy(concat, f->rgt_son->hash, SHA1_SIZE);
		memcpy(concat + SHA1_SIZE, f->lft_son->hash, SHA1_SIZE);
		sha1::calc(concat, 2 * SHA1_SIZE, check);
		if(memcmp(check, f->hash, SHA1_SIZE) != 0)
		{
			delete[] p.tbs;
			return false;
		}
		s = f;
		f = s->father;
	}
	int v = r.verify(p.tbs, SHA1_SIZE + 1, p.St, 128);
	delete[] p.tbs;
	return v;
}
