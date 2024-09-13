
#ifndef __SM234__
#define __SM234__

#include "com.h"

#include "gmssl/sm2.h"
#include "gmssl/sm3.h"
#include "gmssl/sm4.h"

#define SM2_PUBKEY_HEAD      0x04

#define SM2_PUBKEY_X_OFS     1
#define SM2_PUBKEY_Y_OFS     33
#define SM2_PUBKEY_X_LEN     32
#define SM2_PUBKEY_Y_LEN     32
#define SM2_PUBKEY_LEN       65
#define SM2_PRIKEY_LEN       32

#define SM2_SIGN_R_OFS       0
#define SM2_SIGN_S_OFS       32
#define SM2_SIGN_R_LEN       32
#define SM2_SIGN_S_LEN       32
#define SM2_SIGN_LEN         64

#define SM2_ECC_X_LEN        32
#define SM2_ECC_Y_LEN        32
#define SM2_ECC_M_LEN        32
#define SM2_ECC_L_LEN        1
#define SM2_ECC_HEAD_LEN     96
#define SM2_ECC_BUF_LEN      255

int sm2_ecc_encrypt(uint8_t *pubkey, const uint8_t *in, size_t inlen, uint8_t *out, size_t *outlen);
int sm2_ecc_decrypt(uint8_t *prikey, const uint8_t *in, size_t inlen, uint8_t *out, size_t *outlen);

int sm2_sign_data(uint8_t *prikey, uint8_t *id, uint32_t idlen, const uint8_t *in, size_t inlen, uint8_t *out);

int sm2_sign_verify(uint8_t *pubkey, uint8_t *id, uint32_t idlen, const uint8_t *in, size_t inlen, uint8_t *sign);

#define SM4_ENCRYPT    1   
#define SM4_DECRYPT    0

void sm4_ecb_crypt(int enc, uint8_t *key, uint8_t *in, uint8_t *out, uint32_t length);
void sm4_cbc_crypt(int enc, uint8_t *key, uint8_t *iv, uint8_t *in, uint8_t *out, uint32_t len);

#endif

