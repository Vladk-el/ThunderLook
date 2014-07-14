#ifndef DETAILLEDEMAIL_H
#define DETAILLEDEMAIL_H

#include "../includes/smtpClient/src/mimemessage.h"
#include "sendnewemail.h"

#include <iostream>

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPixmap>
#include <QPushButton>

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
        void slot_answer();

    private:
        // MimeMessage
        //MimeMessage * message;

        // Layouts
        QVBoxLayout * layout_main;
        QFormLayout * layout_top;
        QHBoxLayout * layout_bottom;

        // Labels
        QLabel * label_object;
        QLabel * label_sender;
        QLabel * label_date;
        QLabel * label_to;
        QLabel * label_cc;
        QLabel * label_attachement;

        QTextEdit * label_corps;

        // QPushButton
        QPushButton * answer;


};

#endif // DETAILLEDEMAIL_H
