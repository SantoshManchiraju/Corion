#include "CRubberBand.h"
#include <iostream>

CRubberBand::CRubberBand(QWidget* parent, QGraphicsPixmapItem *pixmap)
    :QRubberBand(QRubberBand::Rectangle, parent), m_isSelected(false)
{
    setFocusPolicy(Qt::ClickFocus);
    setFocus();
}

CRubberBand::~CRubberBand()
{

}

void CRubberBand::changeColor(const QColor &color)
{
    QPalette pal;
    pal.setBrush(QPalette::Highlight, QBrush(color));
    this->setPalette(pal);
}

void CRubberBand::keyPressEvent(QKeyEvent *event){
    std::cout<<"Key pressed"<<std::endl;
    if(event->key() == Qt::Key_Delete){
        std::cout<<"delete pressed"<<std::endl;
//        TODO: delete rubber band
    }
}

void CRubberBand::mouseDoubleClickEvent(QMouseEvent *event){
    std::cout<<"Double pressed"<<std::endl;
}

void CRubberBand::mousePressEvent(QMouseEvent *event)
{
    if(this->underMouse()){
        changeColor(Qt::red);
        m_isSelected = true;
    }else{
        changeColor(Qt::red);
        m_isSelected = false;
    }

}
