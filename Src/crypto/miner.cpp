#include "miner.h"

//converts hash to string
string hash_to_str(const Hash& hash)
{
    char hexstring[Hash_char_number + 1];
    sha1::toHexString(hash.x, hexstring);
    return hexstring;
}

//converts string to hash
Hash str_to_hash(const string& str)
{
    size_t str_size = str.size();
    str_size = str_size > Hash_char_number ? Hash_char_number : str_size;
    size_t str_bytes_number = str_size / 2;
    Hash hash;
    char temp[3];
    temp[2] = 0;
    unsigned int a = 0;
    for(int i = 0; i < str_bytes_number; ++i)
    {
        strncpy(temp, &str[str_size-2*(i+1)], 2);
        sscanf(temp, "%x", &a);
        hash.x[Hash_byte_number-1-i] = a;
    }

    if ((str_size % 2) == 1)
    {
        strncpy(temp, &str[0], 2);
        sscanf(temp, "%x", &a);
        hash.x[0] = a;
    }

    return hash;
}

//Calculates hash=HASH(input)
void calculate_hash(const char* const input, Hash& hash)
{
    sha1::calc(input, strlen(input), hash.x);
}

//Checks if hash has preaty format (0000000...)
//number - number of leading zeros
bool preaty_hash(const Hash& hash, unsigned int number)
{
    number = number > Hash_bit_number ? Hash_bit_number : number;

    unsigned int byte_number = number / 8;
    unsigned int bit_number = number % 8;

    for(int i = 0; i < byte_number; ++i)
        if (hash.x[i] != 0)
            return false;

    Byte mask = ~((Byte)~0 >> bit_number);

    if ((mask & hash.x[byte_number]) != 0)
        return false;

    return true;
}

//generates random string
string random_string()
{
    Hash l;
    for(int i = 0; i < Hash_byte_number; ++i)
        l.x[i] = rand();
    return hash_to_str(l);
}

Miner::Miner(string s_private) :
		h_key(str_to_hash(s_private)) {
	Block block;
	Hash h_initial = str_to_hash("fb3ced57e7764e5f9e64483827f4ba5900205f22");
	block.previous_block = h_initial;
	block_chain.emplace_back(block);
}

void Miner::Start_mining(Leafes &l) {
	size_t last = block_chain.size() - 1;
	while (l.size() != 8) {
		Block block = block_chain[last];
		string s_prev_block = hash_to_str(block.previous_block);
		string s_key = hash_to_str(h_key);
		string s_prefix = s_prev_block + s_key;
		string s_magic;
		string s_block;
		Hash h_block;
		int i = 0;
		do {
			s_magic = random_string();
			s_block = s_prefix + s_magic;
			calculate_hash(s_block.c_str(), h_block);
			++i;
		} while (!preaty_hash(h_block, 16));

		cout << i << ":\t" << hash_to_str(h_block) << endl;
		l.push_back(h_block.x);
		block.magic = str_to_hash(s_magic);

		Block new_block;
		new_block.previous_block = h_block;
		block_chain.emplace_back(new_block);
		++last;
	}
}

/*int main()
 {
 srand (time(NULL));

 char key[] = "Public Key";
 Hash h_key;
 calculate_hash(key, h_key);
 string s_key = hash_to_str(h_key);

 Miner m(s_key);

 m.Start_mining();

 return 0;
 }*/
