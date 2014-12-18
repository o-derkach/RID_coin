#include "PayTree.h"

Node::Node()
	: father(NULL), rgt_son(NULL), lft_son(NULL)
{
}

Node::~Node()
{
	// TODO Auto-generated destructor stub
}

Node::setSecret(byte *secret)
{
	sha1::calc(secret, SHA1_SIZE, &(this->hash));
	INFO("--- leaf hash --");
	INFO(this->hash);
}

void Node::setRL(Node *right, Node *left)
{
	rgt_son = right;
	lft_son = left;
	right->setFather(this);
	left->setFather(this);
	byte concat[2 * SHA1_SIZE];
	INFO(concat);
	memcpy(concat, right->hash, SHA1_SIZE);
	INFO(concat);
	memcpy(concat + SHA1_SIZE, left->hash, SHA1_SIZE);
	INFO(concat);
	INFO(this->hash);
	sha1::calc(concat, 2 * SHA1_SIZE, &(this->hash));
	INFO(this->hash);
}

void Node::setFather(Node *father)
{
	this->father = father;
}

PayTree::PayTree(Leafes l)
{
	size = 2 * l.size() - 1;
	height = 1;
	while (size >> height != 1)
		++height;
	nodes = new Node[size];

	int i = 0;
	for (Leafes::iterator<byte [SHA1_SIZE]> it = l.begin(); it != l.end(); ++it)
	{
		nodes[i].setSecret(*it);
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
			nodes[i].setRL(nodes[2 * j + pl_size], nodes[2 * j + 1 + pl_size]);
			++i;
		}
		pl_size = 1 << (level + 1);
	}
	INFO("i=");
	INFO(i);
}

PayTree::~PayTree()
{
	delete[] nodes;
}
