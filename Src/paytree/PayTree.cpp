#include "PayTree.h"

Node::~Node()
{
	// TODO Auto-generated destructor stub
}

Node::Node(Node *right, Node *left)
	: father(NULL), rgt_son(right), lft_son(left)
{
	right->setFather(this);
	left->setFather(this);
	//TODO: generating hash of sons
}

void Node::setFather(Node *father)
{
	this->father = father;
}

PayTree::PayTree()
{
	// TODO Auto-generated constructor stub
}

PayTree::~PayTree()
{
	// TODO Auto-generated destructor stub
}
