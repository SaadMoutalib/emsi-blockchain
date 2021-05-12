#include "transaction.h"

/**
 * unspent_tx_out_create - creates unspent transaction struct
 * @block_hash: hash of block containing transaction
 * @tx_id: hash of transaction in block
 * @out: address of transaction output to be copied
 *
 * Return: pointer to created unspent transaction output upon success, or NULL
 */
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out)
{
	unspent_tx_out_t *uout = calloc(1, sizeof(*uout));

	if (!uout)
		return (NULL);
	memcpy(uout->block_hash, block_hash, sizeof(uout->block_hash));
	memcpy(uout->tx_id, tx_id, sizeof(uout->tx_id));
	memcpy(&uout->out, out, sizeof(uout->out));
	return (uout);
}
