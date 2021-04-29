#include "hblk_crypto.h"

/**
 * ec_sign - sign a set of bytes, using given private EC_KEY
 * @key: pointer to EC_KEY struct containing private key to perform the signing
 * @msg: pointer to characters to be signed
 * @msglen: len of msg
 * @sig: address to store signature
 *
 * Return: pointer to signature buffer on success, NULL on error
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,	size_t msglen,
		sig_t *sig)
{
	EC_KEY *ckey = EC_KEY_new();
	unsigned char hash[SHA256_DIGEST_LENGTH];

	if (!key || !msg || !sig)
		return (NULL);
	if (!EC_KEY_check_key(key))
		return (NULL);
	if (!SHA256(msg, msglen, hash))
		return (NULL);
	sig->len = ECDSA_size(key);
	if (!sig->len)
		return (NULL);
	if (!EC_KEY_copy(ckey, key))
		return (NULL);
	if (!ECDSA_sign(0, hash, SHA256_DIGEST_LENGTH, sig->sig,
				(unsigned int *)&(sig->len), ckey))
		return (NULL);
	EC_KEY_free(ckey);
	return (sig->sig);
}
