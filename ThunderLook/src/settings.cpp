#include "settings.h"

Settings::Settings()
{
    settings = new QSettings("../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);

    setMainLayout();
    setAccountTab();
    setSendTab();
    setReceptionTab();
    setSlotsConnexions();

    show();
}


void Settings::setMainLayout(){
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

    setLayout(layout_main);
}


void Settings::setAccountTab(){
    tab_account = new QWidget;
    layout_tab_account = new QVBoxLayout;
    label_account_name = new QLabel(tr("Nom du compte"));
    line_account_name = new QLineEdit(settings->value("Account/account_name").toString());
    label_name = new QLabel(tr("Nom de l'utilisateur"));
    line_name = new QLineEdit(settings->value("Account/user_name").toString());
    label_email = new QLabel(tr("Adresse email"));
    line_email = new QLineEdit(settings->value("Account/user_email").toString());
    label_signature = new QLabel(tr("Signature"));
    line_signature = new QTextEdit();
    line_signature->setText(settings->value("Account/user_signature").toString());
    label_synchronization = new QLabel(tr("Fréquence de synchronisation"));
    line_synchronization = new QSpinBox;
    line_synchronization->setMinimum(5);
    line_synchronization->setSingleStep(5);
    line_synchronization->setMaximum(60);
    line_synchronization->setSuffix(tr(" minutes"));
    line_synchronization->setValue(settings->value("Account/user_synchro").toInt());

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
    line_smtp_name = new QLineEdit(settings->value("Send/smtp_server").toString());
    label_smtp_port = new QLabel(tr("Port"));
    line_smtp_port = new QLineEdit(settings->value("Send/smtp_port").toString());
    label_smtp_user = new QLabel(tr("Nom d'utilisateur"));
    line_smtp_user = new QLineEdit(settings->value("Send/smtp_user").toString());
    label_smtp_password = new QLabel(tr("Mot de passe"));
    line_smtp_password = new QLineEdit(settings->value("Send/smtp_password").toString());
    line_smtp_password->setEchoMode(QLineEdit::Password);
    label_smtp_security = new QLabel(tr("Type de sécurité"));
    line_stmp_security = new QComboBox;
    line_stmp_security->addItem(tr("Aucune"));
    line_stmp_security->addItem(tr("SSL"));
    line_stmp_security->setCurrentIndex(settings->value("Send/smtp_security").toInt());

    layout_tab_send->addWidget(label_smtp_name);
    layout_tab_send->addWidget(line_smtp_name);
    layout_tab_send->addWidget(label_smtp_port);
    layout_tab_send->addWidget(line_smtp_port);
    layout_tab_send->addWidget(label_smtp_user);
    layout_tab_send->addWidget(line_smtp_user);
    layout_tab_send->addWidget(label_smtp_password);
    layout_tab_send->addWidget(line_smtp_password);
    layout_tab_send->addWidget(label_smtp_security);
    layout_tab_send->addWidget(line_stmp_security);
    layout_tab_send->addStretch(1);

    tab_send->setLayout(layout_tab_send);

    qtab_settings->addTab(tab_send, tr("Envoi"));
}

void Settings::setReceptionTab(){
    tab_recept = new QWidget;
    layout_tab_recept = new QVBoxLayout;
    label_recept_name = new QLabel(tr("Serveur"));
    line_recept_name = new QLineEdit(settings->value("Reception/reception_server").toString());
    label_recept_port = new QLabel(tr("Port"));
    line_recept_port = new QLineEdit(settings->value("Reception/reception_port").toString());
    label_recept_user = new QLabel(tr("Nom d'utilisateur"));
    line_recept_user = new QLineEdit(settings->value("Reception/reception_user").toString());
    label_recept_password = new QLabel(tr("Mot de passe"));
    line_recept_password = new QLineEdit(settings->value("Reception/reception_password").toString());
    line_recept_password->setEchoMode(QLineEdit::Password);
    label_recept_delete_on_server = new QLabel(tr("Supprimer les mails du serveur"));
    line_recept_delete_on_server = new QComboBox;
    line_recept_delete_on_server->addItem(tr("Jamais"));
    line_recept_delete_on_server->addItem(tr("Si messages supprimés de la boite de réception"));
    line_recept_delete_on_server->setCurrentIndex(settings->value("Reception/reception_delete_on_server").toInt());
    label_recept_security = new QLabel(tr("Type de sécurité"));
    line_recept_security = new QComboBox;
    line_recept_security->addItem(tr("Aucune"));
    line_recept_security->addItem(tr("SSL"));
    line_recept_security->setCurrentIndex(settings->value("Reception/reception_security").toInt());

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
    layout_tab_recept->addWidget(label_recept_security);
    layout_tab_recept->addWidget(line_recept_security);
    layout_tab_recept->addStretch(1);

    tab_recept->setLayout(layout_tab_recept);

    qtab_settings->addTab(tab_recept, tr("Réception"));
}

void Settings::setSlotsConnexions(){
    connect(button_save, SIGNAL(clicked()), this, SLOT(save()));
    connect(button_cancel, SIGNAL(clicked()), this, SLOT(close()));
}

// Slots

void Settings::save(){
    // Account
    settings->setValue("Account/account_name", line_account_name->text());
    settings->setValue("Account/user_name", line_name->text());
    settings->setValue("Account/user_email", line_email->text());
    settings->setValue("Account/user_signature", line_signature->toPlainText());
    settings->setValue("Account/user_synchro", line_synchronization->value());

    // Send
    settings->setValue("Send/smtp_server", line_smtp_name->text());
    settings->setValue("Send/smtp_port", line_smtp_port->text());
    settings->setValue("Send/smtp_user", line_smtp_user->text());
    settings->setValue("Send/smtp_password", line_smtp_password->text());
    settings->setValue("Send/smtp_security", line_stmp_security->currentIndex());

    // Reception
    settings->setValue("Reception/reception_server", line_recept_name->text());
    settings->setValue("Reception/reception_port", line_recept_port->text());
    settings->setValue("Reception/reception_user", line_recept_user->text());
    settings->setValue("Reception/reception_password", line_recept_password->text());
    settings->setValue("Reception/reception_delete_on_server", line_recept_delete_on_server->currentIndex());
    settings->setValue("Reception/reception_security", line_recept_security->currentIndex());

    close();
}















