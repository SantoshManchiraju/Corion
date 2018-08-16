/*
 * CtypeThread.h
 *
 *  Created on: Aug 1, 2017
 *      Author: bob
 */

#ifndef SRC_INTERFACES_CTYPETHREAD_H_
#define SRC_INTERFACES_CTYPETHREAD_H_

#include <pthread.h>

// Posix thread in C++ style as interface

class CtypeThread {
public:
	CtypeThread() {
		m_thread = 0;
		m_isRunning = false;
	}

	virtual ~CtypeThread() {
	}

	/** Returns true if the thread was successfully started, false if there was an error starting the thread */
	bool start() {
		if (!m_isRunning) {
			if (pthread_create(&m_thread, NULL, InternalThreadEntryFunc, this)
					== 0) {
				m_isRunning = true;
				return true;
			} else {
				return false;
			}
		}
		return false;
	}

	/** Will not return until the internal thread has exited. */
	void stop() {
		if (m_isRunning) {
			m_isRunning = false;
			(void) pthread_join(m_thread, NULL);
		}
	}

protected:
	/** Implement this method in your subclass with the code you want your thread to run. */
	virtual void run() = 0;

private:
	static void * InternalThreadEntryFunc(void * This) {
		((CtypeThread *) This)->run();
		return NULL;
	}

	pthread_t m_thread;
	bool m_isRunning;
};

#endif /* SRC_INTERFACES_CTYPETHREAD_H_ */
