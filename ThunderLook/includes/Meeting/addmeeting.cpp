#include <iostream>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

#include "addmeeting.h"

Q_DECLARE_METATYPE(User);
Q_DECLARE_METATYPE(Room);

AddMeeting::AddMeeting(QWidget *parent, int account_id) : QDialog(parent)
{
    setFixedWidth(750);
    setWindowTitle("Planifier une réunion");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("meetings.db");
    if (!db.open())
    {
        qDebug() << "Impossible de se connecter à la base de données." << endl;
        return;
    }

    id = account_id;

    // Subject meeting
    title_meeting = new QLineEdit();

    meetings_rooms = new QComboBox();
    modelRooms = new QStandardItemModel();

    QSqlQuery query;
    query.exec("SELECT * FROM Room");
    int i = 0;
    while(query.next())
    {
        Room room(query.value(0).toInt(),QString(query.value(1).toString()));

        QStandardItem *item = new QStandardItem();
        item->setText(room.name());

        QVariant data;
        data.setValue(room);
        item->setData(data);

        modelRooms->setItem(i,item);
        i++;
    }

    meetings_rooms->setModel(modelRooms);

    meetings_add_users = new QListView();
    meetings_add_users->setEditTriggers(0);

    query.exec("SELECT * FROM Users WHERE id != '" + QString::number(id) +"'");

    modelSourceUsers = new QStandardItemModel();

    currentIndexSource = 0;
    while(query.next())
    {
        User user(query.value(0).toInt(),QString(query.value(1).toString()));

        QStandardItem *item = new QStandardItem();
        item->setText(user.address());

        QVariant data;
        data.setValue(user);
        item->setData(data);

        modelSourceUsers->setItem(currentIndexSource,item);
        currentIndexSource++;
    }

    // Target User Meeting
    currentIndexTarget = 0;
    meeting_list_users = new QListView(this);
    modelTargetUsers = new QStandardItemModel();
    meetings_add_users->setModel(modelSourceUsers);

    QVBoxLayout *layout_add_users = new QVBoxLayout();
    layout_add_users->addWidget(meetings_add_users);

    btn_add_user = new QPushButton("Ajouter");

    QVBoxLayout *layout_add_user = new QVBoxLayout;
    layout_add_user->addWidget(meetings_add_users);
    layout_add_user->addWidget(btn_add_user);

    meeting_details = new QGroupBox("Détails de la réunion");
    meeting_details_data = new QFormLayout();
    meeting_details_data->addRow("Libellé :", title_meeting);
    meeting_details_data->addRow("Salle :", meetings_rooms);
    meeting_details_data->addRow("Invité(s) :", layout_add_user);
    meeting_details->setLayout(meeting_details_data);

    meetings_users_list = new QGroupBox("Liste des invités");

    // USERS MEETING
    meeting_list_users->setModel(modelTargetUsers);

    QVBoxLayout *layout_users = new QVBoxLayout();
    layout_users->addWidget(meeting_list_users);

    btn_delete_user = new QPushButton("Supprimer");

    QVBoxLayout *layout_list_user = new QVBoxLayout;
    layout_list_user->addWidget(meeting_list_users);
    layout_list_user->addWidget(btn_delete_user);

    meetings_users_list->setLayout(layout_list_user);

    // TIME MEETING
    meetings_time = new QGroupBox("Recherche de créneau");

    meeting_dt_begin = new QDateTimeEdit(QDateTime::currentDateTime());
    meeting_dt_begin->setDisplayFormat("dd/MM/yyyy hh:mm");
    meeting_dt_begin->setMinimumDate(QDate(QDate::currentDate()));
    meeting_dt_begin->setMinimumTime(QTime(8,0,0,0));
    meeting_dt_begin->setMaximumTime(QTime(19,45,0,0));

    meeting_duration = new QTimeEdit();
    meeting_duration->setDisplayFormat("hh:mm");
    meeting_duration->setTimeRange(QTime(0,30,0,0), QTime(4,0,0,0));

    meeting_form_duration = new QFormLayout;
    meeting_form_duration->addRow("Début :", meeting_dt_begin);
    meeting_form_duration->addRow("Durée :", meeting_duration);

    QVBoxLayout *layout_meeting_time = new QVBoxLayout;
    layout_meeting_time->addLayout(meeting_form_duration);

    meetings_time->setLayout(layout_meeting_time);

    // OTHERS OPTIONS
    meeting_options = new QGroupBox("Autres options");

    checkbox_compulsory = new QCheckBox();

    combobox_colors = new QComboBox();

    combobox_colors->addItem(QIcon(":blue.png"), "Blue", "#668cd9");
    combobox_colors->addItem(QIcon(":pink.png"), "Pink", "#dd4477");
    combobox_colors->addItem(QIcon(":green.png"), "Green", "#109618");
    combobox_colors->addItem(QIcon(":orange.png"), "Orange", "#dd5511");
    combobox_colors->addItem(QIcon(":brown.png"), "Brown", "#b08b59");
    combobox_colors->addItem(QIcon(":yellow.png"), "Yellow", "#fad163");

    meeting_form_options = new QFormLayout;
    meeting_form_options->addRow("Présence obligatoire :", checkbox_compulsory);
    meeting_form_options->addRow("Couleur :", combobox_colors);

    meeting_options->setLayout(meeting_form_options);

    btn_action = new QPushButton("Valider");
    btn_cancel = new QPushButton("Annuler");

    QHBoxLayout *layout_buttons = new QHBoxLayout;
    layout_buttons->setAlignment(Qt::AlignRight);
    layout_buttons->addWidget(btn_action);
    layout_buttons->addWidget(btn_cancel);

    QVBoxLayout *layout_right = new QVBoxLayout;
    layout_right->addWidget(meetings_users_list);
    layout_right->addWidget(meetings_time);
    layout_right->addWidget(meeting_options);
    layout_right->addLayout(layout_buttons);

    QHBoxLayout *layout_meeting = new QHBoxLayout;
    layout_meeting->addWidget(meeting_details);
    layout_meeting->addLayout(layout_right);

    QVBoxLayout *layout_main = new QVBoxLayout;
    layout_main->addLayout(layout_meeting);

    setLayout(layout_main);

    connect(btn_add_user, SIGNAL(clicked()), this, SLOT(addUser()));
    connect(btn_delete_user, SIGNAL(clicked()), this, SLOT(deleteUser()));
    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(quit()));
    connect(btn_action, SIGNAL(clicked()), this, SLOT(add()));
}

