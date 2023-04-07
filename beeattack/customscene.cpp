#include "customscene.h"
#include "qgraphicsitem.h"
#include <QApplication>
#include <iostream>

QT_BEGIN_NAMESPACE
using namespace std;
QT_END_NAMESPACE


CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene(parent)
{

}

CustomScene::~CustomScene()
{

}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(QApplication::mouseButtons() == Qt::LeftButton){
        emit signalTargetCoordinate(event->scenePos());
    }
   /* if(QApplication::mouseButtons() == Qt::RightButton){
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                //QPen(Qt::NoPen));
                QPen(Qt::white,2,Qt::DotLine,Qt::RoundCap));

        previousPoint = event->scenePos();
    }*/
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(QApplication::mouseButtons() == Qt::LeftButton){
        emit signalTargetCoordinate(event->scenePos());
    }
    if(QApplication::mouseButtons() == Qt::MiddleButton){
        QGraphicsItem *foundItem = this->itemAt(event->scenePos().x(),event->scenePos().y(),QTransform());
        //removeItem(foundItem);
        delete(foundItem);
        this->itemAt(274,466,QTransform())->setFocus();
        //if (foundItem->isSelected()) {
        //  foundItem->hide();
        //}

    }
}

