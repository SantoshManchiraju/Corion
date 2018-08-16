#ifndef CRUBBERBAND_H
#define CRUBBERBAND_H

#include <QRubberBand>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

class CRubberBand : public QRubberBand
{
private:
    bool m_isSelected;
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
public:
    CRubberBand(QWidget* parent=0, QGraphicsPixmapItem* pixmap=0);
    virtual ~CRubberBand();
    void changeColor(const QColor &color);
};

#endif // CRUBBERBAND_H
