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
    setTimer();

    show();
}

void MainFrame::setSettings(){
    global_settings = new QSettings("../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);
}

void MainFrame::setSize(){
    setMinimumSize(1200, 800);
    selected_email_indice = 0;
    selected_folder_indice = 1;
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
    //action_new_mail->setIcon(QIcon(":/data/img/toolbar/mail-add-icon.png"));
    menu_email->addAction(action_new_mail);

    // Action refresh
    action_refresh_mails = new QAction(tr("&Rafraichir"), this);
    action_refresh_mails->setShortcut(QKeySequence("F5"));
    //action_refresh_mails->setIcon(QIcon(":/data/img/toolbar/refresh-icon.png"));
    menu_email->addAction(action_refresh_mails);

    // Action new meeting
    action_new_meeting = new QAction(tr("&Réunion"), this);
    action_new_meeting->setShortcut(QKeySequence("Ctrl+R"));
    //action_new_meeting->setIcon(QIcon(":/data/img/toolbar/Groups-Meeting-Dark-icon.png"));
    menu_email->addAction(action_new_meeting);

    // Action quit
    action_quit = new QAction(tr("&Quitter"), this);
    action_quit->setShortcut(QKeySequence("Ctrl+Q"));
    menu_thunderlook->addAction(action_quit);

    // Action configure account
    action_configure_account = new QAction(tr("Paramètres"), this);
    action_configure_account->setShortcut(QKeySequence("Ctrl+P"));
    menu_account->addAction(action_configure_account);

    // Action contact
    action_contact = new QAction(tr("&Contacts"), this);
    //action_contact->setIcon(QIcon(":/data/img/toolbar/contacts-icon.png"));
    menu_account->addAction(action_contact);
}

void MainFrame::setToolBars(){

    toolbar_top = addToolBar("Top");

    toolbar_top->addAction(action_new_mail);
    toolbar_top->addAction(action_new_meeting);
    toolbar_top->addAction(action_contact);
    toolbar_top->addAction(action_refresh_mails);

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
            reqCount->prepare("SELECT COUNT(id_email) FROM Emails WHERE isRead = 0 AND id_folder = 1");
            reqCount->exec();
            reqCount->next();*/

            //QString value(req->value(rec.indexOf("name")).toString() + " (" + reqCount->value(0).toString() + ")");
            QString value(req->value(rec.indexOf("name")).toString());

            folders << value;
        }

        else
        {
            folders << req->value(rec.indexOf("name")).toString();
        }
    }

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
        widget_previewed->updateMyChild(selected_email_indice);
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
    connect(action_contact, SIGNAL(triggered()), this, SLOT(slot_contacts()));

    connect(view_list_folders->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this, SLOT(handleSelectionChanged(QItemSelection)));
}

void MainFrame::handleSelectionChanged(const QItemSelection& selection){
    QModelIndexList items = selection.indexes();

    selected_folder_indice = items.at(0).row() + 1;
    slot_refresh_mails();
}

void MainFrame::setTimer(){
    QTimer * refresh_emails = new QTimer;
    refresh_emails->setInterval(global_settings->value("Account/user_synchro").toInt() * 1000 * 60);
    QObject::connect(refresh_emails, SIGNAL(timeout()), this, SLOT(slot_refresh_mails()));
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

    if(selected_folder_indice == 1)
        getEmails();

    SqlLiteHelper * helper = new SqlLiteHelper;
    QList<MimeMessage *> messages_refresh = helper->getAllEmails(selected_folder_indice);

    //if(messages.size() != messages_refresh.size()){
    if(messages != messages_refresh){
        widget_previewed->update(messages_refresh);

        selected_email_indice = selected_email_indice + (messages_refresh.size() - messages.size());
        messages = helper->getAllEmails(selected_folder_indice);
        if(messages.size() > selected_email_indice + 1 && selected_email_indice > -1)
            widget_previewed->updateMyChild(selected_email_indice);
    }
}

void MainFrame::slot_new_meeting(){
    MeetingWindow *meeting = new MeetingWindow;
    meeting->show();
}

void MainFrame::slot_configure_account(){
    cout << "Slot configure account" << endl;

    Settings * settings = new Settings;
}

void MainFrame::slot_contacts(){
    cout << "Slot contacts " << endl;

    Contact * contact = new Contact;
}

void MainFrame::slot_launch(){
    global_settings->sync();
    if(global_settings->value("account_configured").toBool())
        init();
}

void MainFrame::slot_get_email_indice(int indice){
    cout << "indice : " << indice << endl;
    cout << "messages.size() : " << messages.size() << endl;
    selected_email_indice = indice;

    // Update database
    /*QSqlQuery *req = new QSqlQuery();
    req->prepare("UPDATE Emails SET isRead = :isRead WHERE indice = :indice");
    req->bindValue(":isRead",QString::number(1));
    req->bindValue(":indice",messages.at(indice)->getIndice());
    req->exec();*/

    if(!detailledEmail->isAlive()){
        detailledEmail = new DetailledEmail(messages.at(indice));
        layout_detailled->addWidget(detailledEmail);
        widget_detailled->setLayout(layout_detailled);
    }
    else{
        detailledEmail->update(messages.at(indice));
    }
}

void MainFrame::slot_update_from_folder(QItemSelection & selection){

    if(!selection.indexes().isEmpty()){
        cout << "Folder indice : " << selection.indexes().first().row() << endl;
        selected_folder_indice = selection.indexes().first().row();
        slot_refresh_mails();
    }
}



bool MainFrame::getEmails()
{
    SqlLiteHelper * slh = new SqlLiteHelper();

    PopClient * pop = new PopClient(global_settings->value("Reception/reception_server").toString(),995,PopClient::SslConnection);
    pop->setUser(global_settings->value("Reception/reception_user").toString());
    pop->setPassword(global_settings->value("Reception/reception_password").toString());

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
