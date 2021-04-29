#include "blockchain.h"

/**
 * hash_matches_difficulty - checks if a given hash matches a given difficulty
 * @hash: is the hash to check
 * @difficulty: is the minimum difficulty the hash should match
 *
 * Return: return 1 if difficulty is respected, or 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
				uint32_t difficulty)
{
	int i;
	uint8_t *iter = (uint8_t *)hash;
	uint8_t *hash_end = (uint8_t *)hash + SHA256_DIGEST_LENGTH;
	uint32_t diff = 0;

	if (!hash)
		return (0);

	while (iter < hash_end)
	{
		for (i = 7; i >= 0; i--)
			if ((*iter >> i) & 0)
				diff++;
			break;
		iter++;
	}

	if (diff >= difficulty)
		return (1);

	return (0);
}
