#include "mainframe.h"

using namespace std;

MainFrame::MainFrame()
{
    setSettings();

    if(global_settings->value("account_configured").toBool())
        init();
    else
        initConfig();
}

MainFrame::~MainFrame()
{
    std::cout << "MainFrame destoyed" << std::endl;
}

void MainFrame::initConfig(){
    InitConfig * initConfig = new InitConfig();
    connect(initConfig, SIGNAL(destroyed()), this, SLOT(slot_launch())); // Voir ce qui cloche avec ça
}

void MainFrame::init(){
    // Init si fichier de conf OK
    setSize();
    setMenus();
    setActions();
    setToolBars();
    setLayouts();
    setSlotsConnexions();

    show();
}


void MainFrame::setSettings(){
    global_settings = new QSettings("../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);
}

void MainFrame::setSize(){
    setMinimumSize(1200, 800);
}

void MainFrame::setMenus(){

    menu_thunderlook = menuBar()->addMenu(tr("&ThunderLook"));
    menu_account = menuBar()->addMenu(tr("&Compte"));
    menu_email = menuBar()->addMenu(tr("&Email"));
}

void MainFrame::setActions(){

    // Action new mail
    action_new_mail = new QAction(tr("&Nouvel e-mail"), this);
    action_new_mail->setShortcut(QKeySequence("Ctrl+N"));
    menu_email->addAction(action_new_mail);

    // Action refresh
    action_refresh_mails = new QAction(tr("&Rafraichir"), this);
    action_refresh_mails->setShortcut(QKeySequence("F5"));
    menu_email->addAction(action_refresh_mails);

    // Action quit
    action_quit = new QAction(tr("&Quitter"), this);
    action_quit->setShortcut(QKeySequence("Ctrl+Q"));
    menu_thunderlook->addAction(action_quit);

    // Action configure account
    action_configure_account = new QAction(tr("Paramètres"), this);
    action_configure_account->setShortcut(QKeySequence("Ctrl+P"));
    menu_account->addAction(action_configure_account);



}

void MainFrame::setToolBars(){

    toolbar_top = addToolBar("Top");

    //toolbar_top->addAction(action_quit);
    toolbar_top->addAction(action_new_mail);
    toolbar_top->addAction(action_refresh_mails);


    //toolbar_top->setOrientation(Qt::Vertical);
}

void MainFrame::setLayouts(){

    // A virer dans une classe à part
    widget_central = new QWidget;
    layout_main = new QHBoxLayout;

    // TEST MESSAGES MODEL
    /*MimeMessage * test = construct();

    PreviewedEmail * previewedEmail = new PreviewedEmail(test);
    */

    // Folders
    QStringList folders;
    folders << "Folder1" << "Folder2" << "Folder3" << "Folder4" ;
    model_folders = new QStringListModel(folders);
    view_list_folders = new QListView;
    view_list_folders->setModel(model_folders);
    view_list_folders->setMaximumWidth(this->width()/10);
    //QSizePolicy spLeft(QSizePolicy::Minimum, QSizePolicy::Minimum);
    //spLeft.setHorizontalStretch(1);
    //view_list_folders->setSizePolicy(spLeft);


    // Previewed mail
    widget_previewed = new QWidget;
        layout_previewed = new QVBoxLayout;

            MimeMessage * test = construct();

            PreviewedEmail * pe1 = new PreviewedEmail(test);
            PreviewedEmail * pe2 = new PreviewedEmail(test);
            PreviewedEmail * pe3 = new PreviewedEmail(test);

            layout_previewed->addWidget(pe1);
            layout_previewed->addWidget(pe2);
            layout_previewed->addWidget(pe3);
            layout_previewed->addStretch(1);

        widget_previewed->setLayout(layout_previewed);

        QPalette p;
        p.setColor(QPalette::Background, Qt::white);
        widget_previewed->setAutoFillBackground(true);
        widget_previewed->setPalette(p);
        widget_previewed->setMaximumWidth(3*this->width()/10);


    // Detailled mail
    widget_detailled = new QWidget;
        layout_detailled = new QVBoxLayout;
            DetailledEmail * detailledEmail = new DetailledEmail(test);

            layout_detailled->addWidget(detailledEmail);

        widget_detailled->setLayout(layout_detailled);
        widget_previewed->setMaximumWidth(6*this->width()/10);



    layout_main->addWidget(view_list_folders);
    layout_main->addWidget(widget_previewed);
    layout_main->addWidget(widget_detailled);


    widget_central->setLayout(layout_main);
    setCentralWidget(widget_central);
}

void MainFrame::setSlotsConnexions(){

    connect(action_quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(action_new_mail, SIGNAL(triggered()), this, SLOT(slot_new_mail()));
    connect(action_refresh_mails, SIGNAL(triggered()), this, SLOT(slot_refresh_mails()));
    connect(action_configure_account, SIGNAL(triggered()), this, SLOT(slot_configure_account()));

}

QSettings * MainFrame::getSettings(){
    return global_settings;
}



// SLOTS

void MainFrame::slot_new_mail(){
    cout << "Slot new mail" << endl;
    SendNewEmail * send_new_mail = new SendNewEmail;
    send_new_mail->show();
}

void MainFrame::slot_refresh_mails(){
    cout << "Slot refresh mail" << endl;
}

void MainFrame::slot_configure_account(){
    cout << "Slot configure account" << endl;

    Settings * settings = new Settings;
}

void MainFrame::slot_launch(){
    global_settings->sync();
    if(global_settings->value("account_configured").toBool())
        init();
}





















