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

    // Action new meeting
    action_new_meeting = new QAction(tr("&Réunion"), this);
    action_new_meeting->setShortcut(QKeySequence("Ctrl+R"));
    menu_email->addAction(action_new_meeting);

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
    toolbar_top->addAction(action_new_meeting);

    //toolbar_top->setOrientation(Qt::Vertical);
}

void MainFrame::setLayouts(){

    // A virer dans une classe à part
    widget_central = new QWidget;
    layout_main = new QHBoxLayout;

    // Folders
    QStringList folders;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    if (!db.open())
    {
        qDebug() << "Impossible de se connecter à la base de données." << endl;
        return;
    }

    QSqlQuery *req = new QSqlQuery();
    req->prepare("SELECT * FROM Folder");
    req->exec();
    QSqlRecord rec = req->record();

    while(req->next())
    {
        if(req->value(rec.indexOf("name")).toString().contains("Inbox"))
        {
            /*QSqlQuery *reqCount = new QSqlQuery();
            reqCount->prepare("SELECT COUNT(id_email) FROM Emails WHERE isRead = 1 AND id_folder = 1");
            reqCount->exec();
            reqCount->next();*/

            // QString value(req->value(rec.indexOf("name")).toString() + " (" + reqCount->value(0).toString() + ")");
            QString value(req->value(rec.indexOf("name")).toString());

            folders << value;
        }

        else
        {
            folders << req->value(rec.indexOf("name")).toString();
        }
    }

    // folders << "Folder1" << "Folder2" << "Folder3" << "Folder4" ;

    model_folders = new QStringListModel(folders);
    view_list_folders = new QListView;
    view_list_folders->setModel(model_folders);
    view_list_folders->setMaximumWidth(this->width()/10);
    view_list_folders->setEditTriggers(QAbstractItemView::NoEditTriggers);

    getEmails();
    SqlLiteHelper * helper = new SqlLiteHelper;
    messages = helper->getAllEmails(1);

    widget_previewed = new WidgetPreviewed(messages);

    widget_previewed->setMaximumWidth(3*this->width()/10);
    widget_previewed->setMinimumWidth(2*this->width()/10);

    connect(widget_previewed, SIGNAL(sayMyChildrenSelectedId(int)), this, SLOT(slot_get_email_indice(int)));

    // Detailled mail
    widget_detailled = new QWidget;
    layout_detailled = new QVBoxLayout;

    if(messages.size() > 0){
        detailledEmail = new DetailledEmail(messages.at(0));
    }else{
        MimeMessage * test = construct();
        detailledEmail = new DetailledEmail();
    }


    layout_detailled->addWidget(detailledEmail);

    widget_detailled->setLayout(layout_detailled);
    widget_detailled->setMaximumWidth(6*this->width()/10);


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
    connect(action_new_meeting, SIGNAL(triggered()), this, SLOT(slot_new_meeting()));
    connect(action_configure_account, SIGNAL(triggered()), this, SLOT(slot_configure_account()));

}

void MainFrame::resizeEvent(QResizeEvent * event){
    cout << "Size changed !!!" << endl;
    view_list_folders->setMaximumWidth(this->width()/10);
    //widget_previewed->setMaximumWidth(3*this->width()/10);
    widget_detailled->setMaximumWidth(6*this->width()/10);
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

void MainFrame::slot_new_meeting(){
    //MeetingWindow *meeting = new MeetingWindow;
    //meeting->show();

    Contact *contact = new Contact;
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

void MainFrame::slot_get_email_indice(int indice){
    cout << "indice : " << indice << endl;
    cout << "messages.size() : " << messages.size() << endl;

    /*// Update database
    QSqlQuery *req = new QSqlQuery();
    req->prepare("UPDATE Emails SET isRead = :isRead WHERE indice = :indice");
    req->bindValue(":isRead",1);
    req->bindValue(":indice",messages.at(indice)->getIndice());
    req->exec();*/

    detailledEmail->update(messages.at(indice));
}

bool MainFrame::getEmails()
{
    SqlLiteHelper * slh = new SqlLiteHelper();

    PopClient * pop = new PopClient("pop.gmail.com",995,PopClient::SslConnection);
    pop->setUser("oliveira93700@gmail.com");
    pop->setPassword("Oliveira93");

    if(pop->connectToHost() == true)
        qDebug() << "connectToHost => OK";

    else
    {
        qDebug() << "connectToHost => NOK";
        return false;
    }

    if(pop->login() == true)
        qDebug() << "login => OK";

    else
    {
        qDebug() << "login => NOK";
        return false;
    }

    QList<MimeMessage*> emails = pop->getAllEmails();

    for(int i = 0 ; i < emails.size() ; i++)
    {
        try
        {
            slh->insertEmail(emails.at(i),1);
            qDebug() << "Numero du message :" << i+1 << endl << emails.at(i)->getSubject() << endl;
        }
        catch(exception e)
        {
            qDebug() << "Exception" << endl;
        }
    }

    pop->quit();

    return true;
}
