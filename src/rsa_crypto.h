#ifndef RSA_CRYPTO_H
#define RSA_CRYPTO_H

// rsa_crypto.h : ¾ÏÈ£È­ & º¹È£È­ ÇÔ¼ö Á¤ÀÇ

void rsa_encrypt(const char *filename);
void rsa_decrypt(const char *enc_filename, const char *key_filename);
void generate_keys();

#endif // RSA_CRYPTO_H

