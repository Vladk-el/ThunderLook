#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>

class Settings : public QWidget
{
    Q_OBJECT

    public:
        Settings();

        void setAccountTab();
        void setSendTab();
        void setReceptionTab();

    signals:

    public slots:

    private:
        // QTabWidget
        QTabWidget * qtab_settings;

        // Layouts
        QVBoxLayout * layout_main;
        QHBoxLayout * layout_buttons;

        // QWidgets
        QWidget * tab_account;

            QVBoxLayout * layout_tab_account;
            QLabel * label_account_name;
            QLineEdit * line_account_name;
            QLabel * label_name;
            QLineEdit * line_name;
            QLabel * label_email;
            QLineEdit * line_email;
            QLabel * label_signature;
            QTextEdit * line_signature;
            QLabel * label_synchronization;
            QSpinBox * line_synchronization;


        QWidget * tab_send;
            QVBoxLayout * layout_tab_send;
            QLabel * label_smtp_name;
            QLineEdit * line_smtp_name;
            QLabel * label_smtp_port;
            QLineEdit * line_smtp_port;
            QLabel * label_smtp_user;
            QLineEdit * line_smtp_user;
            QLabel * label_smtp_password;
            QLineEdit * line_smtp_password;


        QWidget * tab_recept;
            QVBoxLayout * layout_tab_recept;
            QLabel * label_recept_name;
            QLineEdit * line_recept_name;
            QLabel * label_recept_port;
            QLineEdit * line_recept_port;
            QLabel * label_recept_user;
            QLineEdit * line_recept_user;
            QLabel * label_recept_password;
            QLineEdit * line_recept_password;
            QLabel * label_recept_delete_on_server;
            QComboBox * line_recept_delete_on_server;


        // QPushButtons
        QPushButton * button_save;
        QPushButton * button_cancel;


};

#endif // SETTINGS_H
