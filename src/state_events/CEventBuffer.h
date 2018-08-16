/*
 * CEventHandler.h
 *
 *  Created on: Jul 28, 2017
 *      Author: bob
 */

#ifndef SRC_STATE_EVENTS_CEVENTBUFFER_H_
#define SRC_STATE_EVENTS_CEVENTBUFFER_H_

#include <queue>

#include "EventTypes.h"
#include "../config/Types.h"

class CEventBuffer {

private:
	std::queue<event::EventType> m_eventBuffer;
public:
	success_t setEvent(event::EventType event);
	event::EventType getEvent();
	CEventBuffer();
	~CEventBuffer();
};

#endif /* SRC_STATE_EVENTS_CEVENTBUFFER_H_ */
