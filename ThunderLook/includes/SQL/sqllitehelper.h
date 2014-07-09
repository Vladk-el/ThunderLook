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
        To,                 // primary
        Cc,                 // carbon copy
        Bcc                 // blind carbon copy
    };

public:
    explicit SqlLiteHelper(QObject *parent = 0);
    bool insertUser(QString addr);
    bool insertEmail(MimeMessage * mail);
    QList<MimeMessage *> getAllEmails();
    QSqlDatabase db;
};

#endif // SQLLITEHELPER_H
