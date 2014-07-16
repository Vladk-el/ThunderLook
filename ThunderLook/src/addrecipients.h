#ifndef ADDRECIPIENTS_H
#define ADDRECIPIENTS_H

#include <QDialog>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QListView>
#include <QPushButton>
#include <QtSql>

#include "../includes/Meeting/user.h"

class AddRecipients : public QDialog
{
    Q_OBJECT
public:
    AddRecipients(QLineEdit & listRecipients,QWidget *parent = 0);

private:
    QLineEdit *currentListRecipients;
    QListView  *listView_users;
    QStandardItemModel *modelListUsers;
    QPushButton *btn_add_user;
    QGroupBox *list_users;
    QFormLayout *form_list_users;
    QSqlDatabase db;

signals:

public slots:
    void addUser();

};

#endif // ADDRECIPIENTS_H
