#ifndef POPCLIENT_H
#define POPCLIENT_H

#include <QObject>
#include <QtNetwork/QSslSocket>
#include <iostream>
#include <vector>
#include "../smtpClient/src/mimemessage.h"
#include "../smtpClient/src/emailaddress.h"
#include "../smtpClient/src/mimetext.h"
#include "../smtpClient/src/mimeattachment.h"

using namespace std;

class PopClient : public QObject
{
    Q_OBJECT
public:

    enum ConnectionType
    {
        TcpConnection,
        SslConnection,
        TlsConnection
    };

    PopClient(QObject *parent = 0);
    PopClient(const QString & host = "locahost", int port = 995, ConnectionType ct = TcpConnection);
    ~PopClient();

    const QString& getHost() const;
    void setHost(QString &host);

    int getPort() const;
    void setPort(int port);

    const QString & getUser() const;
    void setUser(const QString &host);

    const QString & getPassword() const;
    void setPassword(const QString &password);

    ConnectionType getConnectionType() const;
    void setConnectionType(ConnectionType ct);

    int getNbTotalEmail();

    QTcpSocket* getSocket();
    bool connectToHost();
    bool login();

    MimeMessage * getEmail(int id);
    QList<MimeMessage*> getAllEmails();
    void getNumberEmailsToRead();

    void quit();

private:
    QTcpSocket *socket;
    QString host;
    int port;
    QString user;
    QString password;

    int connectionTimeout;
    int responseTimeout;
    int sendMessageTimeout;
    int nbTotalEmail;

    ConnectionType connectionType;

    QString responseText;
    QString responseCode;

    class ErrorResponseException {};
    class ResponseTimeoutException {};
    class SendMessageTimeoutException {};


    void waitForResponse();
    void sendMessage(const QString &text) throw (SendMessageTimeoutException);

};

#endif // POPCLIENT_H
