/*
 * CSocketClient.cpp
 *
 *  Created on: May 22, 2017
 *      Author: krish
 */

#include "CSocketClient.h"

#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

CSocketClient::CSocketClient() {
	m_socket = 0;
	m_isConnected = false;
	m_isRunning = false;
}

CSocketClient::~CSocketClient() {

}

bool CSocketClient::connectToServer(const std::string serverAddress,
		const uint16_t port) {
	struct sockaddr_in serv_addr;

	if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "Socket creation error" << endl;
		return false;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, serverAddress.c_str(), &serv_addr.sin_addr) <= 0) {
		cout << " Invalid address/ Address not supported " << endl;
		return false;
	}

	if (connect(m_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
			< 0) {
		cout << "Connection Failed " << endl;
		return false;
	}
	cout << "Connection success" << endl;
	m_isConnected = true;

	return true;
}

void CSocketClient::run() {
	while (m_isConnected and m_isRunning) {
		if (!m_sendQueue.empty()) {
			CBuffer currentMsg = m_sendQueue.front();
			send(m_socket, currentMsg.getContent(), currentMsg.getSize(), 0);
			m_sendQueue.pop();
			cout << "message sent" << endl;
			sleep(0.5);
		}

		// read part
		/*valread = read(sock, buffer, 1024);
		 printf("%s\n", buffer);*/
	}
}

void CSocketClient::addMsgToSendQueue(const CBuffer& msg) {
	m_sendQueue.push(msg);
}

void CSocketClient::startCommunication() {
	m_commThread = std::thread(&CSocketClient::run, this); //TODO: check if thread was already started
	m_isRunning = true;
}

void CSocketClient::stopCommunication() {
	// wait until all messages are sent
	while (!m_sendQueue.empty()) {
		cout<<"Waiting to close"<<endl;
	}
	m_isRunning = false;
	m_commThread.join();
}

void CSocketClient::disconnect() {
	shutdown(m_socket, SHUT_RDWR);
	m_isConnected = false;
}
