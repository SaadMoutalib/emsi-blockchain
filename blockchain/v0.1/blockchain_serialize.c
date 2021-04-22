#include "blockchain.h"

/**
 * write_block - a function that writes block to file
 * @ptr: pointer to the block to be serialized
 * @idx: index of the parameter
 * @arg: The file in which the data will be written
 *
 * Return: 0 upon success, or -1 upon failure
 */
int write_block(llist_node_t ptr, unsigned int idx, void *arg)
{
	FILE *fp;
	block_t *block = ptr;

	UNUSED(idx);
	fp = (FILE *)arg;
	fwrite(&block->info, sizeof(block->info), 1, fp);
	fwrite(&block->data.len, sizeof(block->data.len), 1, fp);
	fwrite(block->data.buffer, block->data.len, 1, fp);
	fwrite(block->hash, sizeof(block->hash), 1, fp);
	return (0);
}

/**
 * blockchain_serialize - serializes a Blockchain into a file
 * @blockchain: points to the Blockchain to be serialized
 * @path: contains the path to a file to serialize the Blockchain into
 *
 * Return: return 0 upon success, or -1 upon failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *f;
	uint8_t hblk_magic[4] = "HBLK";
	uint8_t hblk_version[3] = "0.1";
	uint8_t hblk_endian = _get_endianness();
	uint32_t hblk_blocks = llist_size(blockchain->chain);

	f = fopen(path, "w");

	if (!f)
		return (-1);

	fwrite(&hblk_magic, sizeof(hblk_magic), 1, f);
	fwrite(&hblk_version, sizeof(hblk_version), 1, f);
	fwrite(&hblk_endian, sizeof(hblk_endian), 1, f);
	fwrite(&hblk_blocks, sizeof(hblk_blocks), 1, f);

	if (llist_for_each(blockchain->chain, write_block, f) == -1)
	{
		fclose(f);
		return (-1);
	}
	fclose(f);
	return (0);
}
