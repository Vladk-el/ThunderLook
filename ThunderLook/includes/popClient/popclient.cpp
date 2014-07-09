#include "popclient.h"
#include <QByteArray>
#include <QStringList>

using namespace std;

PopClient::PopClient(QObject *parent) :
    QObject(parent)
{

}

PopClient::~PopClient()
{
    quit();
}

PopClient::PopClient(const QString &host, int port, ConnectionType connectionType)
{
    this->host = host;
    this->port = port;

    this->connectionTimeout = 50000000;
    this->responseTimeout = 999999999;
    this->sendMessageTimeout = 70000000000;

    this->nbTotalEmail = 0;

    setConnectionType(connectionType);
}

void PopClient::getNumberEmailsToRead()
{
    sendMessage("stat");
    waitForResponse();

    QStringList listLineEmail = responseText.split(" ");

    nbTotalEmail = listLineEmail[1].toInt();

    qDebug() << "NbTotal email : " << nbTotalEmail << endl;
}

 QList<MimeMessage*> PopClient::getAllEmails()
{
    getNumberEmailsToRead();
    QList<MimeMessage*> emails;

    for(int i = 1 ; i <= nbTotalEmail ; i++)
    {
        MimeMessage * email = getEmail(i);
        emails << email;
    }

    return emails;
}

int PopClient::getNbTotalEmail()
{
    return nbTotalEmail;
}

MimeMessage * PopClient::getEmail(int id)
{
    MimeMessage * email = new MimeMessage(true);

    QString indice;
    indice.setNum(id);

    try
    {
        sendMessage("RETR " + indice);
        waitForResponse();
    }
    catch(SendMessageTimeoutException e)
    {
        qDebug() << "Exception : " << endl;
        return email;
    }

    if(responseText.length() > 0)
    {
        QString to;
        QString cc;

        QStringList listLineEmail = responseText.split("\r\n");

        if(listLineEmail.length() < 20)
        {
            sendMessage("RETR " + indice);
            waitForResponse();

            listLineEmail = responseText.split("\r\n");
        }

        for(int i = 0 ; i < listLineEmail.length() ; i++)
        {
            if(listLineEmail[i].startsWith("To:"))
            {
                to = listLineEmail[i];
                for(int j = i + 1 ; j < listLineEmail.length() ; j++)
                {
                    if(listLineEmail[j].startsWith("	"))
                        to += listLineEmail[j];

                    else
                    {
                        i = j-1 ;
                        break;
                    }
                }

                to = to.mid(3);

                QStringList listTo = to.split(",");

                for(int i = 0 ; i < listTo.length() ; i++)
                {
                    listTo[i] = listTo[i].replace("\t","").replace(" ","");

                    QString name;
                    int first;
                    if((first = listTo[i].indexOf("<")) != -1)
                    {
                        name = listTo[i].mid(0,first);

                        int last = listTo[i].indexOf(">");
                        listTo[i] = listTo[i].mid(first+1,(last-first) - 2);
                    }

                    email->addRecipient(new EmailAddress(listTo[i],name));
                }
            }

            if(listLineEmail[i].startsWith("Message-ID"))
            {
                email->setIndice(listLineEmail[i]);
                for(int j = i+1 ; j < listLineEmail.length() ; j++)
                {
                    if(listLineEmail[j].startsWith("	"))
                    {
                        QString concat = email->getIndice() + listLineEmail[j];
                        email->setIndice(concat);
                    }

                    else
                    {
                        i = j-1 ;
                        break;
                    }
                }

                email->setIndice(email->getIndice().mid(13,email->getIndice().length() - 14));
            }

            if(listLineEmail[i].startsWith("Subject:"))
            {
                QString subject = listLineEmail[i];
                for(int j = i+1 ; j < listLineEmail.length() ; j++)
                {
                    if(listLineEmail[j].startsWith("	"))
                        subject += listLineEmail[j];

                    else
                    {
                        i = j-1 ;
                        break;
                    }
                }

                email->setSubject(subject.mid(9,subject.length() - 9));
            }

            if(listLineEmail[i].startsWith("Cc:"))
            {
                    cc = listLineEmail[i];
                    for(int j = i + 1 ; j < listLineEmail.length() ; j++)
                    {
                        if(listLineEmail[j].startsWith("	"))
                            cc += listLineEmail[j];

                        else
                        {
                            i = j-1 ;
                            break;
                        }
                    }

                    cc = cc.mid(3);

                    QStringList listCc = cc.split(",");

                    for(int i = 0 ; i < listCc.length() ; i++)
                    {
                        listCc[i] = listCc[i].replace("\t","").replace(" ","");

                        QString name;
                        int first;
                        if((first = listCc[i].indexOf("<")) != -1)
                        {
                            name = listCc[i].mid(0,first);

                            int last = listCc[i].indexOf(">");
                            listCc[i] = listCc[i].mid(first+1,(last-first) - 1);
                        }

                        email->addCc(new EmailAddress(listCc[i],name));
                    }
            }

            if(listLineEmail[i].startsWith("From:"))
            {
                QString from = listLineEmail[i];
                QString fromName;

                for(int j = i+1 ; j < listLineEmail.length() ; j++)
                {
                    if(listLineEmail[j].startsWith("	"))
                        from += listLineEmail[j];

                    else
                    {
                        i = j-1 ;
                        break;
                    }
                }

                from = from.mid(5,from.length() - 5);
                int first;
                if((first = from.indexOf("<") + 1) != - 1)
                {
                    fromName = from.mid(0,first);
                    int last = from.indexOf(">");
                    from = from.mid(first,last-first);
                }

                email->setSender(new EmailAddress(from,fromName));
            }

            if(listLineEmail[i].startsWith("Date:"))
            {
                email->setDate(listLineEmail[i]);
                for(int j = i+1 ; j < listLineEmail.length() ; j++)
                {
                    if(listLineEmail[j].startsWith("	"))
                    {
                        QString concat = email->getDate() + listLineEmail[j];
                        email->setDate(concat);
                    }

                    else
                    {
                        i = j-1 ;
                        break;
                    }
                }

                email->setDate(email->getDate().mid(6,email->getDate().length() - 6));
            }

            if(listLineEmail[i].startsWith("Content-Type: text/html")&& !listLineEmail[i].contains("name"))
            {
                QString html = listLineEmail[i+1];

                for(int j = i+2 ; j < listLineEmail.length() ; j++)
                {
                    if(!listLineEmail[j].startsWith("--"))
                        html += listLineEmail[j];
                    else
                    {
                        i = j-1 ;
                        break;
                    }
                }

                MimeHtml * text = new MimeHtml;
                text->setHtml(html);

                email->addPart(text);
            }

            if(listLineEmail[i].startsWith("Content-Disposition: "))
            {
                int startName = listLineEmail[i-1].indexOf("name=");

                QString plain = listLineEmail[i+3];
                QString filename = listLineEmail[i-1].mid(startName + 6 ,((listLineEmail[i-1].length()-1) - startName) + 6);
                QString contentType = listLineEmail[i-1].mid(14,(listLineEmail[i-1].indexOf(";") - 14));
                filename = filename.replace("\"","");

                qDebug() << "contentType : " << contentType << endl;
                for(int j = i+4 ; j < listLineEmail.length() ; j++)
                {
                    if(!listLineEmail[j].startsWith("--"))
                    {
                        plain += listLineEmail[j];
                    }

                    else
                    {
                        qDebug() << "A j = " << j << endl;
                        i = j-1 ;
                        break;
                    }
                }

                // Decoder piece jointes
                QByteArray byteArray = QByteArray::fromBase64(plain.toUtf8());
                QString string(byteArray);
                qDebug() << "String : " << string << endl;

                QFile file("test.txt");
                file.open( QIODevice::WriteOnly );
                file.write(string.toUtf8());
                file.close();

                MimeAttachment * attachment = new MimeAttachment(plain.toUtf8(),filename);
                attachment->setContentType("text/plain");
                email->addPart(attachment);
            }

            if(listLineEmail[i].startsWith("Content-Type: text/plain") && !listLineEmail[i].contains("name"))
            {
                QString plain = listLineEmail[i+1];

                for(int j = i+2 ; j < listLineEmail.length() ; j++)
                {
                    if(!listLineEmail[j].startsWith("--"))
                        plain += listLineEmail[j];

                    else
                    {
                        i = j-1 ;
                        break;
                    }
                }

                MimeText * text = new MimeText;
                text->setText(plain);
                email->addPart(text);
            }
        }
    }

    return email;
}

