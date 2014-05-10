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

class SendNewEmail : public QWidget
{

    Q_OBJECT

    public:
        SendNewEmail();

        void setMainIHM();
        void setSlotsConnexions();

    public slots:
        void send();

    private:
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

};

#endif // SENDNEWEMAIL_H
