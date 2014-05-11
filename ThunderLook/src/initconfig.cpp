#include "initconfig.h"

InitConfig::InitConfig(QWidget * mainframe)
{

    setWindowTitle(tr("ThunderLook - Bienvenue"));
    setMinimumSize(400, 500);

    layout_main = new QVBoxLayout;

    settings = new QSettings("../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);

    setWelcomeInterface();

    /*setAccountInterface();

    setSendingInterface();

    setReceptionInterface();*/

    setLayout(layout_main);

    show();
}

void InitConfig::setWelcomeInterface(){
    welcome = new QWidget;
        layout_welcome = new QVBoxLayout;
            label_welcome_welcome = new QLabel;
            label_welcome_welcome->setText("Bonjour et bienvenue sur ThunderLook.\n\n\n");
            label_welcome_present = new QLabel;
            label_welcome_present->setText("Thunderlook est un client mail légé et fiable, qui comblera toute vos attente en matière de \ngestion et envoi de vos mails personnels ou professionnels.\n\n");
            label_welcome_config = new QLabel;
            label_welcome_config->setText("Avant de commencer, veuillez remplir les quelques informations relatives à votre compte email. \n\nCliquez sur \"Suivant\" pour continuer la configuration de votre compte.");
            layout_welcome_buttons = new QHBoxLayout;
                welcome_quit = new QPushButton(tr("Quitter"));
                welcome_next = new QPushButton(tr("Suivant"));
                layout_welcome_buttons->addWidget(welcome_quit);
                layout_welcome_buttons->addWidget(welcome_next);

            layout_welcome->addWidget(label_welcome_welcome);
            layout_welcome->addWidget(label_welcome_present);
            layout_welcome->addWidget(label_welcome_config);
            layout_welcome->addStretch(1);
            layout_welcome->addLayout(layout_welcome_buttons);


        welcome->setLayout(layout_welcome);
    layout_main->addWidget(welcome);

    connect(welcome_quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(welcome_next, SIGNAL(clicked()), this, SLOT(displayAccountInterface()));
}

void InitConfig::setAccountInterface(){
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
            layout_account_buttons = new QHBoxLayout;
                account_previous = new QPushButton(tr("Précédent"));
                account_next = new QPushButton(tr("Suivant"));
                layout_account_buttons->addWidget(account_previous);
                layout_account_buttons->addWidget(account_next);

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
        layout_tab_account->addLayout(layout_account_buttons);


    tab_account->setLayout(layout_tab_account);

    layout_main->addWidget(tab_account);

    connect(account_previous, SIGNAL(clicked()), this, SLOT(displayWelcomeInterfaceBack()));
    connect(account_next, SIGNAL(clicked()), this, SLOT(displaySendingInterface()));
}

void InitConfig::setSendingInterface(){
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
            layout_smtp_buttons = new QHBoxLayout;
                smtp_previous = new QPushButton(tr("Précédent"));
                smtp_next = new QPushButton(tr("Suivant"));
                layout_smtp_buttons->addWidget(smtp_previous);
                layout_smtp_buttons->addWidget(smtp_next);

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
        layout_tab_send->addLayout(layout_smtp_buttons);

    tab_send->setLayout(layout_tab_send);

    layout_main->addWidget(tab_send);

    connect(smtp_previous, SIGNAL(clicked()), this, SLOT(displayAccountInterfaceBack()));
    connect(smtp_next, SIGNAL(clicked()), this, SLOT(displayReceptionInterface()));
}

void InitConfig::setReceptionInterface(){
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
            layout_recept_buttons = new QHBoxLayout;
                recept_previous = new QPushButton(tr("Précédent"));
                recept_done = new QPushButton(tr("Découvrir ThunderLook"));
                layout_recept_buttons->addWidget(recept_previous);
                layout_recept_buttons->addWidget(recept_done);

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
        layout_tab_recept->addLayout(layout_recept_buttons);

    tab_recept->setLayout(layout_tab_recept);

    layout_main->addWidget(tab_recept);

    connect(recept_previous, SIGNAL(clicked()), this, SLOT(displaySendingInterfaceBack()));
    connect(recept_done, SIGNAL(clicked()), this, SLOT(display_main_frame()));
}

void InitConfig::updateAccountConfig(){
    settings->setValue("Account/account_name", line_account_name->text());
    settings->setValue("Account/user_name", line_name->text());
    settings->setValue("Account/user_email", line_email->text());
    settings->setValue("Account/user_signature", line_signature->toPlainText());
    settings->setValue("Account/user_synchro", line_synchronization->value());
}

void InitConfig::updateSendingConfig(){
    settings->setValue("Send/smtp_server", line_smtp_name->text());
    settings->setValue("Send/smtp_port", line_smtp_port->text());
    settings->setValue("Send/smtp_user", line_smtp_user->text());
    settings->setValue("Send/smtp_password", line_smtp_password->text());
    settings->setValue("Send/smtp_security", line_stmp_security->currentIndex());
}

void InitConfig::updateReceptionConfig(){
    settings->setValue("Reception/reception_server", line_recept_name->text());
    settings->setValue("Reception/reception_port", line_recept_port->text());
    settings->setValue("Reception/reception_user", line_recept_user->text());
    settings->setValue("Reception/reception_password", line_recept_password->text());
    settings->setValue("Reception/reception_delete_on_server", line_recept_delete_on_server->currentIndex());
    settings->setValue("Reception/reception_security", line_recept_security->currentIndex());
}


// Slots

void InitConfig::displayWelcomeInterfaceBack(){
    updateAccountConfig();
    layout_main->removeWidget(tab_account);
    delete(tab_account);
    setWelcomeInterface();
}

void InitConfig::displayAccountInterface(){
    layout_main->removeWidget(welcome);
    delete(welcome);
    setAccountInterface();
}

void InitConfig::displayAccountInterfaceBack(){
    updateSendingConfig();
    layout_main->removeWidget(tab_send);
    delete(tab_send);
    setAccountInterface();
}

void InitConfig::displaySendingInterface(){
    updateAccountConfig();
    layout_main->removeWidget(tab_account);
    delete(tab_account);
    setSendingInterface();
}

void InitConfig::displaySendingInterfaceBack(){
    updateReceptionConfig();
    layout_main->removeWidget(tab_recept);
    delete(tab_recept);
    setSendingInterface();
}

void InitConfig::displayReceptionInterface(){
    updateSendingConfig();
    layout_main->removeWidget(tab_send);
    delete(tab_send);
    setReceptionInterface();
}

void InitConfig::display_main_frame(){
    updateReceptionConfig();
    // Trouver un moyen de retourner sur MainFrame
    close();
}










