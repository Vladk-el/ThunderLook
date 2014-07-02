#include "previewedemail.h"

using namespace std;

PreviewedEmail::PreviewedEmail()
{
    show();
}

PreviewedEmail::PreviewedEmail(MimeMessage * message)
{
    //this->message = message;
    setConstraints();
    setIHM(message);
    show();
}


void PreviewedEmail::setConstraints(){
    setMaximumHeight(50);
    QPalette p;
    p.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(p);
}

void PreviewedEmail::setIHM(MimeMessage * message){

    layout_main = new QHBoxLayout;

        label_statement = new QLabel("Statut");

        layout_central = new QVBoxLayout;
            label_sender = new QLabel(message->getSender().getName());
            label_object = new QLabel(message->getSubject());

            layout_central->addWidget(label_sender);
            layout_central->addWidget(label_object);


            layout_right = new QVBoxLayout;
                label_date = new QLabel(message->getDate());
                label_attachement = new QLabel("Pièce jointe");

                layout_right->addWidget(label_date);
                layout_right->addWidget(label_attachement);

        layout_main->addWidget(label_statement);
        layout_main->addLayout(layout_central);
        layout_main->addLayout(layout_right);

    setLayout(layout_main);

}


void PreviewedEmail::mousePressEvent(QMouseEvent * event){
    cout << "MouseEvent detected !!!" << endl;
}



