#include "utils.h"
#include "RSAclass.h"

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
	return 0;
}
