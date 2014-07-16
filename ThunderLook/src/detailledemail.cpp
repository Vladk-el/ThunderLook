#include "detailledemail.h"

using namespace std;


DetailledEmail::DetailledEmail()
{
    show();
    alive = false;
}

DetailledEmail::DetailledEmail(MimeMessage * message){

    setConstraints();
    setIHM(message);
    setAlive();
    show();

}

void DetailledEmail::setConstraints(){
    //setMinimumSize(Qt::MaximumSize);

}

void DetailledEmail::setIHM(MimeMessage * message){

    QString style_label("border: 1px solid black;");

    layout_main = new QVBoxLayout;

        layout_top = new QFormLayout;
            label_object = new QLabel("");
                label_object->setStyleSheet(style_label);
            label_sender = new QLabel("");
                label_sender->setStyleSheet(style_label);
            label_date = new QLabel("");
                label_date->setStyleSheet(style_label);
            label_to = new QLabel("");
                label_to->setStyleSheet(style_label);
            label_attachement = new QLabel("");
            label_cc = new QLabel("");
                label_cc->setStyleSheet(style_label);
            label_attachement = new QLabel("");
                label_attachement->setStyleSheet(style_label);

            layout_top->addRow(tr("Objet"), label_object);
            layout_top->addRow(tr("Expéditeur"), label_sender);
            layout_top->addRow(tr("Date"), label_date);
            layout_top->addRow(tr("Destinataire(s)"), label_to);
            layout_top->addRow(tr("Destinataire(s) - Cc"), label_cc);
            button_attachement = new QPushButton(tr("Pièce(s) jointe(s)"));
            layout_top->addRow(button_attachement, label_attachement);

        label_corps = new QTextEdit(message->getContent().toString());
            label_corps->setEnabled(false);

        layout_bottom = new QHBoxLayout;
            layout_bottom->setAlignment(Qt::AlignRight);
            answer = new QPushButton(tr("Répondre"));

            layout_bottom->addWidget(answer);


        layout_main->addLayout(layout_top);
        layout_main->addWidget(label_corps);
        layout_main->addLayout(layout_bottom);

        QObject::connect(answer, SIGNAL(clicked()), this, SLOT(slot_answer()));

        update(message);

    setLayout(layout_main);
}

void DetailledEmail::update(MimeMessage * message){
    label_object->setText(message->getSubject());
    label_sender->setText(message->getSender().getName());
    label_date->setText(message->getDate());
    label_to->setText("");
    label_cc->setText("");

    if(message->getRecipients(MimeMessage::To).size() > 0){
        cout << "MimeMessage::To.size() : " << message->getRecipients(MimeMessage::To).size() << endl;
        for(int i = 0; i < message->getRecipients(MimeMessage::To).size(); i++){
            if(label_to->text().size() > 0)
                label_to->setText(label_to->text().append(","));
            label_to->setText(label_to->text().append(message->getRecipients(MimeMessage::To).at(i)->getAddress()));
        }
    }

    if(message->getRecipients(MimeMessage::Cc).size() > 0){
        cout << "MimeMessage::Cc.size() : " << message->getRecipients(MimeMessage::Cc).size() << endl;
        for(int i = 0; i < message->getRecipients(MimeMessage::Cc).size(); i++){
            if(label_cc->text().size() > 0)
                label_cc->setText(label_cc->text().append(","));
            label_cc->setText(label_cc->text().append(message->getRecipients(MimeMessage::Cc).at(i)->getAddress()));
        }
    }

    attachements = message->getAttachment();
    cout << "attachement size : " << attachements.size() << endl;
    label_attachement->setText("label attachement");
    label_corps->setText(message->getHtml());
}


void DetailledEmail::slot_answer(){
    cout << "Slot answer mail" << endl;
    SendNewEmail * new_mail = new SendNewEmail(label_sender->text(), label_cc->text(), label_object->text(), label_corps->toPlainText());
    new_mail->show();
}

bool DetailledEmail::isAlive(){
    return alive;
}

void DetailledEmail::setAlive(){
    alive = true;
}
