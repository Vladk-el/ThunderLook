#ifndef WIDGETPREVIEWED_H
#define WIDGETPREVIEWED_H

#include "../includes/smtpClient/src/mimemessage.h"

#include "previewedemail.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QList>
#include <QPainter>
#include <QScrollArea>

class WidgetPreviewed : public QWidget
{
    Q_OBJECT

    public:
        WidgetPreviewed(QList<MimeMessage *> &);

        void update(QList<MimeMessage *> &);
        void updateMyChild(int);

    signals:
        void sayMyChildrenSelectedId(int);

    public slots:
        void getMyChildrensId(int);
        void paintEvent(QPaintEvent *);

    private:
        QWidget * container;
        QVBoxLayout * layout_previewed;

        QList<PreviewedEmail *> * previewed;

        QScrollArea * sa;
        QVBoxLayout * layout;

};

#endif // WIDGETPREVIEWED_H
