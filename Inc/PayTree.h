#ifndef PAYTREE_H_
#define PAYTREE_H_

#include "utils.h"
#include "config.h"

class Node {
	public:
		Node();
		Node(Node *right, Node *left);
		virtual ~Node();
		void setFather(Node *father);
	private:
		Node *father;
		Node *rgt_son;
		Node *lft_son;
		byte hash[SHA1_SIZE];
};

class PayTree {
	public:
		PayTree();
		virtual ~PayTree();
	private:
		Node root;
		byte St[SIGN_SIZE];
};

#endif /* PAYTREE_H_ */
