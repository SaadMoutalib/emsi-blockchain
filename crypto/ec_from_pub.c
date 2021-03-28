#include "hblk_crypto.h"

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN]){
	EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);
	BIGNUM *x = BN_bin2bn(pub);
	EC_KEY_set_public_key_affine_coordinates(key, x, NULL);
	BN_free(x);
	return key;
}
