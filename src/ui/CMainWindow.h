#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <QCloseEvent>

#include "CDrawingBoard.h"
#include "CToastMsg.h"
#include "../interfaces/GuiInterface.h"
#include "../state_events/CEventBuffer.h"
#include "../vision/CObjectDatabase.h"

class CDrawingBoard;

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow, GuiInterface
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    void connectToDB(CObjectDatabase *db);
    void showSpokenText(std::string);
    void showFrame(cv::Mat frame);
    void connectToEventBuffer(CEventBuffer *eventBuffer);
    virtual void closeEvent(QCloseEvent *event);
    CDrawingBoard* drawingBoard();
    void showToastMsg(std::string msg);

private slots:
    void on_bt_save_clicked();
    void on_bt_watch_clicked();
    void on_bt_pause_clicked();
    void on_bt_track_clicked();
    void on_bt_clear_clicked();
    void on_bt_learn_clicked();
    void on_bt_wht_see_clicked();

    void on_bt_listen_clicked();

    void on_bt_stop_listen_clicked();

private:
    Ui::CMainWindow *ui;
    QLabel *m_wall;
    CDrawingBoard *m_imgLabel;
    CEventBuffer *m_pEventBuffer;
    CObjectDatabase *m_DB;
    CToastMsg *m_toast;

    void organizeUI();
    void addEventToBuffer(event::EventType event);

};

#endif // CMAINWINDOW_H
