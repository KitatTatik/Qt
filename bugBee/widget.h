#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QTimer>
#include "customscene.h"

//#include "tbee.h"
//#include "ball.h"
//#include "Hfl.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void ball_emit(int,int);
    void slotFromPoi(int,int, QVector<QString>);

private:
    Ui::Widget *ui;
    CustomScene *scene;
    QTimer          *timer;

};

#endif // WIDGET_H
