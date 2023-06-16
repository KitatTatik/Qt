#ifndef QSQLDBHELPER_H
#define QSQLDBHELPER_H

/*
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
*/
class QString;
bool db_connect( const QString& server,
             const QString& databaseName,
             const QString& userName,
             const QString& password );

#endif // QSQLDBHELPER_H
