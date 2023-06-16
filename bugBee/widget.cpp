#include <QDebug>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QtSql>

#include "QSQLDbHelper.h"
#include "widget.h"
#include "ui_widget.h"
#include "Hfl.h"
#include "tbee.h"
#include "ball.h"
#include "mypoi.h"

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->resize(1200,820);
    this->setFixedSize(1200,820);
    ui->setupUi(this);
    scene = new CustomScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );

    scene->setSceneRect(0,0,1180,800);
    //scene->addPixmap(QPixmap(":/images/map.png"));
    QBrush backgroundImage=QBrush(QPixmap(":/images/map.png"));
    backgroundImage.setStyle(Qt::TexturePattern);
    scene->setBackgroundBrush(backgroundImage);

    Tbee *tbee = new Tbee();
    tbee->setPos(760,50);
    scene->addItem(tbee);
    connect(tbee,SIGNAL(mysignal(int,int)),this,SLOT(ball_emit(int,int)));
    connect(scene, &CustomScene::signalTargetCoordinate, tbee, &Tbee::slotTarget);
    connect(scene, &CustomScene::signalTargetCoordinate, tbee, &Tbee::slotSound);

    Hfl *hfl=new Hfl();
    int hfl_x =274; // ATT!!! used below in stuff placement method
    int hfl_y =466;
    hfl->setPos(hfl_x,hfl_y);
    hfl->setFlag(QGraphicsItem::ItemIsFocusable,true);
    hfl->setFlag(QGraphicsItem::ItemIsFocusScope,true);
    hfl->setXY(hfl_x,hfl_y);
    hfl->setScale(0.01);
    scene->addItem(hfl);
    hfl->setFocus();

    MyPoi *poi = NULL;
    qDebug() << "Compiled with Qt Version = " << QT_VERSION_STR;
 //   const char* driverName = "QPSQL";
 //   QSQLDbHelper* qSQLDbHelper = new QSQLDbHelper(driverName);
 //   QSqlDatabase* db = qSQLDbHelper->connect("localhost", "tatik", "tatik", "tatik");
    if(db_connect("localhost", "tatik", "tatik", "tatik")) {
       QSqlQuery query;
       query.setForwardOnly(true);
       if( !query.prepare(QString("SELECT * FROM qmap")) )
       {
           qDebug() <<"Error = " << query.lastError().text();
       }
  //     int queryResultRowCount = qSQLDbHelper->selectRowCountResult(query);
 //      qDebug() << "Initial Row Count = " << queryResultRowCount << "\n";
       if( !query.exec(QString
        ("SELECT qmap.person as owner, wood.color,address,x,y,r,age, sex,item,stuff.color as ccolor,pic FROM qmap,wood,stuff WHERE qmap.person=wood.person AND qmap.person =stuff.person ORDER BY qmap.person;")) )
       {
           qDebug() << " Error with myquery ";
       }
       QSqlRecord rec     = query.record();
       QString    tipname,name,color,sex;
       QString    address, age, smth, smthcolor,smthpic;
       int        poix, poiy, poir;
       QString oldname="";
       while (query.next()) {
            name  = query.value(rec.indexOf("owner")).toString();
            address  = query.value(rec.indexOf("address")).toString();
            poix = query.value(rec.indexOf("x")).toInt();
            poiy = query.value(rec.indexOf("y")).toInt();
            poir = query.value(rec.indexOf("r")).toInt();
            color  = query.value(rec.indexOf("color")).toString();
            sex  = query.value(rec.indexOf("sex")).toString();
            age = query.value(rec.indexOf("age")).toString();
            smth  = query.value(rec.indexOf("item")).toString();
            smthcolor = query.value(rec.indexOf("ccolor")).toString();
            smthpic = query.value(rec.indexOf("pic")).toString();
            if (age == "0") age = "unknown";
/*there is a small problem with this approach: it looks suspicious
when we use apparently null pointer. While it could be discerned that it should
never be null, WTF-moments are bad karma. It works, but could be better.
Right now a comment would suffice*/
            if (name==oldname) {
               tipname = tipname + "\n             " + smth + ", " + smthcolor;
               poi->setInfo(tipname);
               poi->myVector.push_back(smthpic);
           } else {
               tipname =  " \nAddress:  " + address + " \nColor:  " + color + " \nAge:  " + age //"Name:  "+ name +
                       + "\n\nStuff:  " + smth + ", " + smthcolor;
               poi = new MyPoi();
               poi->setPos(poix,poiy);
               poi->setXY(poix,poiy);
               poi->setName(name);
               poi->setInfo(tipname);
               poi->myVector.push_back(smthpic);
               //qDebug() << name << "  " << smthpic << " deb1" << poi->myVector.size();
               scene->addItem(poi);
               connect(poi,SIGNAL(signal1(int,int,QVector<QString>)),this, SLOT(slotFromPoi(int,int,QVector<QString>)));
               oldname=name;
            }//else from if(name==oldname)
        }//while(query.next)
    } else {
//       qDebug() << "Something went Wrong:" << db->lastError().text();
//we don't have db here; just exiting the application
        QApplication::exit(1);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ball_emit(int x, int y)
{
    Ball *ball = new Ball();
    ball->setPos(x,y);
    scene->addItem(ball);
}

void Widget::slotFromPoi(int x, int y, QVector<QString> myVector)
{
    int count=myVector.size();
    for (int i=1; i<count;i++) {
        QPixmap temp= QPixmap(":/images/" + myVector[i] ).scaledToWidth(40);
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(temp);
        item->setPos(randomBetween(x-50, x), randomBetween(y-50, y));
        item->setFlag(QGraphicsItem::ItemIsMovable,true);
        item->setFlag(QGraphicsItem::ItemIsSelectable,true);
        item->setSelected(true);
        scene->addItem(item);
        QMessageBox about("Stuff item","Owner - " + myVector[0], QMessageBox::NoIcon,
            QMessageBox::Ok| QMessageBox::Default,
            QMessageBox::NoButton,
            QMessageBox::NoButton);
     // about.setText(myVector[0]);
        about.setStandardButtons(QMessageBox::Ok);
        about.setIconPixmap(QPixmap(":/images/" + myVector[i]));
        about.exec();
        about.show();
        //scene->setFocus();
        if(scene->itemAt(274,466,QTransform())) scene->itemAt(274,466,QTransform())->setFocus(); // if added;
    }
}
