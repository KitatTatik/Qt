#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
#include <limits>
#include <QStandardItemModel>
#include <QStandardItem>


QT_BEGIN_NAMESPACE
using namespace std;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
   //QStandardItemModel *model;
    };


#endif // MAINWINDOW_H
