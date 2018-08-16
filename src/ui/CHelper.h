#ifndef CHELPER_H
#define CHELPER_H

#include <QImage>
#include <opencv2/opencv.hpp>
#include <dlib/geometry/drectangle.h>

class CHelper
{
public:
    CHelper();
    static QImage cvMatToQImage( const cv::Mat &inMat );
    static dlib::drectangle qrect2drect(QRect selection);
    static QRect drect2qrect(dlib::drectangle selection);
};

#endif // CHELPER_H
