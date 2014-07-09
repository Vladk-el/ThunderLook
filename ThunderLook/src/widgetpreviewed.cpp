#include "widgetpreviewed.h"

WidgetPreviewed::WidgetPreviewed(QList<MimeMessage *> & messages)
{
    previewed = new QList<PreviewedEmail *>;

    layout_previewed = new QVBoxLayout;

        for(int i = 0; i < messages.length(); i++){
                previewed->append(new PreviewedEmail(messages.at(i), i));
                layout_previewed->addWidget(previewed->at(i));
                connect(previewed->at(i), SIGNAL(sayYourId(int)), this, SLOT(getMyChildrensId(int)));
            }

        layout_previewed->addStretch(1);

    setLayout(layout_previewed);

    QPalette p;
    p.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(p);
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
