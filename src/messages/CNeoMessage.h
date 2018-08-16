/*
 * CNeoMessage.h
 *
 *  Created on: May 26, 2017
 *      Author: krish
 */

#ifndef SRC_MESSAGES_CNEOMESSAGE_H_
#define SRC_MESSAGES_CNEOMESSAGE_H_

#include "../config/Constants.h"
#include "../messages/CBuffer.h"

class CNeoMessage: public CBuffer {
private:
	void addNeoHeaderToMsg();
public:
	CNeoMessage(uint32_t size);
	virtual ~CNeoMessage();
	//

};

#endif /* SRC_MESSAGES_CNEOMESSAGE_H_ */
