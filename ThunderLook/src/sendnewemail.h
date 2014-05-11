#ifndef SENDNEWEMAIL_H
#define SENDNEWEMAIL_H

#include "../includes/smtpClient/src/SmtpMime"

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

class SendNewEmail : public QWidget
{

    Q_OBJECT

    public:
        SendNewEmail();

        void setMainIHM();
        void setSlotsConnexions();
        bool isEmailAddress(QString);
        void verifyLineAddress(QLineEdit *);

    public slots:
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
