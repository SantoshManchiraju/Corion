#ifndef CSELECTABLEPICTURE_H
#define CSELECTABLEPICTURE_H


#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QString>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <dlib/geometry/drectangle.h>

#include "CRubberBand.h"
#include "CMainWindow.h"

class CDrawingBoard : public QLabel
{
    friend class CMainWindow;
private:
    cv::Mat m_image;
    CRubberBand *m_rubberBand;
    QPoint m_rubberBandOrigin;
    double m_scaleFactor;

    bool m_isShiftPresssed;
    bool m_isCtrlPressed;


protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);
public:
    CDrawingBoard(cv::Mat , QWidget *parent = 0);
    virtual ~CDrawingBoard();
    virtual void show();
    virtual void hide();
    void projectImage(cv::Mat frame);
    void projectAndHold(cv::Mat frame);
    void getXMLtext(std::ofstream & file);
    bool saveImageToDisk(QString location, bool isObjectKnown);
    void drawSelectionBox(dlib::drectangle selection);
    dlib::drectangle getSelectionBox();
    cv::Mat getCurrentFrame();
};

#endif // CSELECTABLEPICTURE_H
