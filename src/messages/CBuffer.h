/*
 * CBuffer.h
 *
 *  Created on: May 19, 2017
 *      Author: krish
 */

#ifndef SRC_MESSAGES_CBUFFER_H_
#define SRC_MESSAGES_CBUFFER_H_

#include "../config/Types.h"

class CBuffer {
private:
	byte_t* m_pBuffer;
	uint32_t m_size;
	uint32_t m_filled;
	uint32_t m_readIndex;
	uint32_t m_writeIndex;
public:
	CBuffer(uint32_t size);
	CBuffer(const CBuffer& original);
	virtual ~CBuffer();
	// byte
	bool writeByte(byte_t);
	bool peekByte(byte_t &);
	bool readByte(byte_t &);
	// int
	bool writeInt(int);
	bool peekInt(int&);
	bool readInt(int&);
	// double
	bool writeDouble(double);
	bool peekDouble(double&);
	bool readDouble(double&);
	// bool
	bool writeBoolean(bool);
	bool peekBoolean(bool&);
	bool readBoolean(bool&);

	uint32_t getSize() const;
	byte_t* getContent() const;

	void printProtocol();
};

#endif /* SRC_MESSAGES_CBUFFER_H_ */
