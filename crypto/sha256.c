#include "hblk_crypto.h"
#include <openssl/sha.h>

uint8_t *sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH]){
	SHA256_CTX context;
	
	if(!digest)
		return NULL;
	
	SHA256_Init(&context);
	SHA256_Update(&context, s, len);
	SHA256_Final(digest ,&context);
	
	return digest;
}
