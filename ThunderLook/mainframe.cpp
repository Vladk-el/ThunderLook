#include "mainframe.h"

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
    menu_file = menuBar()->addMenu(tr("&Fichier"));
}

void MainFrame::addActions(){

    // Action quit
    action_quit = new QAction(tr("&Quitter"), this);
    action_quit->setShortcut(QKeySequence("Ctrl+Q"));
    menu_thunderlook->addAction(action_quit);

    // Action new mail
    action_new_mail = new QAction(tr("&Nouvel e-mail"), this);
    action_new_mail->setShortcut(QKeySequence("Ctrl+N"));

}

void MainFrame::addToolBars(){

    toolbar_top = addToolBar("Top");

    //toolbar_top->addAction(action_quit);
    toolbar_top->addAction(action_new_mail);


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
}


























