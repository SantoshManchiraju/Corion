/*
 * CNeoMessage.cpp
 *
 *  Created on: May 26, 2017
 *      Author: krish
 */

#include "../messages/CNeoMessage.h"

CNeoMessage::CNeoMessage(uint32_t size) :
		CBuffer(size + neo::NEO_HEADER_LENGTH) {
	addNeoHeaderToMsg();
	writeInt(size);
}

CNeoMessage::~CNeoMessage() {
}

void CNeoMessage::addNeoHeaderToMsg() {
	writeByte(0xFF);
	writeByte(0x01);
	writeByte(0xFE);
	writeByte(0x02);
}
