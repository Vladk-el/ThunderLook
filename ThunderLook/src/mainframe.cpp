#include "mainframe.h"

using namespace std;

MainFrame::MainFrame()
{

    setSettings();

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
    settings = new QSettings("../data/settings/settings.ini", QSettings::IniFormat);
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

    QStringList folders;
    folders << "Folder1" << "Folder2" << "Folder3" << "Folder4" ;
    model_folders = new QStringListModel(folders);
    view_list_folders = new QListView;
    view_list_folders->setModel(model_folders);
    QSizePolicy spLeft(QSizePolicy::Minimum, QSizePolicy::Minimum);
    //spLeft.setHorizontalStretch(1);
    view_list_folders->setSizePolicy(spLeft);

    QStringList mails;
    mails << "Mail1" << "Mail2" << "Mail3" << "Mail4" << "Mail5";
    model_mails = new QStringListModel(mails);
    view_list_mails = new QListView;
    view_list_mails->setModel(model_mails);
    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    //spRight.setHorizontalStretch(10);
    view_list_folders->setSizePolicy(spRight);

    layout_main->addWidget(view_list_folders);
    layout_main->addWidget(view_list_mails);





    widget_central->setLayout(layout_main);
    setCentralWidget(widget_central);
}

void MainFrame::setSlotsConnexions(){

    connect(action_quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(action_new_mail, SIGNAL(triggered()), this, SLOT(slot_new_mail()));
    connect(action_refresh_mails, SIGNAL(triggered()), this, SLOT(slot_refresh_mails()));
    connect(action_configure_account, SIGNAL(triggered()), this, SLOT(slot_configure_account()));


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
}





















