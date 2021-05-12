#include "blockchain.h"

/**
 * blockchain_create - create a blockchain structure
 *
 * Return: The created blockchain structure
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain;
	block_t const _genesis = GENESIS_BLOCK;
	block_t *copy = (block_t *) malloc(sizeof(block_t));

	memcpy(copy, (block_t *) &_genesis, sizeof(block_t));
	blockchain = (blockchain_t *) malloc(sizeof(blockchain_t));
	blockchain->chain = llist_create(MT_SUPPORT_TRUE);
	blockchain->unspent = llist_create(MT_SUPPORT_TRUE);
	if (llist_add_node(blockchain->chain, copy, ADD_NODE_FRONT) != 0)
		return (NULL);
	return (blockchain);
}
