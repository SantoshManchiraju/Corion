/*
 * ENeoCommands.h
 *
 *  Created on: May 30; 2017
 *      Author: bob
 */

#ifndef SRC_ENEOCOMMANDS_H_
#define SRC_ENEOCOMMANDS_H_

#include "../config/Types.h"

namespace neo {

// CAN communication
extern const byte_t CMD_CONNECT_TO_PLTF;
extern const byte_t CMD_SHUTDOWN_PLTF;
extern const byte_t CMD_INIT_PLTF;
extern const byte_t CMD_SET_BRAKE;
extern const byte_t CMD_SET_DIGOUT;

extern const byte_t CMD_START_ULTRASONIC;
extern const byte_t CMD_STOP_ULTRASONIC;

extern const byte_t CMD_ADD_CAN_LISTENING_ID;
extern const byte_t CMD_REMOVE_CAN_LISTENING_ID;
extern const byte_t CMD_SEND_CAN_MESSAGE;
extern const byte_t CMD_GET_CAN_MESSAGES;

// platform operation
extern const byte_t CMD_START;
extern const byte_t CMD_BREAK;
extern const byte_t CMD_CONTINUE;
extern const byte_t CMD_STOP;

extern const byte_t CMD_SET_MODE;
extern const byte_t CMD_EXIT;
extern const byte_t CMD_CLOSE_SOCKET;

// request status
extern const byte_t CMD_GET_STATUS;

// motion commands
extern const byte_t CMD_MOVE_PATH;
extern const byte_t CMD_MOVE_TO_STATION;
extern const byte_t CMD_MOVE_ABS;
extern const byte_t CMD_MOVE_REL;
extern const byte_t CMD_MOVE_VEL_WHEEL;
extern const byte_t CMD_MOVE_VEL;

// platform data
extern const byte_t CMD_SET_MAP;
extern const byte_t CMD_GET_MAP;
extern const byte_t CMD_LOAD_MAP;
extern const byte_t CMD_SAVE_MAP;

extern const byte_t CMD_MAPPING_START;
extern const byte_t CMD_MAPPING_RESET;
extern const byte_t CMD_MAPPING_STOP;

extern const byte_t CMD_SET_ROADMAP;
extern const byte_t CMD_GET_ROADMAP;
extern const byte_t CMD_LOAD_ROADMAP;
extern const byte_t CMD_SAVE_ROADMAP;

extern const byte_t CMD_SET_FRM_PLTF;

extern const byte_t CMD_SET_PLTF_PARAM;
extern const byte_t CMD_GET_PLTF_PARAM;
extern const byte_t CMD_GET_PLTF_PARAM_VEC;

extern const byte_t CMD_SET_PROGRAM;
extern const byte_t CMD_GET_PROGRAM;
extern const byte_t CMD_LOAD_PROGRAM;
extern const byte_t CMD_SAVE_PROGRAM;

// special functions
extern const byte_t CMD_SPEAK_TEXT;
extern const byte_t CMD_PLAY_SOUND;
extern const byte_t CMD_GRAB_IMAGE;

extern const byte_t CMD_SET_POS_HEAD_DRIVE;
extern const byte_t CMD_SET_VEL_HEAD_DRIVE;

extern const byte_t CMD_SET_POS_PAN_TILT_CAMERA;

// group debug
extern const byte_t CMD_GET_DEBUG_DATA;

extern const byte_t CMD_DEBUG1;
extern const byte_t CMD_DEBUG2;
extern const byte_t CMD_DEBUG3;
extern const byte_t CMD_DEBUG4;

extern const byte_t CMD_MOUSE_MOVE;

extern const byte_t CMD_SET_LOG_ENABLED;

extern const byte_t CMD_SET_POST_PROCESS_FILENAME;

extern const byte_t CMD_SET_EVENT;

extern const byte_t CMD_GET_CAMERA;

extern const byte_t CMD_GET_MAPIMAGE;

extern const byte_t CMD_ENABLE_EXT_MAPPING;
extern const byte_t CMD_DISABLE_EXT_MAPPING;
extern const byte_t CMD_EXT_WRITE_MAPPING;
extern const byte_t CMD_EXT_READ_MAPPING;

// write on 2nd Line of LCD
extern const byte_t CMD_WRITE_LCD;

// start/stop motion thread to decrease load of computer for other tasks
extern const byte_t CMD_STOP_MOTIONTHREAD;
extern const byte_t CMD_RESTART_MOTIONTHREAD;

// send current position of platform only
extern const byte_t CMD_GET_POSITION;

// group debug
extern const byte_t CMD_SHUTDOWN_HOST;
}

#endif /* SRC_ENEOCOMMANDS_H_ */
