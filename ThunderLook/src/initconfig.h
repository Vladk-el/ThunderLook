#ifndef INITCONFIG_H
#define INITCONFIG_H

#include "settings.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

class InitConfig : public QWidget
{
    Q_OBJECT

    public:
        InitConfig();

        void setWelcomeInterface();
        void setAccountInterface();
        void setSendingInterface();
        void setReceptionInterface();

        void updateAccountConfig();
        void updateSendingConfig();
        void updateReceptionConfig();


    signals:

    public slots:
        void displayWelcomeInterfaceBack();
        void displayAccountInterface();
        void displayAccountInterfaceBack();
        void displaySendingInterface();
        void displaySendingInterfaceBack();
        void displayReceptionInterface();
        void display_main_frame();

    private:
        // QSettings
        QSettings * settings;

        // Layouts
        QVBoxLayout * layout_main;
        QHBoxLayout * layout_buttons;

        // QWidgets
        QWidget * welcome;
            QVBoxLayout * layout_welcome;
            QLabel * label_welcome_welcome;
            QLabel * label_welcome_present;
            QLabel * label_welcome_config;
            QHBoxLayout * layout_welcome_buttons;
            QPushButton * welcome_quit;
            QPushButton * welcome_next;

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
            QHBoxLayout * layout_account_buttons;
                QPushButton * account_previous;
                QPushButton * account_next;

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
            QLabel * label_smtp_security;
            QComboBox * line_stmp_security;
            QHBoxLayout * layout_smtp_buttons;
                QPushButton * smtp_previous;
                QPushButton * smtp_next;

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
            QLabel * label_recept_security;
            QComboBox * line_recept_security;
            QHBoxLayout * layout_recept_buttons;
                QPushButton * recept_previous;
                QPushButton * recept_done;

        // QPushButtons
        QPushButton * button_save;
        QPushButton * button_cancel;




};

#endif // INITCONFIG_H
