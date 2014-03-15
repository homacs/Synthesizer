/*
 * BufferedStream.h
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#ifndef BUFFEREDSTREAM_H_
#define BUFFEREDSTREAM_H_


#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "Block.h"

class BlockReader {
	Block* block;
	uint8_t* iterator;
	uint8_t* end;

public:
	BlockReader() {
		iterator = end = NULL;
		block = NULL;
	}
	void init(Block* _block) {
		if (block) Block::release(block);

		block = _block;
		iterator = block->data;
		end = iterator + block->size;
	}

	size_t read(uint8_t* target, size_t size) {
		size_t bytes = end - iterator;
		if (bytes > size) bytes = size;

		memcpy(target, iterator, bytes);
		iterator += bytes;
		return bytes;
	}

};
class BufferedStream {
	BlockReader blockReader;
	ConcurrentBlockQueue blockQueue;
public:
	BufferedStream(size_t capacity) : blockQueue(capacity){}
	block_time_t read(uint8_t* target, size_t size);
	size_t size() { return blockQueue.size(); }
	ConcurrentBlockQueue* getInput() { return &blockQueue; }
};

#endif /* BUFFEREDSTREAM_H_ */
