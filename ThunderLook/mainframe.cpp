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

}

void MainFrame::addToolBars(){

    toolbar_top = addToolBar("Top");
    toolbar_top->addAction(action_quit);


    //toolbar_top->setOrientation(Qt::Vertical);
}

void MainFrame::addLayouts(){

}

void MainFrame::addSlotsConnexions(){


    connect(action_quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}
