#ifndef RUNNING_ON_ECLIPSE

#ifndef TRIALMAIN_H
#define TRIALMAIN_H

#include <QApplication>

#include "CMainWindow.h"
#include "../config/Types.h"
#include "../interfaces/CtypeThread.h"

class CGuiLauncher : public CtypeThread
{
private:
    CMainWindow *m_mainWindow;
    bool m_isInitialized;

public:
    CGuiLauncher(int argc, char *argv[]);
    ~CGuiLauncher();
    void run();
    CMainWindow* ui();
    void waitForInit();
};

#endif // TRIALMAIN_H
#endif // RUNNING_ON_ECLIPSE
