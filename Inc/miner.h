#ifndef MINER_H_
#define MINER_H_

#include "sha1.h"
#include "utils.h"
#include "PayTree.h"

using namespace std;

const size_t Hash_byte_number = 20;
const size_t Hash_char_number = 2*Hash_byte_number;
const size_t Hash_bit_number = 8*Hash_byte_number;

typedef unsigned char Byte;

//result of hashing
struct Hash {
     Byte x[Hash_byte_number];
};

//block in chain
struct Block {
     Hash previous_block;
     Hash miner;
     Hash magic;
};


//converts hash to string
string hash_to_str(const Hash& hash);

//converts string to hash
Hash str_to_hash(const string& str);

//Calculates hash=HASH(input)
void calculate_hash(const char* const input, Hash& hash);

//Checks if hash has preaty format (0000000...)
//number - number of leading zeros
bool preaty_hash(const Hash& hash, unsigned int number);

//generates random string
string random_string();

class Miner
{
public:
    Miner(string s_private);

    void Start_mining(Leafes &leaf);

private:
    vector<Block> block_chain;
    Hash h_key;
};


#endif /* MINER_H_ */
