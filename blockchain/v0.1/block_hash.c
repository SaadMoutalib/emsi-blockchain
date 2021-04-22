#include "blockchain.h"

/**
 * block_hash - computes the hash of a Block
 * @block: points to the Block to be hashed
 * @hash_buf: stores the resulting hash
 * Return: pointer to hash_buf
 */
uint8_t *block_hash(block_t const *block,
			uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	return (SHA256((const unsigned char *)block,
		sizeof(block), hash_buf));
}
