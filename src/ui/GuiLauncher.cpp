#ifndef RUNNING_ON_ECLIPSE

#include "GuiLauncher.h"
#include <iostream>
#include <unistd.h>

CGuiLauncher::CGuiLauncher(int argc, char *argv[])
{
    m_mainWindow = NULL;
    m_isInitialized = false;
}

CGuiLauncher::~CGuiLauncher()
{
    delete m_mainWindow;
}

void CGuiLauncher::run()
{
    int argc =0;
    QApplication app(argc,NULL);

    m_mainWindow = new CMainWindow();
    m_isInitialized = true;
    m_mainWindow->show();

    app.exec();
}

CMainWindow *CGuiLauncher::ui()
{
    return m_mainWindow;
}

void CGuiLauncher::waitForInit()
{
    while(!m_isInitialized){
        std::cout << "Waiting for GUI init..." << std::endl;
        sleep(1);
    }
}

#endif // RUNNING_ON_ECLIPSE
