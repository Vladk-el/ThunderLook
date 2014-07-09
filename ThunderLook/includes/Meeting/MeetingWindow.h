#ifndef MEETINGWINDOW_H
#define MEETINGWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTableView>
#include <QCalendarWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QListView>
#include <QtSql>

#include "../smtpClient/src/smtpclient.h"
#include "meeting.h"
#include "detailmeeting.h"

class MeetingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MeetingWindow(QWidget *parent = 0);
    ~MeetingWindow();

private slots:
    void refreshList();
    void displayInfo();
    void addMeeting();

private:
    QStandardItemModel *model;
    QTableView *view;
    QCalendarWidget *calendar;
    QComboBox *cb_view;
    QPushButton *btn_add;
    QStringList hours;
    QList<QColor> *colours;
    QLabel *rate;
    QLabel *label_week;
    QWidget *widget_central;
    QHBoxLayout *layout_main;
    QStringListModel *model_folders;
    QStringListModel *model_mails;
    QListView *view_list_mails;
    QListView *view_list_folders;
    QSqlDatabase db;
    int id_account;
    QSettings *global_settings;
};

#endif // MEETINGWINDOW_H
