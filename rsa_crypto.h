#ifndef RSA_CRYPTO_H
#define RSA_CRYPTO_H

// rsa_crypto.h : ��ȣȭ & ��ȣȭ �Լ� ����

void rsa_encrypt(const char *filename);
void rsa_decrypt(const char *enc_filename, const char *key_filename);
void generate_keys();

#endif // RSA_CRYPTO_H

