#ifndef ADDMEETING_H
#define ADDMEETING_H

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

#include "../../src/settings.h"
#include "../smtpClient/src/smtpclient.h"
#include "user.h"
#include "room.h"

class AddMeeting : public QDialog
{
    Q_OBJECT
public:
    AddMeeting(QWidget *parent = 0, int id = -1);

private:
    int id;
    int currentIndexSource;
    int currentIndexTarget;

    QLineEdit *title_meeting;
    QDateTimeEdit *meeting_dt_begin;
    QTimeEdit *meeting_duration;

    QListView  *meeting_list_users;
    QListView  *meetings_add_users;

    QComboBox *meetings_rooms;
    QComboBox *meetings_users;
    QComboBox *combobox_colors;

    QFormLayout *meeting_details_data;
    QFormLayout *meeting_form_duration;
    QFormLayout *meeting_form_options;

    QPushButton *btn_action;
    QPushButton *btn_cancel;
    QPushButton *btn_add_user;
    QPushButton *btn_delete_user;

    QGroupBox *meeting_details;
    QGroupBox *meetings_users_list;
    QGroupBox *meetings_time;
    QGroupBox *meeting_options;

    QStandardItemModel *modelSourceUsers;
    QStandardItemModel *modelTargetUsers;
    QStandardItemModel *modelRooms;

    QCheckBox *checkbox_compulsory;

    QSqlDatabase db;
    QSettings *global_settings;
    SmtpClient *smtp;

    void moveItemToTarget(QListView  *source, QListView  *target);
    void moveItemToSource(QListView  *source, QListView  *target);
    void sendEmail(int id_meeting);

public slots:
    void addUser();
    void deleteUser();
    void quit();
    void add();

signals:
    void notifyRefreshList();
};

#endif // ADDMEETING_H
