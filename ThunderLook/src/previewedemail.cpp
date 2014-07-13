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

PreviewedEmail::PreviewedEmail(MimeMessage * message, int indice)
{
    this->indice = indice;
    setConstraints();
    setIHM(message);
    show();
}



void PreviewedEmail::setConstraints(){
    setMaximumHeight(50);
    setMaximumWidth(320);
    setFixedWidth(320);
    QPalette p;
    p.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(p);
}

void PreviewedEmail::setIHM(MimeMessage * message){

    layout_main = new QHBoxLayout;

        label_statement = new QLabel("Statut");

        layout_central = new QVBoxLayout;
            label_sender = new QLabel(message->getSender().getAddress());
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

    isSelected = false;
}


void PreviewedEmail::mousePressEvent(QMouseEvent * event){
    emit sayYourId(this->indice);

    QPalette p;
    p.setColor(QPalette::Background, QColor(213, 229, 242));
    setAutoFillBackground(true);
    setPalette(p);

    isSelected = true;
}

void PreviewedEmail::enterEvent(QEvent * event){
    cout << "Mouse detected !!!" << endl;
    cout << "Indice : " << indice << endl;

    if(!isSelected){
        QPalette p;
        p.setColor(QPalette::Background, QColor(229, 238, 248));
        setAutoFillBackground(true);
        setPalette(p);
    }
}

void PreviewedEmail::leaveEvent(QEvent * event){
    cout << "Mouse leave !!!" << endl;
    cout << "Indice : " << indice << endl;

    if(!isSelected){
        QPalette p;
        p.setColor(QPalette::Background, Qt::white);
        setAutoFillBackground(true);
        setPalette(p);
    }
}

bool PreviewedEmail::getSelectedState(){
    return isSelected;
}

void PreviewedEmail::setUnselected(){
    QPalette p;
    p.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(p);

    isSelected = false;
}

void PreviewedEmail::paintEvent(QPaintEvent * event){

    QPainter painter(this);

    painter.drawRoundedRect(0,0,width()- 1, height()- 1,0,0);

    QWidget::paintEvent(event);
}
