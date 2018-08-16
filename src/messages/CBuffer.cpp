/*
 * CBuffer.cpp
 *
 *  Created on: May 19, 2017
 *      Author: krish
 */

#include "../messages/CBuffer.h"

#include <cstring>
#include <iostream>
#include <bitset>
#include <iomanip>

CBuffer::CBuffer(uint32_t size) {
	m_size = size;
	m_readIndex = 0;
	m_writeIndex = 0;
	m_filled = 0;
	m_pBuffer = new byte_t[m_size];
}

CBuffer::CBuffer(const CBuffer& original) {
	m_size = original.m_size;
	m_readIndex = original.m_readIndex;
	m_writeIndex = original.m_writeIndex;
	m_filled = original.m_filled;

	m_pBuffer = new byte_t[m_size];
	for (uint32_t i = 0; i < m_size; i++) {
		m_pBuffer[i] = original.m_pBuffer[i];
	}
}

CBuffer::~CBuffer() {
	delete[] m_pBuffer;
}

bool CBuffer::writeByte(byte_t value) {
	if (m_filled < m_size) {
		// write the byte and increment the write index
		m_pBuffer[m_writeIndex++] = value;
		m_filled++;

		return true;
	} else {
		return false;
	}
}

bool CBuffer::peekByte(byte_t& retVal) {
	if (m_filled > 0) {
		retVal = m_pBuffer[m_readIndex];
		return true;
	}
	return false;
}

bool CBuffer::readByte(byte_t& retVal) {
	if (m_filled > 0) {
		retVal = m_pBuffer[m_readIndex++];
		m_filled--;

		return true;
	}
	return false;
}

bool CBuffer::writeInt(int value) {
	if ((m_filled + 3) < m_size) {
		// write the integer and increment the write index
		// Big Endian - MSB to LSB

		for (int16_t i = 3; i >= 0; i--) {
			m_pBuffer[m_writeIndex++] = (value >> (i * 8));
		}

		m_filled += 4;

		return true;
	} else {
		return false;
	}
}

bool CBuffer::peekInt(int& retVal) {

	if (m_filled >= 4) {
		retVal = 0;
		for (uint16_t i = 0; i < 4; i++) {
			retVal = retVal | (m_pBuffer[m_readIndex + i] << ((3 - i) * 8));

//			std::cout << std::bitset<32>(retVal) << std::endl;
		}

		return true;
	}
	return false;
}

bool CBuffer::readInt(int& retVal) {
	if (peekInt(retVal)) {
		m_readIndex += 4;
		m_filled -= 4;
		return true;
	}
	return false;
}

bool CBuffer::writeDouble(double value) {
	if ((m_filled + 8) < m_size) {
		// Big Endian - MSB to LSB

//		byte_t candyBytes[8];

		const byte_t* ptr = reinterpret_cast<const byte_t*>(&value);
		for (int16_t i = 7; i >= 0; i--) {
			m_pBuffer[m_writeIndex++] = ptr[i];
//			std::cout << std::bitset<8>(ptr[i]) << std::endl;
		}

		m_filled += 8;

		return true;
	}
	return false;
}

bool CBuffer::peekDouble(double& retVal) {
	if (m_filled >= 8) {
		byte_t buffer[8];
		for (unsigned int i = 0; i < 8; i++) {
			buffer[7 - i] = m_pBuffer[m_readIndex + i];
		}
		memcpy(&retVal, buffer, sizeof(double));
		return true;
	}
	return false;
}

bool CBuffer::readDouble(double& retVal) {
	if (peekDouble(retVal)) {
		m_readIndex += 8;
		m_filled -= 8;
		return true;
	}
	return false;
}

bool CBuffer::writeBoolean(bool value) {
	if (writeByte((byte_t) value))
		return true;
	return false;
}

bool CBuffer::peekBoolean(bool& retVal) {
	if (m_filled > 0) {
		retVal = m_pBuffer[m_readIndex];

		return true;
	}
	return false;
}

bool CBuffer::readBoolean(bool& retVal) {
	if (m_filled > 0) {
		retVal = m_pBuffer[m_readIndex++];
		m_filled--;

		return true;
	}
	return false;
}

uint32_t CBuffer::getSize() const {
	return m_size;
}

byte_t* CBuffer::getContent() const {
	return m_pBuffer;
}

void CBuffer::printProtocol() {
	for (uint16_t i = 0; i < m_filled; i++) {
		std::cout << "0x" << std::setw(2) << std::setfill('0') << std::hex
				<< (int) m_pBuffer[i] << " ";
	}
	std::cout << std::endl;
}
