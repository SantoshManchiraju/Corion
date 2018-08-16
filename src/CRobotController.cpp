/*
 * CRobotController.cpp
 *
 *  Created on: May 22, 2017
 *      Author: krish
 */

#include <thread>

#include "CRobotController.h"

#include "config/Constants.h"
#include "config/MotionModes.h"
#include "messages/CNeoMessage.h"
#include "logger/Logger.h"

CRobotController::CRobotController() {

}

CRobotController::~CRobotController() {
	m_socket.stopCommunication();
}

void CRobotController::connect() {
//	m_socket.connectToServer(neo::HOST_ADDRESS, neo::SOCKET_PORT);
	bool result = m_socket.connectToServer("192.168.0.100", 80);
	if (result) {
		LOG_INFO("Connection to Robot successful");
	} else {
		LOG_INFO("Unable to connect");
	}
}

void CRobotController::init() {
	startSocketCommunication();
	sendCmd(neo::CMD_CONNECT_TO_PLTF);
	setMode(neo::MODE_MOTION_VEL);
}

void CRobotController::disconnect() {
	m_socket.stopCommunication();
	m_socket.disconnect();
}

void CRobotController::startSocketCommunication() {
	try {
		m_socket.startCommunication();
	} catch (std::exception& msg) {
		LOG_ERR(msg.what());
	}
}

void CRobotController::sendCmd(byte_t cmd) {
	CNeoMessage telegram(1);

	telegram.writeByte(cmd);
	m_socket.addMsgToSendQueue(telegram);
}

void CRobotController::setMode(int mode) {
	CNeoMessage telegram(5);

	stop();
	telegram.writeByte(neo::CMD_SET_MODE);
	bool status = telegram.writeInt(mode);

	std::cout << "status: " << status << std::endl;
	telegram.printProtocol();

	m_socket.addMsgToSendQueue(telegram);
}

void CRobotController::stop() {
	sendCmd(neo::CMD_STOP);
}

void CRobotController::continuee() {
	sendCmd(neo::CMD_CONTINUE);
}

void CRobotController::start() {
	sendCmd(neo::CMD_START);
}

void CRobotController::moveForward() {
	CNeoMessage telegram(9);

//	telegram.writeByte(neo::CMD_MOVE_REL);
//	telegram.writeInt(500);
//	telegram.writeInt(0);
//	telegram.writeInt(0);
	telegram.writeByte(neo::CMD_MOVE_VEL_WHEEL);
	telegram.writeInt(300);
	telegram.writeInt(300);

	m_socket.addMsgToSendQueue(telegram);
}

void CRobotController::moveBackward() {
	CNeoMessage telegram(9);
	telegram.writeByte(neo::CMD_MOVE_VEL_WHEEL);
	telegram.writeInt(-300);
	telegram.writeInt(-300);

	m_socket.addMsgToSendQueue(telegram);
}
