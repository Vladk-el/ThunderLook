#include "sendnewemail.h"

using namespace std;

SendNewEmail::SendNewEmail()
{
    setMainIHM();
}

void SendNewEmail::setMainIHM(){

    setMinimumSize(1000, 600);

    layout_main = new QVBoxLayout;

        layout_top = new QHBoxLayout;
            button_send = new QPushButton(tr("Envoyer"));

            layout_form = new QFormLayout;
                button_to = new QPushButton(tr("À"));
                button_copy = new QPushButton(tr("Cc"));
                line_to = new QLineEdit;
                line_copy = new QLineEdit;
                line_subject = new QLineEdit;

                layout_form->addRow(button_to, line_to);
                layout_form->addRow(button_copy, line_copy);
                layout_form->addRow(tr("Objet :"), line_subject);

            layout_top->addWidget(button_send);
            layout_top->addLayout(layout_form);


        text_content = new QTextEdit;

        layout_main->addLayout(layout_top);
        layout_main->addWidget(text_content);

    setLayout(layout_main);

    setSlotsConnexions();
}


void SendNewEmail::setSlotsConnexions(){

    connect(button_send, SIGNAL(clicked()), this, SLOT(send()));
}

// Problème ici
void SendNewEmail::send(){
    cout << "send()" << endl;

    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    smtp.setUser("eliott.laversin@gmail.com");
    smtp.setPassword("chajotensim");

    MimeMessage message;

    message.setSender(new EmailAddress("eliott.laversin@gmail.com", "Eliott Laversin"));

    message.addRecipient(new EmailAddress(line_to->text(), ""));
    if(line_copy->text() != NULL)
        message.addRecipient(new EmailAddress(line_copy->text(), ""));

    message.setSubject(line_subject->text());

    MimeText * text;

    text->setText(text_content->toPlainText());

    message.addPart(text);

    smtp.connectToHost();
    smtp.login();
    smtp.sendMail(message);
    smtp.quit();
}










