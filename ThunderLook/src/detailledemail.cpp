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
            label_date = new QLabel("label_date");
                label_date->setStyleSheet(style_label);
            label_to = new QLabel("label_to");
                label_to->setStyleSheet(style_label);
            label_attachement = new QLabel("label_attachement");
                label_attachement->setStyleSheet(style_label);

            layout_top->addRow(tr("Objet"), label_object);
            layout_top->addRow(tr("Expéditeur"), label_sender);
            layout_top->addRow(tr("Date"), label_date);
            layout_top->addRow(tr("Destinataire(s)"), label_to);
            layout_top->addRow(tr("Pièce(s) jointe(s)"), label_attachement);

        label_corps = new QTextEdit("label_corps");
            label_corps->setEnabled(false);

        layout_main->addLayout(layout_top);
        layout_main->addWidget(label_corps);

    setLayout(layout_main);
}

void DetailledEmail::update(MimeMessage * message){
    label_object->setText(message->getSubject());
    label_sender->setText(message->getSender().getAddress());
    label_date->setText(message->getDate());
    label_to->setText(message->getRecipients().at(0)->getName());
    label_attachement->setText("label attachement");
    label_corps->setText(message->getContent().toString());
}















