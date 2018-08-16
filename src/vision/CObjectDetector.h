/*
 * CObjectTrainer.h
 *
 *  Created on: Sep 9, 2017
 *      Author: bob
 */

#ifndef SRC_VISION_COBJECTDETECTOR_H_
#define SRC_VISION_COBJECTDETECTOR_H_

#include <dlib/svm_threaded.h>
#include <dlib/string.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>
#include <dlib/cmd_line_parser.h>

#include <iostream>
#include <fstream>
#include <thread>

#include "CObjectDatabase.h"
#include "../config/Types.h"
#ifndef RUNNING_ON_ECLIPSE
#include "../ui/CMainWindow.h"
#endif

typedef dlib::object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6>>> detector_t;

class CObjectDetector {

private:
	// ui
#ifndef RUNNING_ON_ECLIPSE
	CMainWindow* m_ui;
#endif

	// Thread related
	std::thread m_thread;
	bool m_isActive;

	// Recognizer related
	std::map<std::string, detector_t> m_detectors;
	void loadDetectors();

	// Trainer related
	unsigned int m_maxThreads;
	double m_c;
	double m_eps;
	unsigned int m_num_folds;
	unsigned long m_target_size;
	CObjectDatabase* m_pObjectDB;

	void pick_best_window_size(
			const std::vector<std::vector<dlib::rectangle> >& boxes,
			unsigned long& width, unsigned long& height,
			const unsigned long target_size);
	bool contains_any_boxes(
			const std::vector<std::vector<dlib::rectangle> >& boxes);

public:
	CObjectDetector(CObjectDatabase* db);
	~CObjectDetector();

	void connectToObjDB(CObjectDatabase* db);
	void train(std::string input_file, std::string object_name,
			std::string output_dir);
	void run_training();
	success_t start_training();
	void stop();
	void run_continuous_detection();
	success_t start_detection();

#ifndef RUNNING_ON_ECLIPSE
	void connectToUI(CMainWindow* ui);
#endif
};

#endif /* SRC_VISION_COBJECTDETECTOR_H_ */
