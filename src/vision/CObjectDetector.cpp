/*
 * CObjectTrainer.cpp
 *
 *  Created on: Sep 9, 2017
 *      Author: bob
 */

#include <map>
#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>

#include "CObjectDetector.h"
#include "../logger/Logger.h"
#include "../config/Constants.h"

using namespace dlib;

CObjectDetector::CObjectDetector(CObjectDatabase* db) {
	m_c = 1;
	m_eps = 0.01;
	m_num_folds = 3;
	m_maxThreads = 4;
	m_target_size = 80 * 80;
	m_pObjectDB = db;
	m_isActive = false;
	loadDetectors();
}

CObjectDetector::~CObjectDetector() {
}

void CObjectDetector::pick_best_window_size(
		const std::vector<std::vector<dlib::rectangle> >& boxes,
		unsigned long & width, unsigned long & height,
		const unsigned long target_size) {
	// find the average width and height
	running_stats<double> avg_width, avg_height;
	for (unsigned long i = 0; i < boxes.size(); ++i) {
		for (unsigned long j = 0; j < boxes[i].size(); ++j) {
			avg_width.add(boxes[i][j].width());
			avg_height.add(boxes[i][j].height());
		}
	}

	// now adjust the box size so that it is about target_pixels pixels in size
	double size = avg_width.mean() * avg_height.mean();
	double scale = std::sqrt(target_size / size);

	width = (unsigned long) (avg_width.mean() * scale + 0.5);
	height = (unsigned long) (avg_height.mean() * scale + 0.5);
	// make sure the width and height never round to zero.
	if (width == 0)
		width = 1;
	if (height == 0)
		height = 1;
}

bool CObjectDetector::contains_any_boxes(
		const std::vector<std::vector<dlib::rectangle> >& boxes) {
	for (unsigned long i = 0; i < boxes.size(); ++i) {
		if (boxes[i].size() != 0)
			return true;
	}
	return false;
}

void CObjectDetector::train(std::string input_file, std::string object_name,
		std::string output_dir) {
	LOG_DEBUG("Training " + object_name);

	try {
		typedef scan_fhog_pyramid<pyramid_down<6> > image_scanner_t;
		// Get the upsample option from the user but use 0 if it wasn't given.
		const unsigned long upsample_amount = 0;

		dlib::array<array2d<unsigned char> > images;
		std::vector<std::vector<rectangle> > object_locations, ignore;

		LOG_INFO("Loading image dataset from metadata file " + input_file);
		ignore = load_image_dataset(images, object_locations, input_file);
		std::stringstream log_temp;
		log_temp << "Number of images loaded: " << images.size() << std::endl;
		LOG_INFO(log_temp.str());
		log_temp.clear();

		if (m_num_folds > images.size())
			m_num_folds = images.size();

		// Upsample images
		for (unsigned long i = 0; i < upsample_amount; ++i)
			upsample_image_dataset<pyramid_down<2>>(images, object_locations,
					ignore);

		image_scanner_t scanner;
		unsigned long width, height;
		pick_best_window_size(object_locations, width, height, m_target_size);
		scanner.set_detection_window_size(width, height);

		structural_object_detection_trainer<image_scanner_t> trainer(scanner);
		trainer.set_num_threads(m_maxThreads);

		trainer.be_verbose();
		trainer.set_c(m_c);
		trainer.set_epsilon(m_eps);

		std::vector<std::vector<rectangle> > removed;
		removed = remove_unobtainable_rectangles(trainer, images,
				object_locations);

		// if we weren't able to get all the boxes to match then throw an error
		if (contains_any_boxes(removed)) {
			unsigned long scale = upsample_amount + 1;
			scale = scale * scale;
			//        throw_invalid_box_error_message(parser[0], removed, target_size/scale);
			LOG_ERR(object_name + " Training failed")
		}

		add_image_left_right_flips(images, object_locations, ignore);
		object_detector<image_scanner_t> detector = trainer.train(images,
				object_locations, ignore);

		LOG_INFO("Saving trained detector to " + object_name + ".svm");

		m_detectors[object_name] = detector;
		serialize(output_dir + object_name + ".svm") << detector;

		LOG_INFO("Testing detector on training data...");

		log_temp << "Test detector (precision,recall,AP): "
				<< dlib::test_object_detection_function(detector, images,
						object_locations, ignore) << std::endl;

		LOG_INFO(log_temp.str());

		image_window hogwin(draw_fhog(detector), "Learned fHOG detector");
		hogwin.show();
	} catch (std::exception& e) {
		LOG_ERR(e.what());
	}
}

