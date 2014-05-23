#ifndef PREVIEWEDEMAIL_H
#define PREVIEWEDEMAIL_H

#include "../includes/smtpClient/src/mimemessage.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

class PreviewedEmail : public QWidget
{
    Q_OBJECT

    public:
        PreviewedEmail();
        PreviewedEmail(MimeMessage *);

        //virtual QStandardItem * clone(MimeMessage *) const;

        void setConstraints();
        void setIHM(MimeMessage *);

    signals:

    public slots:

    private:
        // Layouts
        QHBoxLayout * layout_main;
        QVBoxLayout * layout_central;
        QVBoxLayout * layout_right;

        // Labels
        QLabel * label_statement;
        QLabel * label_sender;
        QLabel * label_object;
        QLabel * label_date;
        QLabel * label_attachement;

};

#endif // PREVIEWEDEMAIL_H
