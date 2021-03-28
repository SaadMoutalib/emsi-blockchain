#include "hblk_crypto.h"

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]){
	const EC_POINT* point = EC_KEY_get0_public_key(key);
	const EC_GROUP* group = EC_KEY_get0_group(key);
		
	BIGNUM *x = BN_new();	
	BIGNUM *y = BN_new();

	if(!group || !point)
		return NULL;	
	
	if (EC_POINT_get_affine_coordinates_GFp(group, point, x, y, NULL)) {
		BN_bn2bin(x, pub);
	}else{
		return NULL;
	}
	
	BN_free(x);
	BN_free(y);
	
	return pub;
}
