#include "sqllitehelper.h"
#include <QDebug>
#include <QDir>

using namespace std;

SqlLiteHelper::SqlLiteHelper(QObject *parent) :
    QObject(parent)
{

}

QList<MimeMessage *> SqlLiteHelper::getAllEmails()
{
    QList<MimeMessage *> emails;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if (!db.open())
    {
        qDebug() << "Impossible de se connecter à la base de données." << endl;
        return emails;
    }

    qDebug() << "Ok Connection etablie" << endl;

    QSqlQuery query;

    query.exec("SELECT * FROM Emails");

    while (query.next())
    {
        qDebug() << "Ok entrer dans la boucle" << endl;
        MimeMessage * email = new MimeMessage;

        qDebug() << " 0 : " << query.value(0).toInt();
        qDebug() << " 1 : " << query.value(1).toInt();
        qDebug() << " 2 : " << query.value(2).toString();

        // Add Subject
        email->setSubject(query.value(3).toString());

        // Add Content
        MimeText * text = new MimeText;
        text->setText(query.value(6).toString());
        email->addPart(text);

        // Add senders
        QSqlQuery sender;
        sender.exec("SELECT * from Sender where id_email = '" + query.value(2).toString() + "'");

        while(sender.next())
        {
            email->setSender(new EmailAddress(sender.value(3).toString(),sender.value(2).toString()));
        }

        // Add recipients
        QSqlQuery recipients;
        recipients.exec("SELECT * FROM Recipient where id_email = '" + query.value(2).toString() + "'");

        while(recipients.next()) // get all recipients
        {
            if(recipients.value(4).toInt() == 0) // TO
            {
                email->addRecipient(new EmailAddress(recipients.value(3).toString(),recipients.value(2).toString()));
            }

            else if(recipients.value(4).toInt() == 1) // CC
            {
                email->addCc(new EmailAddress(recipients.value(3).toString(),recipients.value(2).toString()));
            }

            else // BCC
            {
                email->addBcc(new EmailAddress(recipients.value(3).toString(),recipients.value(2).toString()));
            }
        }

        emails << email;
    }

    return emails;
}

bool SqlLiteHelper::insertEmail(MimeMessage * mail)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    if (!db.open())
    {
        qDebug() << "Impossible de se connecter à la base de données." << endl;
        return false;
    }

    qDebug() << "Ok Connection etablie" << endl;

    QSqlQuery query;

    // INSERT EMAIL
    query.prepare("INSERT INTO Emails (indice, subject, date,content) "
                       "VALUES (:indice, :subject, :date,:content)");
    query.bindValue(":indice", mail->getIndice());
    query.bindValue(":subject", mail->getSubject());
    query.bindValue(":date",mail->getDate());
    query.bindValue(":content", mail->getContent().toString());
    query.exec();

    // INSERT SENDER
    query.prepare("INSERT INTO Sender (id_email, address_sender, name_sender) "
                       "VALUES (:id_email, :address_sender, :name_sender)");

    query.bindValue(":id_email", mail->getIndice());
    query.bindValue(":address_sender", mail->getSender().getAddress());
    query.bindValue(":name_sender",mail->getSender().getName());

    query.exec();

    // INSERT RECIPIENTS CC
    QList<EmailAddress*>::const_iterator it, itEnd;

    for (it = mail->getRecipients(MimeMessage::Cc).begin(), itEnd = mail->getRecipients(MimeMessage::Cc).end();
         it != itEnd; ++it)
    {
        query.prepare("INSERT INTO Recipients (id_email, name, address,recipient_type) VALUES (:id_email, :name, :address,:recipient_type)");

        query.bindValue(":id_email", mail->getIndice());
        query.bindValue(":address", (*it)->getAddress());
        query.bindValue(":name",(*it)->getName());
        query.bindValue(":recipient_type","1");

        query.exec();
    }

    for (it = mail->getRecipients(MimeMessage::To).begin(), itEnd = mail->getRecipients(MimeMessage::To).end();
         it != itEnd; ++it)
    {
        query.prepare("INSERT INTO Recipients (id_email, name, address,recipient_type) VALUES (:id_email, :name, :address,:recipient_type)");

        query.bindValue(":id_email", mail->getIndice());
        query.bindValue(":address", (*it)->getAddress());
        query.bindValue(":name",(*it)->getName());
        query.bindValue(":recipient_type","0");

        query.exec();
    }

    for (it = mail->getRecipients(MimeMessage::Bcc).begin(), itEnd = mail->getRecipients(MimeMessage::Bcc).end();
         it != itEnd; ++it)
    {
        query.prepare("INSERT INTO Recipients (id_email, name, address,recipient_type) VALUES (:id_email, :name, :address,:recipient_type)");

        query.bindValue(":id_email", mail->getIndice());
        query.bindValue(":address", (*it)->getAddress());
        query.bindValue(":name",(*it)->getName());
        query.bindValue(":recipient_type","3");

        query.exec();
    }

    return true;
}
