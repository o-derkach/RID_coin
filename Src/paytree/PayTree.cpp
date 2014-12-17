#include "PayTree.h"

Node::Node(byte *secret)
		: father(NULL), rgt_son(NULL), lft_son(NULL)
{
	sha1::calc(secret, SHA1_SIZE, &(this->hash));
	INFO("--- leaf hash --");
	INFO(this->hash);
}

Node::~Node()
{
	// TODO Auto-generated destructor stub
}

Node::Node(Node *right, Node *left)
		: father(NULL), rgt_son(right), lft_son(left)
{
	right->setFather(this);
	left->setFather(this);
	byte concat[2 * SHA1_SIZE];
	INFO(concat);
	memcpy(concat, right->hash, SHA1_SIZE);
	INFO(concat);
	memcpy((&concat + SHA1_SIZE), left->hash, SHA1_SIZE);
	INFO(concat);
	INFO(this->hash);
	sha1::calc(concat, 2 * SHA1_SIZE, &(this->hash));
	INFO(this->hash);
}

void Node::setFather(Node *father)
{
	this->father = father;
}

PayTree::PayTree(int tree_size)
	: size(tree_size)
{
	nodes = new Node[tree_size];
}

PayTree::~PayTree()
{
	// TODO Auto-generated destructor stub
}
