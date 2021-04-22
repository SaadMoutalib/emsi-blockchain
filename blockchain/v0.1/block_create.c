#include "blockchain.h"

/**
 * block_create - creates a Block structure and initializes it
 * @prev: is a pointer to the previous Block in the Blockchain
 * @data: points to a memory area to duplicate in the Blocks data
 * @data_len: stores the number of bytes to duplicate in data
 *
 * Return: pointer to the allocated Block
 */
block_t *block_create(block_t const *prev, int8_t const *data,
			uint32_t data_len)
{
	block_t *block;
	uint32_t len;
	time_t t = time(0);

	if (!prev || !data || !data_len)
		return (NULL);

	len = data_len > BLOCKCHAIN_DATA_MAX ?
		BLOCKCHAIN_DATA_MAX : data_len;

	block  = (block_t *)malloc(sizeof(block_t));
	block->info.index = prev->info.index + 1;
	block->info.difficulty = 0;
	block->info.timestamp = (uint64_t)&t;
	block->info.nonce = 0;
	memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	memcpy(block->data.buffer, data, len);
	block->data.len = len;
	memset(block->hash, 0, SHA256_DIGEST_LENGTH);

	return (block);
}
