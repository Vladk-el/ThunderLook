#ifndef DETAILLEDEMAIL_H
#define DETAILLEDEMAIL_H

#include "../includes/smtpClient/src/mimemessage.h"

#include <iostream>

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPixmap>

class DetailledEmail : public QWidget
{
    Q_OBJECT

    public:
        DetailledEmail();
        DetailledEmail(MimeMessage *);

        void setConstraints();
        void setIHM(MimeMessage *);

        void update(MimeMessage *);

    signals:

    public slots:

    private:
        // MimeMessage
        //MimeMessage * message;

        // Layouts
        QVBoxLayout * layout_main;
        QFormLayout * layout_top;

        // Labels
        QLabel * label_object;
        QLabel * label_sender;
        QLabel * label_date;
        QLabel * label_to;
        QLabel * label_cc;
        QLabel * label_attachement;

        QTextEdit * label_corps;


};

#endif // DETAILLEDEMAIL_H
