#include <QtSql>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "QSQLDbHelper.h"
/*
QSQLDbHelper::QSQLDbHelper(const char* driver)
{
    db = new QSqlDatabase( QSqlDatabase::addDatabase(driver) );
}

QSQLDbHelper::~QSQLDbHelper()
{
    qDebug() << "Called Destructor!";
    delete db;
}

QSqlDatabase* QSQLDbHelper::connect( const QString& server,
                                     const QString& databaseName,
                                     const QString& userName,
                                     const QString& password )
{
    db->setConnectOptions();
    db->setHostName(server);
    db->setDatabaseName(databaseName);
    db->setUserName(userName);
    db->setPassword(password);

    if(db->open()) {
        return db;
    }
    else {
        QSqlError error=db->lastError();
        QMessageBox msgBox;
        msgBox.setText(error.text());
        msgBox.exec();

        return NULL;
    }
}

int QSQLDbHelper::selectRowCountResult(QSqlQuery* query)
{
    bool queryRes = query->exec();
    if (query->lastError().type() != QSqlError::NoError || !queryRes)
    {
        qDebug() << query->lastError().text();
        return -1;
    }

    int recordCount = 0;
    while (query->next())
    {
        ++recordCount;
    }

    return recordCount;
}

void QSQLDbHelper::disConnect()
{
    qDebug() << "Disconnected From Database!";
    db->close();
}
*/
bool db_connect( const QString& server,
                const QString& databaseName,
                const QString& userName,
                const QString& password )
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setConnectOptions();
    db.setHostName(server);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);

    if(db.open()) {
        return true;
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(db.lastError().text());
        msgBox.exec();
        return false;
    }

}
