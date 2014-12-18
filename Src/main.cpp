#include "utils.h"
#include "RSAclass.h"
#include "PayTree.h"

int main()
{
	INFO("This is a start point of the program");

	RSAclass rsac;

	byte *from = new byte[10];
	byte *to = new byte[rsac.size()];
	byte *from1 = new byte[rsac.size()];

	RAND_bytes(from, 10);

	INFO(rsac.encrypt(10, from, to));
	INFO(rsac.decrypt(rsac.size(), to, from1));

	delete[] from;
	delete[] to;
	delete[] from1;

	Leafes l = Leafes();

	byte t1[SHA1_SIZE];
	byte t2[SHA1_SIZE];
	byte t3[SHA1_SIZE];
	byte t4[SHA1_SIZE];
	byte t5[SHA1_SIZE];
	byte t6[SHA1_SIZE];
	byte t7[SHA1_SIZE];
	byte t8[SHA1_SIZE];

	RAND_bytes(t1, SHA1_SIZE);
	RAND_bytes(t2, SHA1_SIZE);
	RAND_bytes(t3, SHA1_SIZE);
	RAND_bytes(t4, SHA1_SIZE);
	RAND_bytes(t5, SHA1_SIZE);
	RAND_bytes(t6, SHA1_SIZE);
	RAND_bytes(t7, SHA1_SIZE);
	RAND_bytes(t8, SHA1_SIZE);

	l.push_back(t1);
	l.push_back(t2);
	l.push_back(t3);
	l.push_back(t4);
	l.push_back(t5);
	l.push_back(t6);
	l.push_back(t7);
	l.push_back(t8);

	PayTree pt(l);
	return 0;
}