void CObjectDetector::connectToObjDB(CObjectDatabase* db) {
	m_pObjectDB = db;
}

void CObjectDetector::run_training() {
	if (m_pObjectDB != NULL) {

		for (auto& obj_data : m_pObjectDB->getData()) {
			if (!obj_data.isUpToDate) {
				this->train(OBJECTS_DIR + obj_data.name + "/details.xml",
						obj_data.name, DETECTORS_DIR);
				m_pObjectDB->setUpToDateStatus(obj_data.name, true);
#ifndef RUNNING_ON_ECLIPSE
				m_ui->showToastMsg(obj_data.name + " training finished");
#endif
			}
		}
		m_pObjectDB->writeDBtoFile();
		m_isActive = false;
		m_thread.detach();
		LOG_DEBUG("Training complete");
#ifndef RUNNING_ON_ECLIPSE
		m_ui->showToastMsg("All models trained and ready for detection");
#endif
	} else {
		LOG_ERR("Object Database not connected");
	}
}

void CObjectDetector::run_continuous_detection() {
	cv::VideoCapture cam(CAMERA_INDEX);
	cam.set(CV_CAP_PROP_BUFFERSIZE, 3);

	while (m_isActive) {
		if (cam.isOpened()) {
			cv::Mat frame;
			cam >> frame;
			for (auto& current_detector : m_detectors) {
				// run detection on the frame
				std::vector<rectangle> rects = current_detector.second(
						dlib::cv_image<dlib::bgr_pixel>(frame));
				// if found draw a box and print the name
				if (rects.size() != 0)
					LOG_INFO(current_detector.first + " detected");
				for (auto temp_rect : rects) {
					cv::putText(frame, current_detector.first,
							cv::Point(temp_rect.left(), temp_rect.top() - 5),
							cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(0, 255, 0),
							1.0);
					cv::rectangle(frame,
							cv::Point(temp_rect.left(), temp_rect.top()),
							cv::Point(temp_rect.right(), temp_rect.bottom()),
							cv::Scalar(0, 255, 0), 2);
				}
#ifndef RUNNING_ON_ECLIPSE
				m_ui->showFrame(frame);
#endif
			}
		}

	}
}

void CObjectDetector::loadDetectors() {
	if (m_pObjectDB == NULL) {
		LOG_ERR("Null Database");
		exit(-1);
	}
	for (auto& obj_data : m_pObjectDB->getData()) {
		detector_t tempDetector;
		std::string fileName = DETECTORS_DIR + obj_data.name + ".svm";
		struct stat buffer;

		// check for existence of file
		if (stat(fileName.c_str(), &buffer) == 0) {
			std::ifstream fin(fileName, std::ios::binary);

			deserialize(tempDetector, fin);
			m_detectors.insert(
					std::pair<std::string, detector_t>(obj_data.name,
							tempDetector));
		}
	}
}

void CObjectDetector::stop() {
	if (m_isActive) {
		m_isActive = false;
		m_thread.join();
		LOG_INFO("Detector thread closed..");
	}
}

success_t CObjectDetector::start_detection() {
	if (!m_isActive) {
		m_isActive = true;
		m_thread = std::thread(&CObjectDetector::run_continuous_detection,
				this);

		return true;
	}
	return false;
}

success_t CObjectDetector::start_training() {
	if (!m_isActive) {
		m_isActive = true;
		m_thread = std::thread(&CObjectDetector::run_training, this);

		return true;
	} else {
		LOG_ERR("Something else is running on this thread");
	}
	return false;
}

#ifndef RUNNING_ON_ECLIPSE
void CObjectDetector::connectToUI(CMainWindow* ui) {
	m_ui = ui;
}
#endif
