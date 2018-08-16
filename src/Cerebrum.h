#ifndef _CEREBRUM_H
#define _CEREBRUM_H

#include "CRobotController.h"
#include "vision/CVisionController.h"
#include "speech/CSpeechRecog.h"
#include "vision/CObjectDatabase.h"
#include "vision/CObjectDetector.h"
#include "state_events/CEventBuffer.h"
#include "ui/GuiLauncher.h"

class Cerebrum {
private:
	// Frontal Lobe

	CRobotController m_robot;

	// Occipital Lobe

	CVisionController m_vision;

	//	Temporal Lobe

	CSpeechRecog m_speech;

	CObjectDatabase m_objDB;

	CObjectDetector m_detector;

	// Event buffer

	CEventBuffer m_eventBuffer;

	//	UI Lobe

	CGuiLauncher m_uiLauncher;

	std::thread m_trainThread;

	void update_object_models();

	void respond_to_speech();

public:
	Cerebrum(int argc, char * argv[]);

	~Cerebrum();

	void run();

};
#endif
