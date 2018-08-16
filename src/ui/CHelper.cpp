#include "CHelper.h"

CHelper::CHelper() {

}

QImage CHelper::cvMatToQImage(const cv::Mat &inMat) {
    switch (inMat.type()) {
    // 8-bit, 4 channel
    case CV_8UC4: {
        QImage image(inMat.data, inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step), QImage::Format_ARGB32);

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3: {
        QImage image(inMat.data, inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step), QImage::Format_RGB888);

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1: {
        QImage image(inMat.data, inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step), QImage::Format_Grayscale8);

        return image;
    }

    default:
        //        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

dlib::drectangle CHelper::qrect2drect(QRect selection) {
    return dlib::drectangle((double) selection.left(),
                            (double) selection.top(),
                            (double) selection.right(),
                            (double) selection.bottom());
}

QRect CHelper::drect2qrect(dlib::drectangle selection) {
    return QRect((int) selection.left(),
                 (int) selection.top(),
                 (int) selection.width(),
                 (int) selection.height());
}
