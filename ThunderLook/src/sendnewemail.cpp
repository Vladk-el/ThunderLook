#include "sendnewemail.h"

using namespace std;

SendNewEmail::SendNewEmail()
{
    setMainIHM();
}

SendNewEmail::SendNewEmail(QString to, QString cc, QString obj, QString content)
{
    setMainIHM();
    setContentToAnswer(to, cc, obj, content);
}

void SendNewEmail::setMainIHM(){

    setMinimumSize(1000, 600);
    setWindowTitle(tr("Nouveau message"));
    settings = new QSettings("../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);

    layout_main = new QVBoxLayout;

    layout_top = new QHBoxLayout;
    button_send = new QPushButton(tr("Envoyer"));
    button_send->setIcon(QIcon(":/data/img/send_mail/send_mail-48.png"));

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


    text_content = new QTextEdit();

    layout_main->addLayout(layout_top);
    layout_main->addWidget(text_content);

    setLayout(layout_main);

    setSlotsConnexions();
}


void SendNewEmail::setSlotsConnexions(){

    connect(button_send, SIGNAL(clicked()), this, SLOT(send()));
    connect(line_to, SIGNAL(textChanged(QString)), this, SLOT(verifyLineTo()));
    connect(line_copy, SIGNAL(textChanged(QString)), this, SLOT(verifyLineCopy()));
}

bool SendNewEmail::isEmailAddress(QString addr){
    if ( addr.length() == 0 ) return false;

    QString strPatt = "\\b[A-Z0-9a-z._%+-]+@[A-Z0-9a-z.-]+\\.[A-Za-z]{2,4}\\b";
    QRegExp rx(strPatt);
    return rx.exactMatch(addr);
}

void SendNewEmail::verifyLineAddress(QLineEdit * line){
    std::cout << "End editing" << std::endl;
    if(!(isEmailAddress(line->text()))){
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::red);
        line->setPalette(palette);
    }
    else{
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::green);
        line->setPalette(palette);
    }
}

// Slots
void SendNewEmail::send(){
    cout << "send()" << endl;

    if(settings->value("Send/smtp_security").toInt() == 1)
        smtp = new SmtpClient(settings->value("Send/smtp_server").toString(), settings->value("Send/smtp_port").toInt(), SmtpClient::SslConnection);
    else
        smtp = new SmtpClient(settings->value("Send/smtp_server").toString(), settings->value("Send/smtp_port").toInt());

    smtp->setUser(settings->value("Send/smtp_user").toString());
    smtp->setPassword(settings->value("Send/smtp_password").toString());

    MimeMessage message;

    message.setSender(new EmailAddress(
                          settings->value("Account/user_email").toString(),
                          settings->value("Account/user_name").toString()
                          )
                      );

    message.addRecipient(new EmailAddress(line_to->text(), ""));
    if(line_copy->text() != NULL)
        message.addRecipient(new EmailAddress(line_copy->text(), ""));

    message.setSubject(line_subject->text());

    MimeText * text = new MimeText;

    text->setText(text_content->toPlainText());

    message.addPart(text);

    int random = qrand() % ((999999 + 1) - 1) + 1;

    message.setIndice(QString::number(random));
    message.setText(text_content->toPlainText());
    message.setHtml(text_content->toPlainText());

    QDateTime dateTime = QDateTime::currentDateTime();
    message.setDate(dateTime.toString());

    SqlLiteHelper * slh = new SqlLiteHelper();
    slh->insertEmail(&message,2);

    smtp->connectToHost();
    smtp->login();
    smtp->sendMail(message);
    smtp->quit();
    close();
}

void SendNewEmail::verifyLineTo(){
    verifyLineAddress(line_to);
}

void SendNewEmail::verifyLineCopy(){
    verifyLineAddress(line_copy);
}

void SendNewEmail::setContentToAnswer(QString & to, QString & cc, QString & obj, QString & content){

    line_to->setText(to);
    line_copy->setText(cc);
    line_subject->setText("TR: " + obj);
    text_content->setText("\n\n --------------------------------------- \n\n" + content);
}
