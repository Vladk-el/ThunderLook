#include "widgetpreviewed.h"

WidgetPreviewed::WidgetPreviewed(QList<MimeMessage *> & messages)
{
    layout_previewed = new QVBoxLayout;

        for(int i = 0; i < messages.length(); i++){
            PreviewedEmail * pe1 = new PreviewedEmail(messages.at(i), i);
            layout_previewed->addWidget(pe1);
            connect(pe1, SIGNAL(sayYourId(int)), this, SLOT(getMyChildrensId(int)));
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

}
