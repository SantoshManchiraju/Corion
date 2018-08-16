/*
 * CRobotController.h
 *
 *  Created on: May 22, 2017
 *      Author: krish
 */

#ifndef SRC_CROBOTCONTROLLER_H_
#define SRC_CROBOTCONTROLLER_H_

#include "communication/CSocketClient.h"
#include "config/NeoCommands.h"

class CRobotController {
private:
	CSocketClient m_socket;

public:
	CRobotController();
	virtual ~CRobotController();
	//
	void init();

	void connect();
	void disconnect();
	void startSocketCommunication();
	void sendCmd(byte_t cmd);
	void setMode(int mode);
	void start();
	void continuee();
	void stop();

	// movements
	void moveForward();
	void moveBackward();

};

#endif /* SRC_CROBOTCONTROLLER_H_ */
