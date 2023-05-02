#ifndef Tbee_H
#define Tbee_H

#include <QObject>
#include <QTimer>
#include <QGraphicsObject>
#include <QSound>

#define GO true
#define STOP false

class Tbee : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Tbee();
signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void slotTarget(QPointF point);
    void slotSound();

private:
    QTimer *gameTimer;
    QPointF target;
    bool state;
signals:
    void mysignal(int,int);
private slots:
    void slotGameTimer();

};

#endif // Tbee_H
