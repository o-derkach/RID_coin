#include "utils.h"
#include "RSAclass.h"
#include "PayTree.h"
#include "miner.h"

int main()
{
	INFO("This is a start point of the program");

	RSAclass rsac;

	/*byte *from = new byte[10];
	byte *to = new byte[rsac.size()];
	byte *from1 = new byte[rsac.size()];

	RAND_bytes(from, 10);

	INFO(rsac.encrypt(10, from, to));
	INFO(rsac.decrypt(rsac.size(), to, from1));

	delete[] from;
	delete[] to;
	delete[] from1;
*/
	Leafes l = Leafes();

    char key[] = "Public Key";
    Hash h_key;
    calculate_hash(key, h_key);
    string s_key = hash_to_str(h_key);

    Miner m(s_key);

    m.Start_mining(l);

    PayTree pt(l);

    byte *to = new byte[rsac.size()];
    uint32_t sign_size;
    int res = rsac.sign(pt.getTBS(), SHA1_SIZE + 1, to, &sign_size);
    if (res == 0)
    {
    	std::cout << "FAIL!!\n";
    	return -1;
    }

    pt.setSign(to, sign_size);
    delete[] to;

    UsedLeafes ul;
    ul.next_leaf = 0;
    ul.start = NULL;
	PayPath p = pt.getPath(ul, l);
    if (!verifyPath(p, rsac))
    {
    	std::cout << "FAIL!!\n";
    }

	PayPath p1 = pt.getPath(ul, l);
	if (!verifyPath(p1, rsac))
	{
		std::cout << "FAIL!!\n";
	}

	PayPath p2 = pt.getPath(ul, l);
	if (!verifyPath(p2, rsac))
	{
		std::cout << "FAIL!!\n";
	}

    for (int i = 0; i < l.size(); ++i)
    {
    	delete[] l[i];
    }

	return 0;
}
