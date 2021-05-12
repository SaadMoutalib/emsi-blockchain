#include "blockchain.h"

/**
 * blockchain_destroy - deletes an existing Blockchain
 * @blockchain: points to the Blockchain structure to delete
 *
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;
	if (blockchain->unspent)
		llist_destroy(blockchain->unspent, 1, free);
	llist_destroy(blockchain->chain, 1,
		(void (*)(llist_node_t))block_destroy);
	free(blockchain);
}
