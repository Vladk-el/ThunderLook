#ifndef CONTACT_H
#define CONTACT_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QtSql>
#include <QFormLayout>

#include "../includes/Meeting/user.h"

class Contact : public QDialog
{
    Q_OBJECT
public:
    explicit Contact(QWidget *parent = 0);

private:
    QPushButton *btn_delete_user;
    QPushButton *btn_add_user;
    QPushButton *btn_cancel;

    QListView  *listView_users;

    QGroupBox *list_users;
    QGroupBox *add_user;

    QFormLayout *form_list_users;
    QFormLayout *form_add_user;

    QStandardItemModel *modelListUsers;
    QSqlDatabase db;

    QLineEdit *city;
    QLineEdit *fax;
    QLineEdit *tel;
    QLineEdit *firstname;
    QLineEdit *name;
    QLineEdit *addr;

signals:

public slots:
    void addUser();

};

#endif // CONTACT_H
