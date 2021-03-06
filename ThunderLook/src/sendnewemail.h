#ifndef SENDNEWEMAIL_H
#define SENDNEWEMAIL_H

#include "../includes/smtpClient/src/SmtpMime"
#include "../includes/SQL/sqllitehelper.h"

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSettings>

#include "addrecipients.h"

class SendNewEmail : public QWidget
{

    Q_OBJECT

    public:
        SendNewEmail();
        SendNewEmail(QString, QString, QString, QString);

        void setMainIHM();
        void setSlotsConnexions();
        bool isEmailAddress(QString);
        void verifyLineAddress(QLineEdit *);
        void setContentToAnswer(QString &, QString &, QString &, QString &);

        enum RecipientType {
            To,                 // primary
            Cc,                 // carbon copy
            Bcc                 // blind carbon copy
        };

    public slots:
        void addTo();
        void addCopy();
        void send();
        void verifyLineTo();
        void verifyLineCopy();

    private:
        // QSettings
        QSettings * settings;

        // Layouts
        QVBoxLayout * layout_main;
        QHBoxLayout * layout_top;
        QFormLayout * layout_form;

        // QWidgets
        QWidget * widget_layout_form_container;

        // Buttons
        QPushButton * button_send;
        QPushButton * button_to;
        QPushButton * button_copy;

        // QLineEdits
        QLineEdit * line_to;
        QLineEdit * line_copy;
        QLineEdit * line_subject;

        // QTextEdit
        QTextEdit * text_content;

        // SmtpClient
        SmtpClient * smtp;

};

#endif // SENDNEWEMAIL_H
