#include "rsa_crypto.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

extern HWND hEditStatus;

// Key
void generate_keys() {
    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048);
    EVP_PKEY_keygen(ctx, &pkey);

    FILE *private_key_file = fopen("C:\\crypt\\private.pem", "wb");
    if (!private_key_file) {
        SetWindowText(hEditStatus, "Key Generation Failed (Private)!");
        return;
    }
    PEM_write_PrivateKey(private_key_file, pkey, NULL, NULL, 0, NULL, NULL);
    fclose(private_key_file);

    FILE *public_key_file = fopen("C:\\crypt\\public.pem", "wb");
    if (!public_key_file) {
        SetWindowText(hEditStatus, "Key Generation Failed (Public)!");
        return;
    }
    PEM_write_PUBKEY(public_key_file, pkey);
    fclose(public_key_file);

    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    SetWindowText(hEditStatus, "Keys Generated Successfully!");
}

void rsa_encrypt(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        SetWindowText(hEditStatus, "File Not Found!");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *text = malloc(file_size);
    fread(text, 1, file_size, file);
    fclose(file);

    // 🔹 공개 키를 사용하여 암호화
    FILE *key_file = fopen("C:\\crypt\\public.pem", "rb");

    // 🔹 공개 키 파일이 없거나 비어있으면 키 생성
    if (!key_file || fgetc(key_file) == EOF) {
        generate_keys();
        key_file = fopen("C:\\crypt\\public.pem", "rb");  // ✅ 새 키를 다시 로드
    }

    if (!key_file) {
        SetWindowText(hEditStatus, "Public Key Not Found!");
        free(text);
        return;
    }

    EVP_PKEY *pkey = PEM_read_PUBKEY(key_file, NULL, NULL, NULL);  // ✅ 공개 키 로드
    fclose(key_file);
    if (!pkey) {
        SetWindowText(hEditStatus, "Invalid Public Key!");
        free(text);
        return;
    }

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
    EVP_PKEY_encrypt_init(ctx);

    size_t enc_len;
    EVP_PKEY_encrypt(ctx, NULL, &enc_len, text, file_size);
    unsigned char *enc_data = malloc(enc_len);
    EVP_PKEY_encrypt(ctx, enc_data, &enc_len, text, file_size);

    FILE *enc_file = fopen("C:\\crypt\\encrypted.dat", "wb");
    if (!enc_file) {
        SetWindowText(hEditStatus, "File Write Error!");
        free(text);
        free(enc_data);
        EVP_PKEY_free(pkey);
        return;
    }

    fwrite(enc_data, 1, enc_len, enc_file);
    fclose(enc_file);

    free(text);
    free(enc_data);
    EVP_PKEY_free(pkey);

    SetWindowText(hEditStatus, "Encryption Success!");
}

void rsa_decrypt(const char *enc_filename, const char *key_filename) {
    FILE *key_file = fopen(key_filename, "rb");
    if (!key_file) {
        SetWindowText(hEditStatus, "Key Not Found!");
        return;
    }

    EVP_PKEY *pkey = PEM_read_PrivateKey(key_file, NULL, NULL, NULL);
    fclose(key_file);
    if (!pkey) {
        SetWindowText(hEditStatus, "Invalid Key!");
        return;
    }

    FILE *enc_file = fopen(enc_filename, "rb");
    if (!enc_file) {
        SetWindowText(hEditStatus, "Encrypted File Not Found!");
        EVP_PKEY_free(pkey);
        return;
    }

    fseek(enc_file, 0, SEEK_END);
    size_t enc_size = ftell(enc_file);
    rewind(enc_file);

    unsigned char *encrypted = malloc(enc_size);
    fread(encrypted, 1, enc_size, enc_file);
    fclose(enc_file);

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
    EVP_PKEY_decrypt_init(ctx);

    size_t dec_len;
    EVP_PKEY_decrypt(ctx, NULL, &dec_len, encrypted, enc_size);
    unsigned char *decrypted = malloc(dec_len);

    if (!decrypted) {
        SetWindowText(hEditStatus, "Memory Allocation Failed!");
        free(encrypted);
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return;
    }

    if (EVP_PKEY_decrypt(ctx, decrypted, &dec_len, encrypted, enc_size) <= 0) {
        SetWindowText(hEditStatus, "Decryption Failed!");
        free(encrypted);
        free(decrypted);
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return;
    }

    EVP_PKEY_CTX_free(ctx);
    free(encrypted);

    FILE *dec_file = fopen("C:\\crypt\\decrypted.txt", "wb");
    if (!dec_file) {
        SetWindowText(hEditStatus, "File Write Error!");
        free(decrypted);
        EVP_PKEY_free(pkey);
        return;
    }

    fwrite(decrypted, 1, dec_len, dec_file);
    fclose(dec_file);
    free(decrypted);

    EVP_PKEY_free(pkey);
    SetWindowText(hEditStatus, "Decryption Success!");
}


