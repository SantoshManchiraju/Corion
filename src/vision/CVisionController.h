/*
 * CVisionController.h
 *
 *  Created on: Jul 26, 2017
 *      Author: bob
 */

#ifndef SRC_VISION_CVISIONCONTROLLER_H_
#define SRC_VISION_CVISIONCONTROLLER_H_

// OpenCV
#include <opencv2/opencv.hpp>

#include <thread>

#include "../config/Types.h"
#include "../state_events/CEventBuffer.h"
#ifndef RUNNING_ON_ECLIPSE
#include "../ui/CMainWindow.h"
#endif
#include "../interfaces/GuiInterface.h"

class CVisionController {
private:

	// ui
#ifndef RUNNING_ON_ECLIPSE
	CMainWindow* m_ui;
#endif

	// Thread related
	std::thread m_thread;
	bool m_isRunning;

	// Event
	CEventBuffer *m_pEventBuffer;

	void runWatching();
	void runTracking();

public:
	CVisionController();
	~CVisionController();
	void pauseWatching();

	// Thread related
	success_t startWatching();
	success_t startTracking();
	success_t stop();

	void connectToEventBuffer(CEventBuffer *eventBuffer);
#ifndef RUNNING_ON_ECLIPSE
	void connectToUI(CMainWindow* ui);
#endif
};

#endif /* SRC_VISION_CVISIONCONTROLLER_H_ */