void AddMeeting::addUser() {
    this->moveItemToTarget(meetings_add_users,meeting_list_users);
}

void AddMeeting::deleteUser() {
    this->moveItemToSource(meeting_list_users,meetings_add_users);
}

void AddMeeting::add()
{
    // Convert hour to minute
    int duration_minute = (meeting_duration->time().hour()*60) + meeting_duration->time().minute();
    qDebug() << duration_minute << endl;

    QDateTime *date_end = new QDateTime(QDate(meeting_dt_begin->date().year(),meeting_dt_begin->date().month(),meeting_dt_begin->date().day()),meeting_dt_begin->time().addSecs(duration_minute * 60));

    QSqlQuery query;

    // Get room selected
    Room room = modelRooms->item(meetings_rooms->currentIndex())->data().value<Room>();

    QString dt_begin;
    dt_begin = QString::number(meeting_dt_begin->date().year()) + "/" + QString::number(meeting_dt_begin->date().month()) + "/" + QString::number(meeting_dt_begin->date().day()) + " " + QString::number(meeting_dt_begin->time().hour()) + ":" + QString::number(meeting_dt_begin->time().minute());

    QString dt_end;
    dt_end = QString::number(date_end->date().year()) + "/" + QString::number(date_end->date().month()) + "/" + QString::number(date_end->date().day()) + " " + QString::number(date_end->time().hour()) + ":" + QString::number(date_end->time().minute());

    // Insert meeting
    query.prepare("INSERT INTO Meeting (date_begin,date_end,duration,title,room,color,compulsory,organizer) "
                  "VALUES (:date_begin,:date_end, :duration,:title,:room,:color,:compulsory,:organizer)");
    query.bindValue(":date_begin", dt_begin);
    query.bindValue(":date_end", dt_end);
    query.bindValue(":duration", duration_minute);
    query.bindValue(":title",title_meeting->text());
    query.bindValue(":room", room.id() );
    query.bindValue(":color", combobox_colors->currentText());
    query.bindValue(":compulsory",1 );
    query.bindValue(":organizer",id );
    query.exec();

    query.prepare("SELECT * FROM Meeting where date_begin = :date_begin AND date_end = :date_end AND duration = :duration AND title = :title AND room = :room");
    query.bindValue(":date_begin", dt_begin);
    query.bindValue(":date_end", dt_end);
    query.bindValue(":duration", duration_minute);
    query.bindValue(":title",title_meeting->text());
    query.bindValue(":room", room.id());
    query.exec();

    QSqlQuery query_insert_user;

    while(query.next())
    {
        // Get user selected
        for(int i = 0 ; i < modelTargetUsers->rowCount() ; i++)
        {
            User user = modelTargetUsers->item(i)->data().value<User>();

            query_insert_user.prepare("INSERT INTO UsersMeeting (id_meeting,id_user,present) VALUES(:id_meeting,:id_user,:present)");
            query_insert_user.bindValue(":id_meeting", query.value(0).toInt());
            query_insert_user.bindValue(":id_user", user.id());
            query_insert_user.bindValue(":present", 0);
            query_insert_user.exec();
        }
    }

    sendEmail(3);
    emit notifyRefreshList();
    this->quit();
}

