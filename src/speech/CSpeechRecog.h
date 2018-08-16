/*
 * CSpeechRecog.h
 *
 *  Created on: May 18, 2017
 *      Author: krish
 */

#ifndef CSPEECHRECOG_H_
#define CSPEECHRECOG_H_

#include <string>
#include <thread>
#include <pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>
#include <iostream>
#include <unistd.h>

#include "../config/Types.h"
#include "../state_events/CEventBuffer.h"

// Could be a executed as a Thread

class CSpeechRecog {
protected:
	// Audio related
	cmd_ln_t* m_config; // configuration
	ps_decoder_t* m_ps; // decoder
	ad_rec_t *m_ad; // audio device
	std::string m_recognizedSpeech;

	// Thread related
	std::thread m_thread;
	bool m_isRunning;

	// Event
	CEventBuffer *m_pEventBuffer;
public:
	CSpeechRecog(std::string grammarFile = "../grammarTest.jsgf");
	virtual ~CSpeechRecog();

	bool openAudioDevice();
	void closeAudioDevice();
	void recognizeFromMic();
	bool recognizeFromFile(std::string, std::string&);

	std::string& getRecognizedSpeech();

	// Thread related
	success_t startListening();
	success_t join();
	success_t stop();

	void connectToEventBuffer(CEventBuffer *eventBuffer);

};

#endif /* CSPEECHRECOG_H_ */
