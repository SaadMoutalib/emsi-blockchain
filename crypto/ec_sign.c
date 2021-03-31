#include "hblk_crypto.h"

uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg, size_t msglen, sig_t *sig){
	EC_KEY *ckey = EC_KEY_new();

	if(!key)
		return NULL;

	if(!EC_KEY_copy(ckey, key))
		return NULL;
	
	if(ECDSA_sign(0, msg, msglen, sig->sig, (unsigned int*)&sig->len, ckey)==0)
		return NULL;

	return sig->sig;

}
