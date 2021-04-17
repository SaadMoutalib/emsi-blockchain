#include "hblk_crypto.h"

/**
 * ec_save - save existing EC key pair to disk
 * @key: EC key pair to save
 * @folder: path to folder to save keys
 *
 * Return: 1 on success, 0 on error
 */
int ec_save(EC_KEY *key, char const *folder)
{
	char path[BUFSIZ];
	struct stat sb;
	FILE *f;

	if (!key || !folder)
		return (0);
	if (stat(folder, &sb))
	{
		if (mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
			return (0);
	}
	sprintf(path, "%s/%s", folder, PUB_FILENAME);
	f = fopen(path, "w");
	if (!f)
		return (0);
	if (!PEM_write_EC_PUBKEY(f, key))
	{
		fclose(f);
		return (0);
	}
	fclose(f);
	sprintf(path, "%s/%s", folder, PRI_FILENAME);
	f = fopen(path, "w");
	if (!f)
		return (0);
	if (!PEM_write_ECPrivateKey(f, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(f);
		return (0);
	}
	fclose(f);
	return (1);
}
