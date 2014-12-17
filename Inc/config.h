/*
 * Header for different configuration parameters of the system
 */
#ifndef CONFIG_H_
#define CONFIG_H_

#include "utils.h"
#define SHA1_SIZE 20

#define SIGN_SIZE 100500

#define PAYTREE_HEIGHT 100
#define PAYTREE_SIZE 2 << (PAYTREE_HEIGHT + 1)
#define LEAF_SIZE 2 << PAYTREE_HEIGHT

#define RSA_SIZE 1024

#endif /* CONFIG_H_ */
