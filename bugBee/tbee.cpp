#include "tbee.h"
#include <math.h>
#include <iostream>
#include <QPainter>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
using namespace std;
QT_END_NAMESPACE

qreal dif =200;
static const double Pi = 3.141592653;
static double TwoPi = 2.0 * Pi;
QSound bee(":/images/compress.wav");
QSound scream(":/images/ouch.wav");

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}
Tbee::Tbee()
    : QGraphicsObject()
{
    setRotation(0);

    state = STOP;
    gameTimer = new QTimer();
    connect(gameTimer, &QTimer::timeout, this, &Tbee::slotGameTimer);
    gameTimer->start(10);
}

QRectF Tbee::boundingRect() const
{
    return QRectF(-12,-15,144,160);
}

void Tbee::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/images/bee1.png");
    painter->drawPixmap(0, 0, 80, 80, pixmap);
    qreal dif1 = sqrt((this->y() - 375.)*(this->y() - 375.) + (this->x() - 135)*(this->x() - 135));
    dif = 1./ max(1./dif, 1/dif1);
    this->setScale((1. - 14./ (dif + 15.)));
    this->setZValue(dif);
    if (dif > 10.) this->setZValue(10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Tbee::slotGameTimer()
{
    int eps;
    if(state){
        QLineF lineToTarget(QPoint(0,0), mapFromScene(target));
        if(lineToTarget.length() > 2){
             setPos(mapToParent(0, -2));
        }
        // borders control

        if(this->x() - 30 < 0){
            this->setX(30);
            state = STOP;
        }
        if(this->x() + 30 > 1160){
            this->setX(1160 - 30);
            state = STOP;
        }
        if(this->y() - 30 < 0){
            this->setY(30);
            state = STOP;
        }
        if(this->y() + 30 > 800){
            this->setY(800 - 30);
            state = STOP;
        }
        // pooh control
        eps = 2;
        if ((abs(this->y() - 375) < eps) && (abs(this->x() - 135) < eps)) {
            scream.play();
            scream.setLoops(1);
            emit mysignal(130,305);
        }
        QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                               << mapToScene(0, 0)
                                                               << mapToScene(-30, -30)
                                                               << mapToScene(30, -30));
        qreal dist = 200.;
        qreal dist0 = 200.;
        foreach (QGraphicsItem *item, foundItems) {
            if (item == this)
                continue;
            dist =sqrt((this->y() - item->y())*(this->y() -item->y()) + (this->x() - item->x())*(this->x() - item->x()));
            if (dist < dist0) dist0 = dist;
        }
        dif = dist0;

    }
}

void Tbee::slotTarget(QPointF point)
{
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    if (angleToTarget >= 0 && angleToTarget < Pi) {
        // Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        // Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }

    state = GO;
}

void Tbee::slotSound()
{
    bee.setLoops(2);// QSound::Infinite
    bee.play();
}

