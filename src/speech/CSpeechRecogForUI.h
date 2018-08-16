/*
 * CSpeechRecogForUI.h
 *
 *  Created on: Jul 24, 2017
 *      Author: bob
 */

#ifndef SRC_SPEECH_CSPEECHRECOGFORUI_H_
#define SRC_SPEECH_CSPEECHRECOGFORUI_H_

#include "CSpeechRecog.h"

template<class GUI>
class CSpeechRecogForUI: public CSpeechRecog {
private:
	GUI* m_ui;

public:
	CSpeechRecogForUI(std::string grammarFile = "../grammarTest.jsgf");
	virtual ~CSpeechRecogForUI();

	void connectToUI(GUI* ui);
	void recognizeFromMic();

	success_t startListening();

};

template<class GUI>
inline CSpeechRecogForUI<GUI>::CSpeechRecogForUI(std::string grammarFile) :
		CSpeechRecog(grammarFile) {
	m_ui = NULL;
}

template<class GUI>
inline CSpeechRecogForUI<GUI>::~CSpeechRecogForUI() {

}

template<class GUI>
inline void CSpeechRecogForUI<GUI>::recognizeFromMic() {

	int16 adbuf[2048];
	bool is_UttStarted, is_inSpeech;
	int32 k;
	char const *hyp;

	while (m_isRunning) {
		if ((k = ad_read(m_ad, adbuf, 2048)) < 0)
			E_FATAL("Failed to read audio\n");
		ps_process_raw(m_ps, adbuf, k, FALSE, FALSE);

		is_inSpeech = ps_get_in_speech(m_ps);
		if (is_inSpeech && !is_UttStarted) {
			is_UttStarted = true;
			E_INFO("Listening...\n");
		}
		if (!is_inSpeech && is_UttStarted) {
			/* speech -> silence transition, time to start new utterance  */
			ps_end_utt(m_ps);
			hyp = ps_get_hyp(m_ps, NULL);
			if (hyp != NULL) {
				m_recognizedSpeech = hyp;
				std::cout << m_recognizedSpeech << std::endl;
				m_ui->showSpokenText(m_recognizedSpeech);
			}

			if (ps_start_utt(m_ps) < 0)
				E_FATAL("Failed to start utterance\n");
			is_UttStarted = false;
			E_INFO("Ready....\n");
		}
		sleep(0.1);
	}

}

template<class GUI>
inline void CSpeechRecogForUI<GUI>::connectToUI(GUI* ui) {
	m_ui = ui;
}

template<class GUI>
inline success_t CSpeechRecogForUI<GUI>::startListening() {
	if (!m_isRunning) {
		m_isRunning = true;
		m_thread = std::thread(&CSpeechRecogForUI::recognizeFromMic,
				this);

		return true;
	}
	return false;
}

#endif /* SRC_SPEECH_CSPEECHRECOGFORUI_H_ */
