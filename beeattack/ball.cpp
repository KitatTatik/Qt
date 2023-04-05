#include "ball.h"
#include <QPainter>

Ball::Ball()
    : QGraphicsObject()
{
    ballTimer = new QTimer();

    connect(ballTimer, &QTimer::timeout, this, &Ball::slotBallTimer);
    ballTimer->start(50);
}

QRectF Ball::boundingRect() const
{
    return QRectF(0,0,105,200);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    //int bcase = qrand()%2 +1;
    QString ballpath =":/images/ball2.png";
    //if (bcase == 1) {ballpath= ":/images/ball1.png";}
    pixmap.load(ballpath);
    painter->drawPixmap(0, 0, 100, 180, pixmap);
    this->setScale(0.1+(50./this->y()));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Ball::slotBallTimer()
{
    this->setY((this->y()) - 1);
    this->setZValue(300/(this->y()));
}

