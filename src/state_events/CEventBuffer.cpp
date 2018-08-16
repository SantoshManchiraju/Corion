/*
 * CEventHandler.cpp
 *
 *  Created on: Jul 28, 2017
 *      Author: bob
 */

#include "CEventBuffer.h"

using namespace event;

CEventBuffer::CEventBuffer() {

}

CEventBuffer::~CEventBuffer() {

}

EventType CEventBuffer::getEvent() {
	if (!m_eventBuffer.empty()) {
		EventType retval = m_eventBuffer.front();
		m_eventBuffer.pop();

		return retval;
	} else {
		return event::NONE;
	}
}

success_t CEventBuffer::setEvent(EventType event) {
	m_eventBuffer.push(event);

	return true;
}
