/*
 * CVisionController.cpp
 *
 *  Created on: Jul 26, 2017
 *      Author: bob
 */

#include <dlib/image_processing.h>
#include <dlib/opencv.h>

#include "CVisionController.h"
#include "../config/Constants.h"
#include "../logger/Logger.h"

CVisionController::CVisionController()/* :
 m_cam(CAMERA_INDEX) */{
	m_isRunning = false;
	m_pEventBuffer = NULL;
#ifndef RUNNING_ON_ECLIPSE
	m_ui = NULL;
#endif
}

CVisionController::~CVisionController() {

}

void CVisionController::runWatching() {
	cv::VideoCapture cam(CAMERA_INDEX);
	while (m_isRunning) {
		if (cam.isOpened()) {
			cv::Mat frame;
			cam >> frame; // get a new frame from camera

#ifndef RUNNING_ON_ECLIPSE
			if(m_ui != NULL) {
				m_ui->showFrame(frame);
			} else {
				Logger::ERR("GUI not connected to Vision");
			}
#endif
		} else {
			LOG_ERR("Camera Not opened");
			exit(-1);
		}
//    next: show on screen
	}
}

success_t CVisionController::startWatching() {
	if (!m_isRunning) {
		m_isRunning = true;
		m_thread = std::thread(&CVisionController::runWatching, this);

		return true;
	}
	return false;
}

success_t CVisionController::stop() {
	if (m_isRunning) {
		m_isRunning = false;
		m_thread.join();
		LOG_INFO("Vision thread closed..");
		return true;
	}
	return false;
}

void CVisionController::runTracking() {
	try {
		dlib::drectangle selectionBox;
		dlib::correlation_tracker tracker;
		cv::VideoCapture cam(CAMERA_INDEX);
		cv::Mat frame;
#ifndef RUNNING_ON_ECLIPSE
		frame = m_ui->drawingBoard()->getCurrentFrame();
		selectionBox = m_ui->drawingBoard()->getSelectionBox();
#endif
		tracker.start_track(dlib::cv_image<dlib::bgr_pixel>(frame),
				selectionBox);

		while (m_isRunning) {
			if (cam.isOpened()) {
				cam >> frame;
				tracker.update(dlib::cv_image<dlib::bgr_pixel>(frame));
#ifndef RUNNING_ON_ECLIPSE
				m_ui->showFrame(frame);
				m_ui->drawingBoard()->drawSelectionBox(tracker.get_position());
#endif
			}
		}
	} catch (std::exception& e) {
		LOG_ERR(e.what());
	}
}

success_t CVisionController::startTracking() {
	if (!m_isRunning) {
		m_isRunning = true;
		m_thread = std::thread(&CVisionController::runTracking, this);

		return true;
	}
	return false;
}

void CVisionController::pauseWatching() {
	stop();
	cv::VideoCapture cam(CAMERA_INDEX);
	cv::Mat frame;
	if (cam.isOpened())
		cam >> frame;
#ifndef RUNNING_ON_ECLIPSE
	m_ui->drawingBoard()->projectAndHold(frame);
#endif
}

void CVisionController::connectToEventBuffer(CEventBuffer* eventBuffer) {
	m_pEventBuffer = eventBuffer;
}

#ifndef RUNNING_ON_ECLIPSE
void CVisionController::connectToUI(CMainWindow* ui) {
	m_ui = ui;
}
#endif
