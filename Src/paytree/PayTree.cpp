#include "PayTree.h"

void Node::setSecret(byte *secret)
{
	sha1::calc(secret, SHA1_SIZE, this->hash);
}

void Node::setRL(Node *right, Node *left)
{
	rgt_son = right;
	lft_son = left;
	right->father = this;
	left->father = this;
	byte concat[2 * SHA1_SIZE];
	memcpy(concat, right->hash, SHA1_SIZE);
	memcpy(concat + SHA1_SIZE, left->hash, SHA1_SIZE);
	sha1::calc(concat, 2 * SHA1_SIZE, this->hash);
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
	}

	int j, l_size, pl_size;
	pl_size = 0;
	for (int level = height - 1; level >= 0; --level)
	{
		l_size = 1 << level;
		INFO("--- level   " << l_size);
		INFO("--- p_level " << pl_size);
		for(j = 0; j < l_size; ++j)
		{
			INFO("node =  " << i);
			INFO("left =  " << 2 * j + pl_size);
			INFO("right = " << 2 * j + 1 + pl_size);
			nodes[i].setRL(nodes + 2 * j + pl_size, nodes + 2 * j + 1 + pl_size);
			++i;
		}
		pl_size += 1 << (level + 1);
	}
	INFO("i=" << i);
	root = nodes + i-1;
}

PayTree::~PayTree()
{
	delete[] nodes;
}

byte *PayTree::getTBS()
{
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
	p.start = this->nodes + ul.next_leaf;
	p.pub = l[ul.next_leaf];
	++ul.next_leaf;
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
	p.tbs = tbs;
	return p;
}

bool verifyPath(PayPath &p, RSAclass &r)
{
	Node *s = p.start;
	Node *f = s->father;
	byte check[SHA1_SIZE];
	byte concat[2 * SHA1_SIZE];
	sha1::calc(p.pub, SHA1_SIZE, check);
	std::cout << "check 0\n";
	if (memcmp(check, p.start->hash, SHA1_SIZE) != 0)
	{
		std::cout << "first\n";
		return false;
	}
	int i = 1;
	while (s != p.end)
	{
		std::cout << "check " << i++ << "\n";
		memcpy(concat, f->rgt_son->hash, SHA1_SIZE);
		memcpy(concat + SHA1_SIZE, f->lft_son->hash, SHA1_SIZE);
		sha1::calc(concat, 2 * SHA1_SIZE, check);
		if(memcmp(check, f->hash, SHA1_SIZE) != 0)
		{
			std::cout << "second\n";
			return false;
		}
		s = f;
		f = s->father;
	}
	return (bool)r.verify(p.tbs, SHA1_SIZE + 1, p.St, SIGN_SIZE);
}
