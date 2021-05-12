#include "transaction.h"

/**
 * tx_in_create - allocates and initializes a transaction input structure
 * @unspent: address of unspent transaction output
 *           to be converted to a transaction input
 *
 * Return: pointer to created transaction input upon success, or NULL on fail
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *in = calloc(1, sizeof(tx_in_t));

	if (!in)
		return (NULL);
	memcpy(in->block_hash, unspent->block_hash,
	       sizeof(in->block_hash));
	memcpy(in->tx_id, unspent->tx_id, sizeof(in->tx_id));
	memcpy(in->tx_out_hash, unspent->out.hash, sizeof(in->tx_out_hash));
	return (in);
}
