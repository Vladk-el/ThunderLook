#ifndef WIDGETPREVIEWED_H
#define WIDGETPREVIEWED_H

#include "../includes/smtpClient/src/mimemessage.h"

#include "previewedemail.h"

#include <QWidget>
#include <QVBoxLayout>

class WidgetPreviewed : public QWidget
{
    Q_OBJECT

    public:
        WidgetPreviewed(QList<MimeMessage *> &);

    signals:
        void sayMyChildrenSelectedId(int);

    public slots:
        void getMyChildrensId(int);

    private:
        QVBoxLayout * layout_previewed;

};

#endif // WIDGETPREVIEWED_H
