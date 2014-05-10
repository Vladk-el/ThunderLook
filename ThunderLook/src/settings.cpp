#include "settings.h"

Settings::Settings()
{

    setWindowTitle(tr("Paramètres du compte"));
    setMinimumSize(400, 500);

    layout_main = new QVBoxLayout;
        qtab_settings = new QTabWidget;

        layout_buttons = new QHBoxLayout;
            button_save = new QPushButton(tr("Enregistrer"));
            button_cancel = new QPushButton(tr("Annuler"));
        layout_buttons->addWidget(button_save);
        layout_buttons->addWidget(button_cancel);

    layout_main->addWidget(qtab_settings);
    layout_main->addLayout(layout_buttons);


    setAccountTab();
    setSendTab();
    setReceptionTab();

    setLayout(layout_main);

}


void Settings::setAccountTab(){
    tab_account = new QWidget;
        layout_tab_account = new QVBoxLayout;
            label_account_name = new QLabel(tr("Nom du compte"));
            line_account_name = new QLineEdit;
            label_name = new QLabel(tr("Nom de l'utilisateur"));
            line_name = new QLineEdit;
            label_email = new QLabel(tr("Adresse email"));
            line_email = new QLineEdit;
            label_signature = new QLabel(tr("Signature"));
            line_signature = new QTextEdit;
            label_synchronization = new QLabel(tr("Fréquence de synchronisation"));
            line_synchronization = new QSpinBox;
                line_synchronization->setMinimum(5);
                line_synchronization->setSingleStep(5);
                line_synchronization->setMaximum(60);
                line_synchronization->setSuffix(tr(" minutes"));

        layout_tab_account->addWidget(label_account_name);
        layout_tab_account->addWidget(line_account_name);
        layout_tab_account->addWidget(label_name);
        layout_tab_account->addWidget(line_name);
        layout_tab_account->addWidget(label_email);
        layout_tab_account->addWidget(line_email);
        layout_tab_account->addWidget(label_signature);
        layout_tab_account->addWidget(line_signature);
        layout_tab_account->addWidget(label_synchronization);
        layout_tab_account->addWidget(line_synchronization);

    tab_account->setLayout(layout_tab_account);

    qtab_settings->addTab(tab_account, tr("Compte"));
}

void Settings::setSendTab(){
    tab_send = new QWidget;
        layout_tab_send = new QVBoxLayout;
            label_smtp_name = new QLabel(tr("Serveur SMTP"));
            line_smtp_name = new QLineEdit;
            label_smtp_port = new QLabel(tr("Port"));
            line_smtp_port = new QLineEdit;
            label_smtp_user = new QLabel(tr("Nom d'utilisateur"));
            line_smtp_user = new QLineEdit;
            label_smtp_password = new QLabel(tr("Mot de passe"));
            line_smtp_password = new QLineEdit;
                line_smtp_password->setEchoMode(QLineEdit::Password);

        layout_tab_send->addWidget(label_smtp_name);
        layout_tab_send->addWidget(line_smtp_name);
        layout_tab_send->addWidget(label_smtp_port);
        layout_tab_send->addWidget(line_smtp_port);
        layout_tab_send->addWidget(label_smtp_user);
        layout_tab_send->addWidget(line_smtp_user);
        layout_tab_send->addWidget(label_smtp_password);
        layout_tab_send->addWidget(line_smtp_password);
        layout_tab_send->addStretch(1);

    tab_send->setLayout(layout_tab_send);

    qtab_settings->addTab(tab_send, tr("Envoi"));
}

void Settings::setReceptionTab(){
    tab_recept = new QWidget;
        layout_tab_recept = new QVBoxLayout;
            label_recept_name = new QLabel(tr("Serveur SMTP"));
            line_recept_name = new QLineEdit;
            label_recept_port = new QLabel(tr("Port"));
            line_recept_port = new QLineEdit;
            label_recept_user = new QLabel(tr("Nom d'utilisateur"));
            line_recept_user = new QLineEdit;
            label_recept_password = new QLabel(tr("Mot de passe"));
            line_recept_password = new QLineEdit;
                line_recept_password->setEchoMode(QLineEdit::Password);
            label_recept_delete_on_server = new QLabel(tr("Supprimer les mails du serveur"));
            line_recept_delete_on_server = new QComboBox;
                line_recept_delete_on_server->addItem(tr("Jamais"));
                line_recept_delete_on_server->addItem(tr("Si messages supprimés de la boite de réception"));

        layout_tab_recept->addWidget(label_recept_name);
        layout_tab_recept->addWidget(line_recept_name);
        layout_tab_recept->addWidget(label_recept_port);
        layout_tab_recept->addWidget(line_recept_port);
        layout_tab_recept->addWidget(label_recept_user);
        layout_tab_recept->addWidget(line_recept_user);
        layout_tab_recept->addWidget(label_recept_password);
        layout_tab_recept->addWidget(line_recept_password);
        layout_tab_recept->addWidget(label_recept_delete_on_server);
        layout_tab_recept->addWidget(line_recept_delete_on_server);
        layout_tab_recept->addStretch(1);

    tab_recept->setLayout(layout_tab_recept);

    qtab_settings->addTab(tab_recept, tr("Réception"));
}

















