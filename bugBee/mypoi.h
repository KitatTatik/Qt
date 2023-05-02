#ifndef MYPOI_H
#define MYPOI_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <vector>
#include <utility>
#include <QGraphicsSceneMouseEvent>


class MyPoi : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString poiName;
    QString poiInfo;
    int poix,poiy;

    void showStuff(QVector<QString>);

public:
    explicit MyPoi(QObject *parent = 0);
    ~MyPoi();
    void setInfo (QString);
    void setXY (int,int);
    void setName (QString);
    QVector<QString> myVector;

signals:
    void signal1(int,int,QVector<QString>);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};
#endif // MYPOI_H
