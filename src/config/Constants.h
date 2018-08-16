/*
 * Constants.h
 *
 *  Created on: May 30, 2017
 *      Author: bob
 */

#ifndef SRC_CONFIG_CONSTANTS_H_
#define SRC_CONFIG_CONSTANTS_H_

#include <string>

namespace neo {

extern const unsigned short int NEO_HEADER_LENGTH; // Header + message length (int)
extern const std::string HOST_ADDRESS;
extern const unsigned short int SOCKET_PORT;
}

extern const unsigned short int CAMERA_INDEX;
extern const std::string OBJECTS_DIR;
extern const std::string DETECTORS_DIR;

#endif /* SRC_CONFIG_CONSTANTS_H_ */
