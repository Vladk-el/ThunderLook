#include "detailledemail.h"

using namespace std;


DetailledEmail::DetailledEmail()
{
    show();
}

DetailledEmail::DetailledEmail(MimeMessage * message){

    setConstraints();
    setIHM(message);

    show();

}

void DetailledEmail::setConstraints(){
    //setMinimumSize(Qt::MaximumSize);

}

void DetailledEmail::setIHM(MimeMessage * message){

    QString style_label("border: 1px solid black;");

    layout_main = new QVBoxLayout;

        layout_top = new QFormLayout;
            label_object = new QLabel(message->getSubject());
                label_object->setStyleSheet(style_label);
            label_sender = new QLabel(message->getSender().getAddress());
                label_sender->setStyleSheet(style_label);
            label_date = new QLabel(message->getDate());
                label_date->setStyleSheet(style_label);
            label_to = new QLabel("");
                label_to->setStyleSheet(style_label);
            label_attachement = new QLabel("label_attachement");
            label_cc = new QLabel("");
                label_cc->setStyleSheet(style_label);
            label_attachement = new QLabel("label_attachement");
                label_attachement->setStyleSheet(style_label);

            layout_top->addRow(tr("Objet"), label_object);
            layout_top->addRow(tr("Expéditeur"), label_sender);
            layout_top->addRow(tr("Date"), label_date);
            layout_top->addRow(tr("Destinataire(s)"), label_to);
            layout_top->addRow(tr("Destinataire(s) - Cc"), label_cc);
            layout_top->addRow(tr("Pièce(s) jointe(s)"), label_attachement);

        label_corps = new QTextEdit(message->getContent().toString());
            label_corps->setEnabled(false);

        layout_main->addLayout(layout_top);
        layout_main->addWidget(label_corps);

    setLayout(layout_main);
}

void DetailledEmail::update(MimeMessage * message){
    label_object->setText(message->getSubject());
    label_sender->setText(message->getSender().getAddress());
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

    label_attachement->setText("label attachement");
    label_corps->setText(message->getContent().toString());
}
