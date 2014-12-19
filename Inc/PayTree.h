#ifndef PAYTREE_H_
#define PAYTREE_H_

#include "utils.h"
#include "config.h"
#include "sha1.h"
#include <vector>
#include "RSAclass.h"

struct Node {
		Node *father;
		Node *rgt_son;
		Node *lft_son;
		byte hash[SHA1_SIZE];

		void setRL(Node *right, Node *left);
		void setSecret(byte *secret);
};

typedef std::vector<byte *> Leafes;

typedef struct {
	Node *start;
	Node *end;
	byte *pub;
	byte *St;
	byte *tbs;
} PayPath;

typedef struct {
	int next_leaf;
	Node *start;
} UsedLeafes;

class PayTree {
	public:
		PayTree(Leafes l);
		virtual ~PayTree();
		byte *getTBS();
		void setSign(byte *sign, int size);
		PayPath getPath(UsedLeafes &ul, Leafes &l);
	private:
		Node *root;
		byte St[SIGN_SIZE];
		byte tbs[SHA1_SIZE];
		int size;
		int height;
		Node *nodes;
};

bool verifyPath(PayPath &p, RSAclass &r);

#endif /* PAYTREE_H_ */
