#include "Cerebrum.h"
#include "logger/Logger.h"
#include "config/MotionModes.h"
#include <time.h>
#include <unistd.h>

Cerebrum::Cerebrum(int argc, char * argv[]) :
		m_objDB("../files/testFile.txt"), m_detector(
				&m_objDB)
#ifndef RUNNING_ON_ECLIPSE
,m_uiLauncher(argc, argv)
#endif
{
	m_speech.connectToEventBuffer(&m_eventBuffer);
	m_vision.connectToEventBuffer(&m_eventBuffer);
//	m_robot.connect();
//	m_robot.startSocketCommunication();
//	m_robot.init();
#ifndef RUNNING_ON_ECLIPSE
	m_uiLauncher.start();
	m_uiLauncher.waitForInit();
	if(m_uiLauncher.ui()) {
		m_vision.connectToUI(m_uiLauncher.ui());
		m_detector.connectToUI(m_uiLauncher.ui());
		m_uiLauncher.ui()->connectToEventBuffer(&m_eventBuffer);
		m_uiLauncher.ui()->connectToDB(&m_objDB);
	}
	else
	Logger::ERR("UI is null..");
#endif

}

Cerebrum::~Cerebrum() {

}

void Cerebrum::update_object_models() {
}

void Cerebrum::respond_to_speech() {
	// get string from speech object
	// put it on gui
#ifndef RUNNING_ON_ECLIPSE
	m_uiLauncher.ui()->showSpokenText(m_speech.getRecognizedSpeech());
#endif
	if (m_speech.getRecognizedSpeech() == "move forward"
			or m_speech.getRecognizedSpeech() == "go forward") {

		/*m_robot.connect();
		m_robot.startSocketCommunication();
		m_robot.sendCmd(neo::CMD_CONNECT_TO_PLTF);
		m_robot.setMode(neo::MODE_MOTION_VEL);

		time_t endTime;
		endTime = time(NULL) + 5;
		m_robot.continuee();
		while (time(0) < endTime) {
			m_robot.moveForward();
			usleep(400000);
		}

		m_robot.stop();
		m_robot.disconnect();*/

	} else if (m_speech.getRecognizedSpeech() == "move backward"
			or m_speech.getRecognizedSpeech() == "go backward") {

		/*m_robot.connect();
		m_robot.startSocketCommunication();
		m_robot.sendCmd(neo::CMD_CONNECT_TO_PLTF);
		m_robot.setMode(neo::MODE_MOTION_VEL);

		time_t endTime;
		endTime = time(NULL) + 5;
		m_robot.continuee();
		while (time(0) < endTime) {
			m_robot.moveBackward();
			usleep(400000);
		}

		m_robot.stop();
		m_robot.disconnect();*/

	} 
}

void Cerebrum::run() {

	auto event = m_eventBuffer.getEvent();

	while (event != event::SHUT_DOWN) {
		switch (event) {

		case event::START_LISTENING:
			LOG_INFO("started listening")
			;
			m_speech.startListening();
			break;
		case event::START_WATCHING:
			m_vision.startWatching();
			break;
		case event::STOP_LISTENING:
			m_speech.stop(); // TODO: should stop wait for join? I don't think so
			break;
		case event::STOP_WATCHING:
			m_vision.stop();
			break;
		case event::PAUSE_WATCHING:
			m_vision.pauseWatching();
			m_detector.stop();
			break;
		case event::START_TRACKING:
			m_vision.startTracking();
			break;
		case event::START_LEARNING:
			m_detector.start_training();
			break;
		case event::SPEECH_RECOGNIZED:
			this->respond_to_speech();
			break;
		case event::START_DETECTION:
			m_detector.start_detection();
			break;
		}
		event = m_eventBuffer.getEvent();
	}
	LOG_INFO("Shutting down..");
	m_vision.stop();
	m_detector.stop();
	m_speech.stop();
	m_objDB.writeDBtoFile();
#ifndef RUNNING_ON_ECLIPSE
	m_uiLauncher.stop();
#endif

}

