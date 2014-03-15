/*
 * BufferedStream.cpp
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#include "BufferedStream.h"
#include "Report.h"
#include "Block.h"

block_time_t BufferedStream::read(uint8_t* target, size_t size) {
	block_time_t last_block_time;
	while (size > 0) {
		size_t bytes = blockReader.read(target, size);
		if (!bytes) {
			Block* block = blockQueue.pop();
			if (!block) {
				Report::fatal("Processing too slow");
			}
			last_block_time = block->timestamp;
			blockReader.init(block);
			continue;
		}
		size -= bytes;
		target += bytes;
	}
	return last_block_time;
}
