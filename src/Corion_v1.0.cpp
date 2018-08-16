//============================================================================
// Name        : 0.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Cerebrum.h"
#include "CRobotController.h"
#include "config/MotionModes.h"
#include "speech/CSpeechRecog.h"
#include "vision/CObjectDatabase.h"

using namespace std;

int main(int argc, char *argv[]) {

//	Cerebrum mainBrain(argc, argv);

//	mainBrain.run();

	CRobotController robot;
//
	robot.connect();
//	robot.startSocketCommunication();
//	robot.sendCmd(neo::CMD_CONNECT_TO_PLTF);
//	robot.setMode(neo::MODE_MOTION_VEL);
//
//	time_t endTime;
//	endTime = time(NULL) + 3;
//	robot.continuee();
//	while (time(0) < endTime) {
//		robot.moveForward();
//		usleep(400000);
//	}
//
////	sleep(3);
//	robot.stop();

//	CSpeechRecog trial("../grammarTest.jsgf");

//	trial.recognizeFromMic();

//	CObjectDatabase objDB("testFile.txt");

//	objDB.loadDBfromFile();
//	objDB.addObjectToDB("key");
//	objDB.addObjectToDB("chair");
//	objDB.addObjectToDB("door");

	return 0;
}

/*
 *
 CSpeechRecog asr("grammarTest.jsgf");
 //	CRobotController robot;
 string asrOutput;
 //	robot.connect();
 //	robot.startSocketCommunication();
 //	robot.sendCmd(neo::CMD_CONNECT_TO_PLTF);
 //	robot.setMode(neo::MODE_MOTION_AUTOMATIC);


 char a;
 while (true) {
 cout << "Continue? (y/n)" << endl;
 cin >> a;

 if (a == 'y') {
 asr.recognizeFromFile("/home/bob/Thesis/workshop/go10.wav",
 asrOutput);
 cout << "understood: " << asrOutput << endl;
 robot.continuee();
 robot.moveForward();
 sleep(3);
 robot.stop();
 } else {
 // disconnect socket, stop the thread and break out
 //			robot.disconnect();
 break;
 }
 }


 while (true) {
 asr.recognizeFromMic(asrOutput);
 cout << asrOutput << endl;
 sleep(0.5);
 }

 while(true)
 asr.recognizeFromMic();

 //	asr.recognizeFromMic(asrOutput);
 //	robot.disconnect();*/
