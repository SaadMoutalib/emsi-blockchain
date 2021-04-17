#include "hblk_crypto.h"

EC_KEY *ec_create(void)
{
	C_KEY *key = EC_KEY_new_by_curve_name(EC_CURVE);

	if (!key)
	{
		return (NULL);
	}
	if (!EC_KEY_generate_key(key))
	{
		return (NULL);
	}
	return (key);
}
