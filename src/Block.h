/*
 * Block.h
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "Timer.h"
#include "ConcurrentQueue.h"


struct Block {
	volatile size_t refcount;
	size_t size;
	block_time_t timestamp;
	uint8_t data[0];

	static Block* create();
	static void release(Block* block);
	static Block* reference(Block* block);
};


class BlockPool {
	friend class Block;

private:
	size_t block_size;
	BlockPool() {block_size = 0;}


	Block* take();
	void give(Block* block);

public:
	static void init(size_t _block_size);

	static BlockPool instance;
};


typedef ConcurrentQueue<Block*> ConcurrentBlockQueue;

#endif /* BLOCK_H_ */
