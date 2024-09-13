

#include <stdio.h>

#include "sm234.h"

#define TAG "sm234"

void sm4_cbc_crypt(int enc, uint8_t *key, uint8_t *iv, uint8_t *in, uint8_t *out, uint32_t len)
{
	SM4_KEY sm4_key;
	memset(&sm4_key, 0, sizeof(SM4_KEY));
	if(enc == SM4_ENCRYPT){
		sm4_set_encrypt_key(&sm4_key, key);
		sm4_cbc_encrypt(&sm4_key, iv, in, len/SM4_BLOCK_SIZE, out);
	}
	else{
		sm4_set_decrypt_key(&sm4_key, key);
		sm4_cbc_decrypt(&sm4_key, iv, in, len/SM4_BLOCK_SIZE, out);
	}
}

void sm4_ecb_crypt(int enc, uint8_t *key, uint8_t *in, uint8_t *out, uint32_t len)
{
	int length = len;
	SM4_KEY sm4_key;
	memset(&sm4_key,0,sizeof(SM4_KEY));
	if(enc == SM4_ENCRYPT){
		sm4_set_encrypt_key(&sm4_key, key);
		while (length >= SM4_BLOCK_SIZE) {
			sm4_encrypt(&sm4_key, in, out);
			length -= SM4_BLOCK_SIZE;
			in += SM4_BLOCK_SIZE;
			out += SM4_BLOCK_SIZE;
		}
	}
	else{
		sm4_set_decrypt_key(&sm4_key, key);
		while (len >= SM4_BLOCK_SIZE) {
			sm4_decrypt(&sm4_key, in, out);
			len -= SM4_BLOCK_SIZE;
			in += SM4_BLOCK_SIZE;
			out += SM4_BLOCK_SIZE;
		}
	}
}

int format_print(FILE *fp, int format, int indent, const char *str, ...)
{
    return 0;
}

int format_bytes(FILE *fp, int format, int indent, const char *str, const uint8_t *data, size_t datalen)
{
    return 0;
}
