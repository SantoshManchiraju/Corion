/*
 * GuiInterface.h
 *
 *  Created on: Jul 24, 2017
 *      Author: bob
 *      This is an interface class for any GUI which is used for this project
 */

#ifndef SRC_INTERFACES_GUIINTERFACE_H_
#define SRC_INTERFACES_GUIINTERFACE_H_

#include <string>
#include "opencv2/opencv.hpp"

class GuiInterface {
public:
	virtual void showSpokenText(std::string) = 0;
	virtual void showFrame(cv::Mat) = 0;
	virtual ~GuiInterface() {
	}
	;
};

#endif /* SRC_INTERFACES_GUIINTERFACE_H_ */
