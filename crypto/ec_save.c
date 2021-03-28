#include "hblk_crypto.h"

int ec_save(EC_KEY *key, char const *folder){
	EVP_PKEY *pkey = EVP_PKEY_new(); 
	char path[BUFSIZ];
	
	int dir_err = -1;
	
	struct stat sb;
	FILE *f;
	
	if(stat(folder, &sb))
	{
		dir_err = mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
		
		if(dir_err == -1)
		{
			EVP_PKEY_free(pkey);
			return 0;
		}
	}
	
	
 	if(!EVP_PKEY_assign_EC_KEY(pkey, key))
	{
		EVP_PKEY_free(pkey);
		return 0;
	}
	
	sprintf(path, "%s/%s", folder, PUB_FILENAME);
	f = fopen(path, "w");

	if(!f)
	{
		EVP_PKEY_free(pkey);
		return 0;
	}

	if(!PEM_write_PUBKEY(f, pkey))
	{
		fclose(f);
		EVP_PKEY_free(pkey);
		return 0;
	}
	
	fclose(f);
	
	sprintf(path, "%s/%s", folder, PRI_FILENAME);
	
	f = fopen(path, "w");
	
	if(!f)
	{
		EVP_PKEY_free(pkey);
		return 0;
	}


	if(!PEM_write_PrivateKey(f, pkey, NULL, NULL, 0, 0, NULL))
	{
		fclose(f);
		EVP_PKEY_free(pkey);
		return 0;
	}
	
	EVP_PKEY_free(pkey);
	fclose(f);
	return 1;

}
