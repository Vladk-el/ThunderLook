#ifndef WIDGETPREVIEWED_H
#define WIDGETPREVIEWED_H

#include "../includes/smtpClient/src/mimemessage.h"

#include "previewedemail.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QList>

#include <QPainter>

class WidgetPreviewed : public QWidget
{
    Q_OBJECT

    public:
        WidgetPreviewed(QList<MimeMessage *> &);

    signals:
        void sayMyChildrenSelectedId(int);

    public slots:
        void getMyChildrensId(int);
        void paintEvent(QPaintEvent *);

    private:
        QVBoxLayout * layout_previewed;

        QList<PreviewedEmail *> * previewed;

};

#endif // WIDGETPREVIEWED_H
