#ifndef PAYTREE_H_
#define PAYTREE_H_

#include "utils.h"
#include "config.h"
#include "sha1.h"
#include <list>

class Node {
	public:
		Node();
		//Node(byte *secret);
		//Node(Node *right, Node *left);
		virtual ~Node();
		void setFather(Node *father);
		void setRL(Node *right, Node *left);
		void setSecret(byte *secret);
	private:
		Node *father;
		Node *rgt_son;
		Node *lft_son;
		byte hash[SHA1_SIZE];
};

typedef std::list<byte *> Leafes;

class PayTree {
	public:
		PayTree(Leafes l);
		virtual ~PayTree();
	private:
		Node root;
		byte *St;
		int size;
		int height;
		Node *nodes;
};

#endif /* PAYTREE_H_ */
