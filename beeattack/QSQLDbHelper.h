#ifndef QSQLDBHELPER_H
#define QSQLDBHELPER_H
#include <QtSql>
#include <QString>
#include <QDebug>

class QSQLDbHelper
{
public:
    QSQLDbHelper(const char* driver);
    ~QSQLDbHelper();
    QSqlDatabase* connect( const QString& server,
                           const QString& databaseName,
                           const QString& userName,
                           const QString& password );
    void disConnect();

    int selectRowCountResult(QSqlQuery* query);

private:
    QSqlDatabase* db;
};

#endif // QSQLDBHELPER_H
