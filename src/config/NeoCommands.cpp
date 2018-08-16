/*
 * NeoCommands.cpp
 *
 *  Created on: Jun 1, 2017
 *      Author: bob
 */

#include "NeoCommands.h"

namespace neo{

// CAN communication
const byte_t CMD_CONNECT_TO_PLTF = 0;
const byte_t CMD_SHUTDOWN_PLTF = 1;
const byte_t CMD_INIT_PLTF = 2;
const byte_t CMD_SET_BRAKE = 3;
const byte_t CMD_SET_DIGOUT = 4;

const byte_t CMD_START_ULTRASONIC = 5;
const byte_t CMD_STOP_ULTRASONIC = 6;

const byte_t CMD_ADD_CAN_LISTENING_ID = 7;
const byte_t CMD_REMOVE_CAN_LISTENING_ID = 8;
const byte_t CMD_SEND_CAN_MESSAGE = 9;
const byte_t CMD_GET_CAN_MESSAGES = 10;

// platform operation
const byte_t CMD_START = 11;
const byte_t CMD_BREAK = 12;
const byte_t CMD_CONTINUE = 13;
const byte_t CMD_STOP = 14;

const byte_t CMD_SET_MODE = 15;
const byte_t CMD_EXIT = 16;
const byte_t CMD_CLOSE_SOCKET = 17;

// request status
const byte_t CMD_GET_STATUS = 18;

// motion commands
const byte_t CMD_MOVE_PATH = 19;
const byte_t CMD_MOVE_TO_STATION = 20;
const byte_t CMD_MOVE_ABS = 21;
const byte_t CMD_MOVE_REL = 22;
const byte_t CMD_MOVE_VEL_WHEEL = 23;
const byte_t CMD_MOVE_VEL = 24;

// platform data
const byte_t CMD_SET_MAP = 25;
const byte_t CMD_GET_MAP = 26;
const byte_t CMD_LOAD_MAP = 27;
const byte_t CMD_SAVE_MAP = 28;

const byte_t CMD_MAPPING_START = 29;
const byte_t CMD_MAPPING_RESET = 30;
const byte_t CMD_MAPPING_STOP = 31;

const byte_t CMD_SET_ROADMAP = 32;
const byte_t CMD_GET_ROADMAP = 33;
const byte_t CMD_LOAD_ROADMAP = 34;
const byte_t CMD_SAVE_ROADMAP = 35;

const byte_t CMD_SET_FRM_PLTF = 36;

const byte_t CMD_SET_PLTF_PARAM = 37;
const byte_t CMD_GET_PLTF_PARAM = 38;
const byte_t CMD_GET_PLTF_PARAM_VEC = 39;

const byte_t CMD_SET_PROGRAM = 40;
const byte_t CMD_GET_PROGRAM = 41;
const byte_t CMD_LOAD_PROGRAM = 42;
const byte_t CMD_SAVE_PROGRAM = 43;

// special functions
const byte_t CMD_SPEAK_TEXT = 44;
const byte_t CMD_PLAY_SOUND = 45;
const byte_t CMD_GRAB_IMAGE = 46;

const byte_t CMD_SET_POS_HEAD_DRIVE = 47;
const byte_t CMD_SET_VEL_HEAD_DRIVE = 48;

const byte_t CMD_SET_POS_PAN_TILT_CAMERA = 49;

// group debug
const byte_t CMD_GET_DEBUG_DATA = 50;

const byte_t CMD_DEBUG1 = 51;
const byte_t CMD_DEBUG2 = 52;
const byte_t CMD_DEBUG3 = 53;
const byte_t CMD_DEBUG4 = 54;

const byte_t CMD_MOUSE_MOVE = 55;

const byte_t CMD_SET_LOG_ENABLED = 56;

const byte_t CMD_SET_POST_PROCESS_FILENAME = 57;

const byte_t CMD_SET_EVENT = 58;

const byte_t CMD_GET_CAMERA = 59;

const byte_t CMD_GET_MAPIMAGE = 60;

const byte_t CMD_ENABLE_EXT_MAPPING = 61;
const byte_t CMD_DISABLE_EXT_MAPPING = 62;
const byte_t CMD_EXT_WRITE_MAPPING = 63;
const byte_t CMD_EXT_READ_MAPPING = 64;

// write on 2nd Line of LCD
const byte_t CMD_WRITE_LCD = 70;

// start/stop motion thread to decrease load of computer for other tasks
const byte_t CMD_STOP_MOTIONTHREAD = 72;
const byte_t CMD_RESTART_MOTIONTHREAD = 73;

// send current position of platform only
const byte_t CMD_GET_POSITION = 74;

// group debug
const byte_t CMD_SHUTDOWN_HOST = 99;
}