void AddMeeting::quit() {
    this->close();
}

void AddMeeting::moveItemToTarget(QListView  *source, QListView  *target)
{
    QModelIndex index = source->selectionModel()->currentIndex();
    if(index.isValid()){

        if(modelSourceUsers->itemFromIndex(index)->text() != "")
        {
            User user = modelSourceUsers->item(index.row())->data().value<User>();
            source->model()->removeRow(index.row());
            currentIndexSource--;

            QStandardItem *item = new QStandardItem();
            item->setText(user.address());

            QVariant data;
            data.setValue(user);
            item->setData(data);

            modelTargetUsers->setItem(currentIndexTarget,item);
            currentIndexTarget++;
        }
    }
}

void AddMeeting::sendEmail(int id_meeting)
{
    global_settings = new QSettings("../../../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);

    if(global_settings->value("Send/smtp_server").toInt() == 1)
        smtp = new SmtpClient(global_settings->value("Send/smtp_server").toString(), global_settings->value("Send/smtp_port").toInt(), SmtpClient::SslConnection);
    else
        smtp = new SmtpClient(global_settings->value("Send/smtp_server").toString(), global_settings->value("Send/smtp_port").toInt());

    smtp->setUser(global_settings->value("Send/smtp_user").toString());
    smtp->setPassword(global_settings->value("Send/smtp_password").toString());

    QSqlQuery query;

    query.prepare("SELECT * FROM Users,UsersMeeting where id_meeting = :id_meeting AND UsersMeeting.id_user = Users.id");
    query.bindValue(":id_meeting", id_meeting);
    query.exec();
    QSqlRecord rec = query.record();

    while(query.next())
    {
        MimeMessage message;

        message.setSender(new EmailAddress(
                              global_settings->value("Account/user_email").toString(),
                              global_settings->value("Account/user_name").toString()
                              ));

        message.addRecipient(new EmailAddress(query.value(rec.indexOf("address")).toString(), ""));
        message.setSubject("Sujet du mail");

        MimeText * text = new MimeText;
        text->setText("text_content->toPlainText()");

        message.addPart(text);

        smtp->connectToHost();
        smtp->login();
        smtp->sendMail(message);
    }

    smtp->quit();
    close();
}

void AddMeeting::moveItemToSource(QListView  *source, QListView  *target)
{
    QModelIndex index = source->selectionModel()->currentIndex();
    if(index.isValid()){

        if(modelTargetUsers->itemFromIndex(index)->text() != "")
        {
            User user = modelTargetUsers->item(index.row())->data().value<User>();
            source->model()->removeRow(index.row());
            currentIndexTarget--;

            QStandardItem *item = new QStandardItem();
            item->setText(user.address());

            QVariant data;
            data.setValue(user);
            item->setData(data);

            modelSourceUsers->setItem(currentIndexSource,item);
            currentIndexSource++;
        }
    }
}
