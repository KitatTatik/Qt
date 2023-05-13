#include "Hfl.h"
#include <QKeyEvent>
#include <QDebug>

Hfl::Hfl(QGraphicsItem *parent)
     :QGraphicsObject(parent),
    angle(0.), ratio(0.025), k(1), i(0)
//it would be better to provide for default values of ix and iy, too
{
   setRotation(angle);
   setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable);
   setFlags(QGraphicsItem::ItemSendsGeometryChanges|
   QGraphicsItem::ItemIsMovable);

   }
     
Hfl::~Hfl()
{

}

void Hfl::setXY (int x, int y)
{
    ix=x;
    iy=y;
}

QRectF Hfl::boundingRect() const
{
    return QRectF(0,0,200,200);
}
     
void Hfl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/images/hfl2.png");
    painter->drawPixmap(0, 0, 180, 180, pixmap);

    this->setScale(ratio);
    this->setZValue(0.01);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
     

void Hfl::keyPressEvent(QKeyEvent *event)
{

 /*   if (event->key() == Qt::Key_Left) {
        angle += 5;
        setRotation(angle);
    }

    if (event->key() == Qt::Key_Right) {
        angle -= 5;
        setRotation(angle);
    }
 */

    if ((event->key() == Qt::Key_Up) && (i < 6)) {
        ratio = ratio * 1.75;
        this->setY((this->y()) - 65.2*ratio);
        this->setX((this->x()) - 30.2*ratio);
        this->setZValue(ratio*500.);
        angle += 15*k;
        k=-k;
        i++;
        //qDebug() << "ratio" << ratio << "and" << this->zValue();
        setRotation(angle);
    }
    if ((event->key() == Qt::Key_Down) && (i >= 0)) {
        this->setZValue(ratio*500.);
        this->setX((this->x()) + 30.2*ratio);
        this->setY((this->y()) + 65.2*ratio);
        ratio = ratio / 1.75;
        angle += 15*k;
        k=-k;
        --i;
        qDebug() << "x y" << this->x() << this->y();
        setRotation(angle);
    }
    /*
    if (event->key() == Qt::Key_Up) {
        for (int i =0; i < 50; i++) {
         this->setY((this->y()) - 0.01*ratio*(1+i%2));
         this->setX((this->x()) - 0.01*ratio*(1+i%2));
         ratio = ratio * 1.15*(i%2);
         angle += 3*i;
        setRotation(angle);
        }

        for (int i =0; i < 50; i++) {
         this->setY((this->y()) + 0.01*ratio*(1+i%2));
         this->setX((this->x()) + 0.01*ratio*(1+i%2));
         ratio = ratio / (1.15*(i%2));
         angle -= 3*i;
        setRotation(angle);
        }

    }
    */
    QGraphicsItem::keyPressEvent(event);

}

