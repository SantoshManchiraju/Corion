/*
 * CSocketClient.h
 *
 *  Created on: May 22, 2017
 *      Author: krish
 */

#ifndef SRC_COMMUNICATION_CSOCKETCLIENT_H_
#define SRC_COMMUNICATION_CSOCKETCLIENT_H_

#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <iostream>
#include <queue>
#include <thread>

#include "../config/Types.h"
#include "../messages/CBuffer.h"
#include "../messages/CNeoMessage.h"

/*This class is implemented as a thread*/

class CSocketClient {

private:
	int m_socket;
	bool m_isConnected;
	std::queue<CBuffer> m_sendQueue;

	// Thread related
	std::thread m_commThread;
	bool m_isRunning;

public:
	CSocketClient();
	~CSocketClient();

	bool connectToServer(const std::string serverAddress, const uint16_t port);
	void disconnect();
	void run();
	void addMsgToSendQueue(const CBuffer&);
	/*creates and  starts a new thread
	 * for socket communication*/
	void startCommunication();
	void stopCommunication();

};

#endif /* SRC_COMMUNICATION_CSOCKETCLIENT_H_ */
