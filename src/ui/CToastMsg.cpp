#include "CToastMsg.h"
#include <iostream>
#include <QGraphicsOpacityEffect>
#include <unistd.h>

CToastMsg::CToastMsg(QWidget *parent, int timeout)
    :QLabel(parent)
{

    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.7);
    this->setGraphicsEffect(effect);
    this->setStyleSheet("border:2px solid grey; border-radius: 5px; background-color: black; color : white");
    // geometry
    // xpos 70% of parent width, ypos 5% height
    // width 20% of parent width, height 10% of height

    this->setGeometry(0.7*parent->geometry().width(),
                      0.05*parent->geometry().height(),
                      0.2*parent->geometry().width(),
                      0.1*parent->geometry().height());
    this->setAlignment(Qt::AlignCenter);
    m_timeout = timeout;
}

void CToastMsg::showMsg(std::string msg)
{
    this->setText(QString(msg.c_str()));
    m_mutex.lock();
    m_closeTime = QTime::currentTime().addSecs(m_timeout);
    m_mutex.unlock();
    if(this->isHidden()){
        m_thread = std::thread(&CToastMsg::wait_and_close,this);
        m_thread.detach();
    }
}

void CToastMsg::wait_and_close()
{
    this->show();
    while(true){
        // wait
        std::cout << "timer running"<< std::endl;
//        m_mutex.lock();
        if(QTime::currentTime() > m_closeTime)
            break;
//        m_mutex.unlock();
        sleep(1);
    }

    this->hide();
}

