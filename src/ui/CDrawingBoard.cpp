#include <iostream>
#include <exception>
#include <sstream>

#include "CDrawingBoard.h"
#include "CObjectXmlParser.h"
#include "CHelper.h"
#include "../logger/Logger.h"

CDrawingBoard::CDrawingBoard(cv::Mat frame, QWidget *parent)
    :QLabel(parent),
      m_image(frame)
{
    this->setFocus();
    m_isShiftPresssed = false;
    m_isCtrlPressed = false;
    m_rubberBand = NULL;

    // wall geometry
    int wallMaxHeight = 0.81 * parent->height();
    int wallMaxWidth = 0.81 * parent->width();
    int wallX = parent->geometry().x();
    double wallY = 0.1*parent->geometry().height();

    // scale
    if ( frame.rows < frame.cols ){
        m_scaleFactor = wallMaxHeight /(double) frame.rows;
    }else{
        m_scaleFactor = wallMaxWidth /(double) frame.cols;
    }
    //    m_scaleFactor = 1; // remove as soon as u see this
    // set geometry
    int boardWidth = frame.cols*m_scaleFactor;
    int boardHeight = frame.rows*m_scaleFactor;
    int boardX = (wallX + parent->geometry().width() - boardWidth)/2;
    int boardY = (wallY + parent->geometry().height() - boardHeight)/2;

    this->setGeometry(boardX,boardY,boardWidth,boardHeight);
}

CDrawingBoard::~CDrawingBoard()
{
    delete m_rubberBand;
}

void CDrawingBoard::show()
{
    QLabel::show();
    //    QLabel::update();
    //    m_rubberBand->show();
}

void CDrawingBoard::hide()
{
    //    m_rubberBand->hide();
    QLabel::hide();
}

void CDrawingBoard::projectImage(cv::Mat frame)
{
    QPixmap image = QPixmap::fromImage(CHelper::cvMatToQImage(frame));
    QPixmap scaledImg(image.scaled(image.width()*m_scaleFactor, image.height()*m_scaleFactor));

    this->setPixmap(scaledImg);
    this->show();
}

void CDrawingBoard::projectAndHold(cv::Mat frame)
{
    m_image = frame;
    projectImage(frame);
    if(m_rubberBand != NULL){
//        m_rubberBand->hide();
    }
    this->setFocus();
}

bool CDrawingBoard::saveImageToDisk(QString location, bool isObjectKnown)
{
    if(m_rubberBand != 0){
        QRect actualBox(m_rubberBand->geometry().x()/m_scaleFactor,
                        m_rubberBand->geometry().y()/m_scaleFactor,
                        m_rubberBand->geometry().width()/m_scaleFactor,
                        m_rubberBand->geometry().height()/m_scaleFactor);

        CObjectXmlParser details(location);

        if(isObjectKnown){
            unsigned int imgCount = details.addNewImage(actualBox);
            //            bool retVal = m_image.save(location + "/" + QString::number(imgCount) + ".jpg","JPG");
            bool retVal = cv::imwrite((location + "/" + QString::number(imgCount) + ".jpg").toStdString(),m_image);
            if(!retVal){
                Logger::ERR("Image save failed");
            }
        }else{
            details.createNewFile(actualBox);
            //             bool retVal = m_image.save(location+"/0.jpg","JPG");
            bool retVal = cv::imwrite((location+"/0.jpg").toStdString(),m_image);
            if(!retVal){
                Logger::ERR("Image save failed");
            }
        }

        return true;
    }
    return false;

}

void CDrawingBoard::drawSelectionBox(dlib::drectangle selection)
{
    m_rubberBand->setGeometry(CHelper::drect2qrect(selection*m_scaleFactor));
    m_rubberBand->show();

    //    QRubberBand *rubberBand = new QRubberBand(QRubberBand::Rectangle,this);
    //    rubberBand->setGeometry(CHelper::drect2qrect(selection*m_scaleFactor));
    //    rubberBand->show();
}

dlib::drectangle CDrawingBoard::getSelectionBox()
{
    return (CHelper::qrect2drect(m_rubberBand->geometry()))/m_scaleFactor;
}

cv::Mat CDrawingBoard::getCurrentFrame()
{
    return m_image;
}

void CDrawingBoard::mousePressEvent(QMouseEvent *event)
{
    if (m_isShiftPresssed){
        //        std::cout<<"m_isShiftPresssed: "<<m_isShiftPresssed<<std::endl;
        m_rubberBandOrigin = event->pos();
        m_rubberBand = new CRubberBand(this);
        m_rubberBand->setGeometry(QRect(m_rubberBandOrigin, QSize()));
        m_rubberBand->show();
    }
}

void CDrawingBoard::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isShiftPresssed and m_rubberBand != 0){
        //        std::cout<<"m_isShiftPresssed: "<<m_isShiftPresssed<<std::endl;
        m_rubberBand->setGeometry(QRect(m_rubberBandOrigin, event->pos()).normalized());
    }
}

void CDrawingBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_rubberBand != NULL){
        m_rubberBand->changeColor(Qt::green);
    }
}

void CDrawingBoard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift and !m_isShiftPresssed){
        m_isShiftPresssed = true;
        setCursor(Qt::CrossCursor);
    } else if(event->key() == Qt::Key_Control and !m_isCtrlPressed){
        m_isCtrlPressed = true;
    }
    //    Qt::Key_Delete
}

void CDrawingBoard::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift and m_isShiftPresssed){
        m_isShiftPresssed = false;
        setCursor(Qt::ArrowCursor);
    } else if(event->key() == Qt::Key_Control and m_isCtrlPressed){
        m_isCtrlPressed = false;
    }
}


