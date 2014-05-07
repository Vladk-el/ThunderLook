#include "mainframe.h"

using namespace std;

MainFrame::MainFrame()
{

    // Init
    addMenus();
    addActions();
    addToolBars();
    addLayouts();
    addSlotsConnexions();

    show();
}


void MainFrame::addMenus(){

    menu_thunderlook = menuBar()->addMenu(tr("&ThunderLook"));
    menu_email = menuBar()->addMenu(tr("&Email"));
}

void MainFrame::addActions(){

    // Action new mail
    action_new_mail = new QAction(tr("&Nouvel e-mail"), this);
    action_new_mail->setShortcut(QKeySequence("Ctrl+N"));
    menu_email->addAction(action_new_mail);

    // Action new mail
    action_get_mails = new QAction(tr("&Rafraichir"), this);
    action_get_mails->setShortcut(QKeySequence("F5"));
    menu_email->addAction(action_get_mails);

    // Action quit
    action_quit = new QAction(tr("&Quitter"), this);
    action_quit->setShortcut(QKeySequence("Ctrl+Q"));
    menu_thunderlook->addAction(action_quit);


}

void MainFrame::addToolBars(){

    toolbar_top = addToolBar("Top");

    //toolbar_top->addAction(action_quit);
    toolbar_top->addAction(action_new_mail);
    toolbar_top->addAction(action_get_mails);


    //toolbar_top->setOrientation(Qt::Vertical);
}

void MainFrame::addLayouts(){

    widget_central = new QWidget;
    layout_main = new QHBoxLayout;
    QStringList folders;
    folders << "Folder1" << "Folder2" << "Folder3" << "Folder4" ;
    model_folders = new QStringListModel(folders);
    view_list_folders = new QListView;
    view_list_folders->setModel(model_folders);

    QStringList mails;
    mails << "Mail1" << "Mail2" << "Mail3" << "Mail4" << "Mail5";
    model_mails = new QStringListModel(mails);
    view_list_mails = new QListView;
    view_list_mails->setModel(model_mails);

    layout_main->addWidget(view_list_folders);
    layout_main->addWidget(view_list_mails);





    widget_central->setLayout(layout_main);
    setCentralWidget(widget_central);
}

void MainFrame::addSlotsConnexions(){

    connect(action_quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(action_new_mail, SIGNAL(triggered()), this, SLOT(slot_new_mail()));
}



// SLOTS

void MainFrame::slot_new_mail(){
    cout << "Slot new mail" << endl;
}






















