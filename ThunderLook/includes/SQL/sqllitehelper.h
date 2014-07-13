#ifndef SQLLITEHELPER_H
#define SQLLITEHELPER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql>

#include "../smtpClient/src/mimemessage.h"

using namespace std;

class SqlLiteHelper : public QObject
{
    enum RecipientType {
        To,
        Cc,
        Bcc
    };

public:
    explicit SqlLiteHelper(QObject *parent = 0);
    bool insertUser(QString addr);
    bool insertEmail(MimeMessage * mail,int id_folder);
    QList<MimeMessage *> getAllEmails(int id_folder);
    QSqlDatabase db;
};

#endif // SQLLITEHELPER_H
