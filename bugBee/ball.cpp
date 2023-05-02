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
    QString ballpath =":/images/ball2.png";
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

