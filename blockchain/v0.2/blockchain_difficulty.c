#include "blockchain.h"

/**
 * blockchain_difficulty - computes the difficulty to assign to the next Block
 * @blockchain: points to the Blockchain to analyze
 *
 * Return: the difficulty to be assigned
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *last_block, *last_adjusted_block;
	time_t exp_elapsed_time, act_elapsed_time;

	if (!blockchain)
		return (0);

	last_block = llist_get_tail(blockchain->chain);

	if (last_block->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL == 0 &&
		last_block->info.index != 0)
	{
		last_adjusted_block = llist_get_node_at(blockchain->chain,
			llist_size(blockchain->chain) - DIFFICULTY_ADJUSTMENT_INTERVAL);
		exp_elapsed_time = BLOCK_GENERATION_INTERVAL *
					DIFFICULTY_ADJUSTMENT_INTERVAL;
		act_elapsed_time = last_block->info.timestamp -
					last_adjusted_block->info.timestamp;
		if (act_elapsed_time < exp_elapsed_time / 2)
			return (last_block->info.difficulty + 1);
		else if (act_elapsed_time > exp_elapsed_time * 2)
			return (last_block->info.difficulty--);
	}
	return (last_block->info.difficulty);
}
