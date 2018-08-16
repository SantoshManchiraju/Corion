/*
 * CSpeechRecog.cpp
 *
 *  Created on: May 18, 2017
 *      Author: krish
 */

#include "CSpeechRecog.h"
#include "../logger/Logger.h"

CSpeechRecog::CSpeechRecog(std::string grammarFile) {

	m_config = cmd_ln_init(NULL, ps_args(), TRUE, "-hmm",
			"../en-in-5.2/en_in.cd_cont_5000", "-dict",
			"../en-in-5.2/en_in.dic", /*"-lm", "../en-in-5.2/en-us.lm.bin",*/"-samprate",
			"16000", "-jsgf", grammarFile.c_str(), "-logfn", "/dev/null",
			NULL);

	if (m_config == NULL) {
		LOG_ERR("Failed to create configuration object for speech recognition")
		exit(-1);
	}

	m_ps = ps_init(m_config);
	if (m_ps == NULL) {
		LOG_ERR("Failed to create recognizer");
		exit(-1);
	}

	m_ad = NULL;
	if (openAudioDevice() == false) {
		LOG_ERR("Failed to open the audio device");
		exit(-1);
	}
	m_isRunning = false;
}

CSpeechRecog::~CSpeechRecog() {
	closeAudioDevice();
	ps_free(m_ps);
	cmd_ln_free_r(m_config);
}

/*void CSpeechRecog::recognize_from_microphone() {

 if ((k = ad_read(m_ad, m_adbuf, 2048)) < 0)
 E_FATAL("Failed to read audio\n");
 ps_process_raw(m_ps, m_adbuf, k, FALSE, FALSE);

 m_is_inSpeech = ps_get_in_speech(m_ps);
 if (m_is_inSpeech && !m_is_UttStarted) {
 m_is_UttStarted = true;
 E_INFO("Listening...\n");
 }
 if (!m_is_inSpeech && m_is_UttStarted) {
 speech -> silence transition, time to start new utterance
 ps_end_utt(m_ps);
 hyp = ps_get_hyp(m_ps, NULL);
 if (hyp != NULL) {
 printf("%s\n", hyp);
 fflush(stdout);
 }

 if (ps_start_utt(m_ps) < 0)
 E_FATAL("Failed to start utterance\n");
 m_is_UttStarted = false;
 E_INFO("Ready....\n");
 }
 sleep(0.1);

 }*/

void CSpeechRecog::recognizeFromMic() {

	int16 adbuf[2048];
	bool is_UttStarted(false), is_inSpeech(false), hotWordSpoken(false);
	int32 k;
	char const *hyp;

	while (m_isRunning) {
		if ((k = ad_read(m_ad, adbuf, 2048)) < 0)
			LOG_ERR("Failed to read audio");
		ps_process_raw(m_ps, adbuf, k, FALSE, FALSE);

		is_inSpeech = ps_get_in_speech(m_ps);
		if (is_inSpeech && !is_UttStarted) {
			is_UttStarted = true;
			LOG_INFO("Listening...");
		}
		if (!is_inSpeech && is_UttStarted) {
			/* speech -> silence transition, time to start new utterance  */
			ps_end_utt(m_ps);
			hyp = ps_get_hyp(m_ps, NULL);
			if (hyp != NULL) {
				if (strcmp(hyp, "hello") == 0) {
					hotWordSpoken = true;
					LOG_INFO("Yes sir....");
				} else if (hotWordSpoken) {
					m_recognizedSpeech = hyp;
					//std::cout << m_recognizedSpeech << std::endl;
                    LOG_INFO(m_recognizedSpeech);
					m_pEventBuffer->setEvent(event::SPEECH_RECOGNIZED);
					hotWordSpoken = false;
				}
			}

			if (ps_start_utt(m_ps) < 0)
				LOG_ERR("Failed to start utterance");
			is_UttStarted = false;
			LOG_INFO("Ready..");
		}
		sleep(0.1);
	}
}

bool CSpeechRecog::openAudioDevice() {
	if ((m_ad = ad_open_dev(cmd_ln_str_r(m_config, "-adcdev"),
			(int) cmd_ln_float32_r(m_config, "-samprate"))) == NULL) {
		LOG_ERR("Failed to open audio device");
		return false;
	}
	LOG_INFO("Succesfully opened the audio device");

	if (ad_start_rec(m_ad) < 0)
		LOG_ERR("Failed to start recording");

	if (ps_start_utt(m_ps) < 0)
		LOG_ERR("Failed to start utterance");

	return true;
}

void CSpeechRecog::closeAudioDevice() {
	ad_close(m_ad);
}

bool CSpeechRecog::recognizeFromFile(std::string fullFilePath,
		std::string& output) {

	FILE *fh;
	int16 buf[512];
	int32 score;

	fh = fopen(fullFilePath.c_str(), "rb");

	if (fh == NULL) {
		fprintf(stderr, "Unable to open input file %s", fullFilePath.c_str());
		return false;
	}

	ps_start_utt(m_ps);

	while (!feof(fh)) {
		size_t nsamp;
		nsamp = fread(buf, 2, 512, fh);
		ps_process_raw(m_ps, buf, nsamp, FALSE, FALSE);
	}

	ps_end_utt(m_ps);
	output = ps_get_hyp(m_ps, &score);
	std::cout << "Recognized: " << output << std::endl;

	fclose(fh);
	return true;
}

success_t CSpeechRecog::startListening() {
	if (!m_isRunning) {
		m_isRunning = true;
		m_thread = std::thread(&CSpeechRecog::recognizeFromMic, this);

		return true;
	}
	return false;
}

success_t CSpeechRecog::join() {
	if (m_isRunning) {
		m_thread.join();
		return true;
	}
	return false;
}

success_t CSpeechRecog::stop() {
	if (m_isRunning) {
		m_isRunning = false;
		m_thread.join();
		LOG_INFO("Speech thread closed..");
		return true;
	}
	return false;
}

void CSpeechRecog::connectToEventBuffer(CEventBuffer* eventBuffer) {
	m_pEventBuffer = eventBuffer;
}

std::string& CSpeechRecog::getRecognizedSpeech() {
	return m_recognizedSpeech;
}
