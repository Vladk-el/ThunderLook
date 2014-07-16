#ifndef DETAILMEETING_H
#define DETAILMEETING_H

#include <QtGui>
#include <QtCore>
#include <QListWidget>
#include <QDialog>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>

#include "../smtpClient/src/smtpclient.h"
#include "../smtpClient/src/smtpclient.h"
#include "user.h"
#include "room.h"

class DetailMeeting : public QDialog
{
    Q_OBJECT
public:
    DetailMeeting(int _meeting_id, QWidget *parent = 0);

private:
    int user_id;
    int meeting_id;
    int id_room;
    SmtpClient *smtp;

    QLabel *lb_label;

    QTimeEdit *meeting_duration;
    QPushButton *btn_editDuration;

    QComboBox *cb_organizer;
    QComboBox *cb_users;
    QComboBox *cb_room;

    QPushButton *btn_unavailable;
    QPushButton *btn_del;
    QPushButton *btn_action;
    QPushButton *btn_cancel;

    QDateTimeEdit *meeting_dt_begin;
    QDateTimeEdit *meeting_dt_end;

    QStandardItemModel *model_users;

    QSettings *global_settings;
    QSqlDatabase db;

private slots:
    void quit();
    void deleteMeeting();
    void sendEmailDeleteMeeting(int id_meeting,QString date);
    void sendEmailUpdateMeeting(int id_meeting,QString date);
    void updateMeeting();

signals:
    void notifyRefreshList();
};


#endif // DETAILMEETING_H
