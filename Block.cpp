/*
 * Block.cpp
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#include "Block.h"

#include <unistd.h>



void BlockPool::init(size_t _block_size) {
	instance.block_size = _block_size;
}

Block* BlockPool::take() {
	assert(block_size);
	Block* block = (Block*) malloc(block_size + sizeof(Block));
	block->refcount = 0;
	block->size = block_size;
	return block;
}

void BlockPool::give(Block* block) {
	free(block);
}


BlockPool BlockPool::instance;


Block* Block::create() {
	return Block::reference(BlockPool::instance.take());
}

Block* Block::reference(Block* block) {
	__sync_add_and_fetch(&block->refcount, 1);
	return block;
}

void Block::release(Block* block) {
	if (!__sync_add_and_fetch(&block->refcount, -1)) BlockPool::instance.give(block);
}
