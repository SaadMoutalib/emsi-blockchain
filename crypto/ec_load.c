#include "hblk_crypto.h"

EC_KEY *ec_load(char const *folder){
	char path[BUFSIZ];
	EC_KEY *key = EC_KEY_new_by_curve_name(EC_CURVE);
	
	FILE *f;
	
	if(!key || !folder)
		return NULL;
	
	sprintf(path, "%s/%s", folder, PUB_FILENAME);
	f = fopen(path, "r");

	if(!f)
		return NULL;

	if(!PEM_read_EC_PUBKEY(f, &key, NULL, NULL))
		return NULL;

	sprintf(path, "%s/%s", folder, PRI_FILENAME);
	f = fopen(path, "r");

	if(!f)
		return NULL;

	if(!PEM_read_ECPrivateKey(f, &key, NULL, NULL))
		return NULL;
	
	return key;
}
