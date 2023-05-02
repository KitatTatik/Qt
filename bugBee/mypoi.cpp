#include "mypoi.h"
#include <QApplication>
#include <QDebug>

MyPoi::MyPoi(QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

MyPoi::~MyPoi()
{

}
void MyPoi::setName(QString n)
{
    poiName = n;
    myVector.push_back(poiName);
}

void MyPoi::setXY (int x, int y)
{
    poix=x;
    poiy=y;
}

void MyPoi::setInfo (QString s)
{
    poiInfo = s;
    setToolTip("Name " + poiName + poiInfo);
}

QRectF MyPoi::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void MyPoi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(QRectF(0, 0, 30, 30));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void MyPoi::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(QApplication::mouseButtons() == Qt::RightButton){
        emit signal1(poix,poiy,myVector);
       //qDebug() << poiName << "  " << myVector[1]<< " Deb signal";
    }
    QGraphicsItem::mousePressEvent(event);
}
