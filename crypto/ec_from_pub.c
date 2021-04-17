#include "hblk_crypto.h"

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key;
	const EC_GROUP *group;
	EC_POINT *pub_key;

	if (!pub)
		return (NULL);
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	group = EC_KEY_get0_group(key);
	pub_key = EC_POINT_new(group);
	if (!EC_POINT_oct2point(group, pub_key, pub, EC_PUB_LEN, NULL))
	{
		EC_KEY_free(key);
		EC_POINT_free(pub_key);
		return (NULL);
	}

	if (!EC_KEY_set_public_key(key, pub_key))
	{
		EC_KEY_free(key);
		EC_POINT_free(pub_key);
		return (NULL);
	}

	EC_POINT_free(pub_key);

	return (key);
}