void PopClient::quit()
{
    sendMessage("quit");
    socket->close();
}

void PopClient::waitForResponse()
{
    QString response;
    responseText.clear();

    do
    {
        int line = 0;
        if (!socket->waitForReadyRead(responseTimeout))
        {
            return ;
        }

        while (socket->canReadLine())
        {
            QByteArray array = socket->readAll();

            for(int i = 0 ; i < array.length() ; i++)
                responseText.append(array.at(i));
            //response = socket->readLine();
            //responseText.append(response);

            responseCode = responseText[0];

            if(line == 0)
            {
                if(responseCode != "+")
                    return;
            }

            line++;
        }

        return;
    }
    while (true);
}

void PopClient::sendMessage(const QString &text) throw (SendMessageTimeoutException)
{
    socket->write(text.toUtf8() + "\r\n");
    if (! socket->waitForBytesWritten(sendMessageTimeout))
    {
        throw SendMessageTimeoutException();
    }
}

bool PopClient::login()
{
    sendMessage("user " + user);
    waitForResponse();

    if (responseCode != "+")
        return false;

    sendMessage("pass " + password);
    waitForResponse();

    if (responseCode != "+")
        return false;

    return true;
}

void PopClient::setConnectionType(ConnectionType ct)
{
    this->connectionType = ct;

    switch (connectionType)
    {
    case TcpConnection:
        socket = new QTcpSocket(this);
        break;
    case SslConnection:
    case TlsConnection:
        socket = new QSslSocket(this);
    }
}

bool PopClient::connectToHost()
{
    switch (connectionType)
    {
    case TlsConnection:
    case TcpConnection:
        socket->connectToHost(host, port);
        break;
    case SslConnection:
        ((QSslSocket*) socket)->connectToHostEncrypted(host, port);
        break;
    }

    if (!socket->waitForConnected(connectionTimeout))
    {
        throw ErrorResponseException();
        return false;
    }

    waitForResponse();

    if (responseCode != "+")
    {
        //throw ErrorResponseException();
        return false;
    }

    return true;
}

PopClient::ConnectionType PopClient::getConnectionType() const
{
    return connectionType;
}

void PopClient::setUser(const QString &user)
{
    this->user = user;
}

void PopClient::setPassword(const QString &password)
{
    this->password = password;
}

void PopClient::setHost(QString &host)
{
    this->host = host;
}

void PopClient::setPort(int port)
{
    this->port = port;
}

const QString& PopClient::getHost() const
{
    return this->host;
}

const QString& PopClient::getUser() const
{
    return this->user;
}

const QString& PopClient::getPassword() const
{
    return this->password;
}

int PopClient::getPort() const
{
    return this->port;
}
