#ifndef RSACLASS_H_
#define RSACLASS_H_

#include "utils.h"
#include "config.h"
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>

class RSAclass {
	public:
		RSAclass();
		virtual ~RSAclass();
		int encrypt (int size_of, byte *src, byte *dest);
		int decrypt (int size_of, byte *src, byte *dest);
		int sign (byte *tbs, uint32_t tbs_len, byte *sig, uint32_t *sig_len);
		int verify (byte *tbs, uint32_t tbs_len, byte *sig, uint32_t sig_len);
		int size();
	private:
		RSA *rsa;
};

#endif /* RSACLASS_H_ */
