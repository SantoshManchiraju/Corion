#include <QMessageBox>
#include <QDesktopWidget>
#include <QDebug>
#include <QDir>
#include <QXmlStreamReader>
#include <opencv2/opencv.hpp>

#include "CMainWindow.h"
#include "ui_mainwindow.h"
#include "CDialogBox.h"
#include "CObjectDetails.h"
#include "CToastMsg.h"
#include "CHelper.h"
#include "../logger/Logger.h"
#include "../config/Constants.h"
#include "../state_events/EventTypes.h"

#include "../vision/CVisionController.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow),
    m_wall(new QLabel(this))
{
    m_DB = 0;
    m_pEventBuffer = NULL;

    ui->setupUi(this);

    organizeUI();
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::connectToDB(CObjectDatabase *db)
{
    m_DB = db;
    Logger::INFO("DB connection level 1");
}

void CMainWindow::organizeUI()
{
    QRect monitorGeometry(QApplication::desktop()->availableGeometry());

    setGeometry(monitorGeometry);
    int upperMargin = 0.1 * monitorGeometry.height();
    m_wall->setGeometry(0,upperMargin ,monitorGeometry.width(),monitorGeometry.height()-upperMargin);
    m_wall->setStyleSheet("background: gray");
    m_wall->show();
    cv::VideoCapture cam(CAMERA_INDEX);
    if(cam.isOpened()){
        cv::Mat frame;
        cam >> frame;
        m_imgLabel = new CDrawingBoard(frame, this);
    }
    m_toast = new CToastMsg(this);
    m_toast->hide();
}

void CMainWindow::addEventToBuffer(event::EventType event)
{
    if(m_pEventBuffer != NULL){
        m_pEventBuffer->setEvent(event);
    }
    else{
        Logger::ERR("Event buffer not connected");
        exit(-1);
    }
}

CDrawingBoard *CMainWindow::drawingBoard()
{
    return m_imgLabel;
}

void CMainWindow::showToastMsg(std::string msg)
{
    m_toast->showMsg(msg);
}

void CMainWindow::on_bt_watch_clicked()
{
    addEventToBuffer(event::START_WATCHING);
    //    cv::VideoCapture cam(CAMERA_INDEX);
    //    if(cam.isOpened()){
    //        cv::Mat frame;
    //        cam >> frame;
    //        m_imgLabel->projectAndHold(frame);
    //    }
    //    cv::Mat frame(cv::imread("/home/bob/dlib-19.4/examples/video_frames/frame_000100.jpg"));
    //    m_imgLabel = new CDrawingBoard(frame, this);
    //    m_imgLabel->projectAndHold(frame);
    //    dlib::drectangle a(93,110, 93+38, 110+86);
    //    dlib::drectangle b(dlib::centered_rect(93,110, 38, 86));
    //    m_imgLabel->drawSelectionBox(b);
    //    m_imgLabel->drawSelectionBox(a);
    ////    m_imgLabel->drawSelectionBox(dlib::drectangle(93,110, 38, 86));

}


void CMainWindow::on_bt_pause_clicked()
{
    addEventToBuffer(event::PAUSE_WATCHING);
    //    qDebug() << m_imgLabel->getSelectionBox().left();
    //    CVisionController temp;

    //    temp.m_ui = this;
    //    temp.runTracking();
}

void CMainWindow::on_bt_track_clicked()
{
    addEventToBuffer(event::START_TRACKING);
}

void CMainWindow::on_bt_save_clicked()
{
    if (m_DB !=0){
        CDialogBox a;
        a.connectToDB(m_DB);

        CObjectDetails physicalObject =  a.execute();

        if(physicalObject.isValid()){
            QDir objectDBDir("../Objects");

            if(!physicalObject.isKnown()){
                objectDBDir.mkdir(physicalObject.name());
                m_DB->addObjectToDB(physicalObject.name().toStdString());
            }else{
                // change up_to_date status
                m_DB->setUpToDateStatus(physicalObject.name().toStdString(),false);
            }
            objectDBDir.cd(physicalObject.name());
            m_imgLabel->saveImageToDisk(objectDBDir.absolutePath(),physicalObject.isKnown());
        }
    }else{
        Logger::ERR("Database not connected!");
    }

}

void CMainWindow::closeEvent(QCloseEvent *event)
{
    if(m_pEventBuffer != NULL){
        m_pEventBuffer->setEvent(event::SHUT_DOWN);
    }
    event->accept();
}

void CMainWindow::showSpokenText(std::string text)
{

}

void CMainWindow::showFrame(cv::Mat frame)
{
    m_imgLabel->projectImage(frame);
}

void CMainWindow::connectToEventBuffer(CEventBuffer *eventBuffer)
{
    m_pEventBuffer = eventBuffer;
}


void CMainWindow::on_bt_clear_clicked()
{
    if(m_imgLabel->m_rubberBand != 0){
        m_imgLabel->m_rubberBand->hide();
    }
}

void CMainWindow::on_bt_learn_clicked()
{
    addEventToBuffer(event::START_LEARNING);
//    showToastMsg("Test Msg..");
}

void CMainWindow::on_bt_wht_see_clicked()
{
    addEventToBuffer(event::START_DETECTION);
}

void CMainWindow::on_bt_listen_clicked()
{
    addEventToBuffer(event::START_LISTENING);
}

void CMainWindow::on_bt_stop_listen_clicked()
{
    addEventToBuffer(event::STOP_LISTENING);
}
