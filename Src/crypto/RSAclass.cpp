#include "RSAclass.h"

RSAclass::RSAclass()
{
	//http://www.codepool.biz/tech-frontier/how-to-use-openssl-generate-rsa-keys-cc.html
	rsa = RSA_new();
	BIGNUM *bne = NULL;
	//BIO *bp_public = NULL, *bp_private = NULL;

	// 1. generate rsa key
	bne = BN_new();
	BN_set_word(bne, RSA_F4);

	RSA_generate_key_ex(rsa, RSA_SIZE, bne, NULL);

	/*
	 // 2. save public key
	 bp_public = BIO_new_file("public.pem", "w+");
	 PEM_write_bio_RSAPublicKey(bp_public, r);
	  
	 // 3. save private key
	 bp_private = BIO_new_file("private.pem", "w+");
	 ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);
	 BIO_free_all(bp_public);
	 BIO_free_all(bp_private);
	 */
	BN_free(bne);
}

RSAclass::~RSAclass()
{
	RSA_free(rsa);
}

//returns the size of the encrypted data
int RSAclass::encrypt(int size_of, byte *src, byte *dest)
{
	return RSA_public_encrypt(size_of, src, dest, rsa, RSA_PKCS1_OAEP_PADDING);
}

//returns the size of the recovered plaintext.
int RSAclass::decrypt(int size_of, byte *src, byte *dest)
{
	return RSA_private_decrypt(size_of, src, dest, rsa, RSA_PKCS1_OAEP_PADDING);
}

//returns 1 on success, 0 otherwise
int RSAclass::sign(byte *tbs, uint32_t tbs_len, byte *sig, uint32_t *sig_len)
{
	int dummy = 0;
	return RSA_sign_ASN1_OCTET_STRING(dummy, tbs, tbs_len, sig, sig_len, rsa);
}

//returns 1 on success, 0 otherwise
int RSAclass::verify(byte *tbs, uint32_t tbs_len, byte *sig, uint32_t sig_len)
{
	int dummy = 0;
	return RSA_verify_ASN1_OCTET_STRING(dummy, tbs, tbs_len, sig, sig_len, rsa);
}

//returns size of module in bytes. it may be size of the future encription result
int RSAclass::size()
{
	return RSA_size(rsa);
}
