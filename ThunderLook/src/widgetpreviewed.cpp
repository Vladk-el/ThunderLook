#include "widgetpreviewed.h"

WidgetPreviewed::WidgetPreviewed(QList<MimeMessage *> & messages)
{
    container = new QWidget;
    previewed = new QList<PreviewedEmail *>;

    layout_previewed = new QVBoxLayout;

        for(int i = 0; i < messages.length(); i++){
                previewed->append(new PreviewedEmail(messages.at(i), i));
                //previewed->at(i)->setMinimumWidth(container->width()-5);
                layout_previewed->addWidget(previewed->at(i));
                connect(previewed->at(i), SIGNAL(sayYourId(int)), this, SLOT(getMyChildrensId(int)));
            }

        layout_previewed->addStretch(1);

    container->setLayout(layout_previewed);

    sa = new QScrollArea;
    sa->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    sa->setWidget(container);

    layout = new QVBoxLayout;
    layout->addWidget(sa);
    setLayout(layout);

    QPalette p;
    p.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(p);
}


void WidgetPreviewed::update(QList<MimeMessage *> & messages){

    for(int i = previewed->size() -1; i > -1; i--){
        layout_previewed->removeWidget(previewed->at(i));
        previewed->removeAt(i);
    }

    delete layout;
    qDeleteAll(children());

    /*layout->removeWidget(sa);
    delete layout_previewed;
    delete previewed;
    delete container;
    delete sa;*/

    container = new QWidget;
    previewed = new QList<PreviewedEmail *>;

    layout_previewed = new QVBoxLayout;

    for(int i = 0; i < messages.length(); i++){
            previewed->append(new PreviewedEmail(messages.at(i), i));
            layout_previewed->addWidget(previewed->at(i));
            connect(previewed->at(i), SIGNAL(sayYourId(int)), this, SLOT(getMyChildrensId(int)));
        }


    layout_previewed->addStretch(1);

    container->setLayout(layout_previewed);
    sa = new QScrollArea;
    sa->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    sa->setWidget(container);

    layout = new QVBoxLayout;
    layout->addWidget(sa);
    setLayout(layout);


}

void WidgetPreviewed::updateMyChild(int indice){
    previewed->at(indice)->setSelected();
}


void WidgetPreviewed::getMyChildrensId(int indice){

    emit sayMyChildrenSelectedId(indice);

    for(int i = 0; i < previewed->size(); i++){
        if(i != indice){
            if(previewed->at(i)->getSelectedState()){
                previewed->at(i)->setUnselected();
            }
        }
    }
}

void WidgetPreviewed::paintEvent(QPaintEvent * event){

    QPainter painter(this);

    painter.drawRoundedRect(0,0,width()-1, height()-1,0,0);

    QWidget::paintEvent(event);
}
