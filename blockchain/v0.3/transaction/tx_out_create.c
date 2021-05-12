#include "transaction.h"

/**
 * tx_out_create - allocates and initializes a transaction output structure
 * @amount: is the amount of the transaction
 * @pub: is the public key of the transaction receiver
 *
 * Return: pointer to the created transaction output or NULL
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *out = calloc(1, sizeof(tx_out_t));

	if (!out)
		return (NULL);
	out->amount = amount;
	memcpy(out->pub, pub, EC_PUB_LEN);
	if (!sha256((void *)out, sizeof(out->amount) +
				sizeof(out->pub), out->hash))
	{
		free(out);
		return (NULL);
	}
	return (out);
}
