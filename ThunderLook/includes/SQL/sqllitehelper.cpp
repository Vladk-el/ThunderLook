#include "sqllitehelper.h"
#include <QDebug>
#include <QDir>

using namespace std;

SqlLiteHelper::SqlLiteHelper(QObject *parent) :
    QObject(parent)
{

}

bool SqlLiteHelper::insertUser(QString addr)
{

}

QList<MimeMessage *> SqlLiteHelper::getAllEmails(int id_folder)
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
    QSqlQuery queryAttachment;

    //query.exec("SELECT * FROM Emails WHERE id_folder = '" + QString::number(id_folder) + "'");
    query.exec("SELECT * FROM Emails WHERE id_folder = '" + QString::number(id_folder) + "' order by id_email desc");

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

        email->setText(query.value(7).toString());
        email->setHtml(query.value(8).toString());

        // Add senders
        QSqlQuery sender;
        sender.exec("SELECT * from Sender where id_email = '" + query.value(2).toString() + "'");

        while(sender.next())
        {
            email->setSender(new EmailAddress(sender.value(3).toString(),sender.value(2).toString()));
        }

        // Add recipients
        QSqlQuery recipients;
        recipients.exec("SELECT * FROM Recipients where id_email = '" + query.value(2).toString() + "'");
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

        email->setDate(query.value(4).toString());

        queryAttachment.prepare("SELECT * FROM Attachments WHERE id_email = :id_email");
        queryAttachment.bindValue(":id_email", email->getIndice());
        queryAttachment.exec();
        QSqlRecord recAttachment = queryAttachment.record();

        while(queryAttachment.next())
        {
            MimeAttachment * attachment = new MimeAttachment(queryAttachment.value(recAttachment.indexOf("data")).toByteArray(),QString(queryAttachment.value(recAttachment.indexOf("filename")).toString()));
            attachment->setContentType(queryAttachment.value(recAttachment.indexOf("data")).toString());

            email->addAttachment(attachment);
        }

        emails << email;
    }

    return emails;
}

bool SqlLiteHelper::insertEmail(MimeMessage * mail,int id_folder)
{
    if (mail->getSender().getAddress() != "")
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
        query.prepare("INSERT INTO Emails (indice, subject, date,content,text,html,id_folder) "
                      "VALUES (:indice, :subject, :date,:content,:text,:html,:id_folder)");
        query.bindValue(":indice", mail->getIndice());
        query.bindValue(":subject", mail->getSubject());
        query.bindValue(":date",mail->getDate());
        query.bindValue(":content", mail->getContent().toString());
        query.bindValue(":text", mail->getText());
        query.bindValue(":html", mail->getHtml());
        query.bindValue(":id_folder", QString::number(id_folder));
        // query.bindValue(":isRead", QString::number(0));
        query.exec();

        QString test(query.lastError().text());

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

        if(mail->getAttachment().count() > 0)
        {
            for(int i = 0 ;i < mail->getAttachment().count() ;i++)
            {
                query.prepare("INSERT INTO Attachments (id_email, filename, data,content_type) VALUES (:id_email, :filename, :data,:content_type)");

                query.bindValue(":id_email", mail->getIndice());
                query.bindValue(":filename", mail->getAttachment().at(i)->getFilename());
                query.bindValue(":data",mail->getAttachment().at(i)->getStream());
                query.bindValue(":content_type",mail->getAttachment().at(i)->getContentType());

                query.exec();
            }
        }

        return true;
    }

    return false;
}
