#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QTimer>
#include <QGraphicsObject>

class Ball : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Ball();

signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QTimer *ballTimer;
    //QPointF target;
    //bool state;
private slots:
    void slotBallTimer();

};

#endif 
