#ifndef WIDGET_H
#define WIDGET_H


#include <QtSql/QSqlDatabase>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class Widget : public QWidget
{
   Q_OBJECT

public:
   explicit Widget(QWidget *parent=nullptr);
   ~Widget();
private slots:
   QString btn1_clicked();
   //void label_setting(QString);
private:
   QPushButton *btn1;
   QLabel *label;
public:

};
#endif // WIDGET_H

