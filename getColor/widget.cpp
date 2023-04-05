#include "widget.h"
#include <sstream>
#include <iostream>

#include <QColorDialog>
#include <QVBoxLayout>
#include <QDebug>



Widget::Widget(QWidget *parent)
   : QWidget(parent)
{
   btn1 = new QPushButton("Point your color");
   QString str1;
   label = new QLabel(str1);

   QVBoxLayout *vbox = new QVBoxLayout();

   connect(btn1, SIGNAL(clicked()),
           this, SLOT(btn1_clicked()));

   vbox->addWidget(btn1);
   vbox->addWidget(label);
   setLayout(vbox);
}

Widget::~Widget() {}

QString Widget::btn1_clicked()
{  QString str1;
   QColor textcolor;
   std::stringstream ss;
   QColor color = QColorDialog::getColor(QColor(102,255, 0), this,
                  "Color Caption");
   if (color.isValid()) {
       QString qss = QString("background-color: %1").arg(color.name());
          //btn1->setStyleSheet(qss);

        ss << color.red() << " " << color.green() << " " << color.blue();
        str1 =  QString::fromStdString(ss.str());
        // makes text black\white to contrast background color:
        int r = (int)color.red();
        int g = (int)color.green();
        int b = (int)color.blue();
        int yiqSpace = ((r * 299) + (g * 587) + (b * 114)) / 1000;
        if (yiqSpace > 131)
        {
            textcolor= Qt::black;
        }
        else
        {
            textcolor = Qt::white;
        }
        label->setText(str1);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        btn1->setAutoFillBackground(true);
        label->setAutoFillBackground(true);
        label->setStyleSheet(qss);
        //edit label setting adding contrast fontcolor:
        QPalette palette(label->palette());
        palette.setColor(QPalette::WindowText, textcolor);
        label->setPalette(palette);

    }
   return(str1);
}

