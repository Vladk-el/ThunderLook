#include "detailmeeting.h"

Q_DECLARE_METATYPE(User);

DetailMeeting::DetailMeeting(int _meeting_id, QWidget *parent) : QDialog(parent)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("188.165.125.160");
    db.setPort(2981);
    db.setDatabaseName("thunderlook");
    db.setUserName("esgi");
    db.setPassword("esgi");

    if (!db.open())
    {
        qDebug() << "Impossible de se connecter à la base de données." << endl;
        return;
    }

    meeting_id = _meeting_id;

    setWindowTitle("Détails de la réunion");

    QSqlQuery *req = new QSqlQuery();
    req->prepare("SELECT * FROM Meeting m WHERE id = :meeting_id");
    req->bindValue(":meeting_id", meeting_id);
    req->exec();
    QSqlRecord rec = req->record();
    req->next();

    lb_label = new QLabel(req->value(rec.indexOf("title")).toString());

    // DATE BEGIN
    QStringList date_begin = req->value(rec.indexOf("date_begin")).toString().split(" ").at(0).split("/");
    QStringList time_begin = req->value(rec.indexOf("date_begin")).toString().split(" ").at(1).split(":");

    QDate date_begin_edit(date_begin.at(0).toInt(),date_begin.at(1).toInt(),date_begin.at(2).toInt());
    QTime time_begin_edit(time_begin.at(0).toInt(),time_begin.at(1).toInt(),0);

    QDateTime date_time_begin(date_begin_edit,time_begin_edit);

    meeting_dt_begin = new QDateTimeEdit(date_time_begin);
    meeting_dt_begin->setDisplayFormat("dd/MM/yyyy hh:mm");
    meeting_dt_begin->setMinimumTime(QTime(8,0,0,0));
    meeting_dt_begin->setMaximumTime(QTime(19,45,0,0));

    // DATE END
    QStringList date_end = req->value(rec.indexOf("date_end")).toString().split(" ").at(0).split("/");
    QStringList time_end = req->value(rec.indexOf("date_end")).toString().split(" ").at(1).split(":");

    QDate date_end_edit(date_end.at(0).toInt(),date_end.at(1).toInt(),date_end.at(2).toInt());
    QTime time_end_edit(time_end.at(0).toInt(),time_end.at(1).toInt(),0);

    QDateTime date_time_end(date_end_edit,time_end_edit);

    meeting_dt_end = new QDateTimeEdit(date_time_end);
    meeting_dt_end->setDisplayFormat("dd/MM/yyyy hh:mm");
    meeting_dt_end->setMinimumTime(QTime(8,0,0,0));
    meeting_dt_end->setMaximumTime(QTime(19,45,0,0));

    meeting_duration = new QTimeEdit();
    meeting_duration->setDisplayFormat("hh:mm");

    QTime time(0,0,0);
    meeting_duration->setTime(time.addSecs(req->value(rec.indexOf("duration")).toInt()*60));

    btn_action = new QPushButton("Mettre à jour");
    btn_cancel = new QPushButton("Annuler");
    btn_del = new QPushButton("Supprimer cette réunion");

    global_settings = new QSettings("../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);

    QSqlQuery *reqOrganizer = new QSqlQuery();
    reqOrganizer->prepare("SELECT Users.address FROM Meeting,Users WHERE Meeting.id = :meeting_id AND Users.id = Meeting.organizer");
    reqOrganizer->bindValue(":meeting_id", meeting_id);
    reqOrganizer->exec();
    QSqlRecord recOrganizer = reqOrganizer->record();
    reqOrganizer->next();

    // Enable Item if user is not organizer
    if(reqOrganizer->value(recOrganizer.indexOf("address")).toString() != global_settings->value("Send/smtp_user").toString())
    {
        btn_del->setEnabled(false);
        btn_action->setEnabled(false);
        meeting_dt_end->setEnabled(false);
        meeting_dt_begin->setEnabled(false);
        meeting_duration->setEnabled(false);
    }

    cb_organizer = new QComboBox();
    cb_organizer->setEnabled(false);

    QSqlQuery *reqUser = new QSqlQuery();

    reqUser->prepare("SELECT * FROM Users WHERE id = :id_user");
    reqUser->bindValue(":id_user", req->value(rec.indexOf("organizer")).toString());
    QString organiz(req->value(rec.indexOf("organizer")).toString());
    reqUser->exec();
    QSqlRecord recUser = reqUser->record();
    while(reqUser->next())
    {
        cb_organizer->addItem(reqUser->value(recUser.indexOf("address")).toString());
    }

    cb_users = new QComboBox();

    model_users = new QStandardItemModel();
    int i = 0;

    QSqlQuery *reqUsersMeeting = new QSqlQuery();
    reqUsersMeeting->prepare("SELECT * FROM UsersMeeting usermeeting INNER JOIN Users user ON user.id = usermeeting.id_user WHERE usermeeting.id_meeting = :id_meeting and present != 0");
    reqUsersMeeting->bindValue(":id_meeting", meeting_id);
    reqUsersMeeting->exec();
    QSqlRecord recUserMeeting = reqUsersMeeting->record();
    while(reqUsersMeeting->next())
    {
        User user(reqUsersMeeting->value(recUserMeeting.indexOf("id_user")).toInt(),reqUsersMeeting->value(recUserMeeting.indexOf("address")).toString());

        QStandardItem *item = new QStandardItem();
        item->setText(user.address());

        QVariant data;
        data.setValue(user);
        item->setData(data);

        model_users->setItem(i,item);
        i++;
    }

    cb_users->setModel(model_users);

    req->first();

    cb_room = new QComboBox();
    cb_room->setEnabled(false);

    QSqlQuery *reqRoom = new QSqlQuery();

    reqRoom->prepare("SELECT * FROM Room WHERE id = :id_room");
    reqRoom->bindValue(":id_room", req->value(rec.indexOf("room")).toString());
    QString room(req->value(rec.indexOf("room")).toString());
    reqRoom->exec();
    QSqlRecord recRoom = reqRoom->record();
    while(reqRoom->next())
    {
        cb_room->addItem(reqRoom->value(recRoom.indexOf("name")).toString());
    }

    id_room = req->value(rec.indexOf("id")).toInt();

    QFormLayout *fl_data = new QFormLayout;
    fl_data->addRow("Libellé:", lb_label);
    fl_data->addRow("Début:", meeting_dt_begin);
    fl_data->addRow("Fin:", meeting_dt_end);
    fl_data->addRow("Durée:", meeting_duration);
    fl_data->addRow("Organisateur:", cb_organizer);
    fl_data->addRow("Invité(s):", cb_users);
    fl_data->addRow("Salle:", cb_room);

    QHBoxLayout *layout_buttons = new QHBoxLayout;
    layout_buttons->setAlignment(Qt::AlignRight);
    layout_buttons->addWidget(btn_del);
    layout_buttons->addWidget(btn_action);
    layout_buttons->addWidget(btn_cancel);

    QVBoxLayout *layout_main = new QVBoxLayout;
    layout_main->addLayout(fl_data);
    layout_main->addLayout(layout_buttons);

    setLayout(layout_main);

    connect(btn_del, SIGNAL(clicked()), this, SLOT(deleteMeeting()));
    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(btn_action, SIGNAL(clicked()), this, SLOT(updateMeeting()));
}

void DetailMeeting::sendEmailDeleteMeeting(int id_meeting,QString date)
{
    global_settings = new QSettings("../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);

    if(global_settings->value("Send/smtp_security").toInt() == 1)
        smtp = new SmtpClient(global_settings->value("Send/smtp_server").toString(), global_settings->value("Send/smtp_port").toInt(), SmtpClient::SslConnection);
    else
        smtp = new SmtpClient(global_settings->value("Send/smtp_server").toString(), global_settings->value("Send/smtp_port").toInt());

    smtp->setUser(global_settings->value("Send/smtp_user").toString());
    smtp->setPassword(global_settings->value("Send/smtp_password").toString());

    QSqlQuery query;
    QString sql("SELECT * FROM Meeting,Users,UsersMeeting where id_meeting = " + QString::number(id_meeting));
    query.prepare("SELECT * FROM Meeting,Users,UsersMeeting where id_meeting = :id_meeting AND UsersMeeting.id_user = Users.id AND UsersMeeting.id_meeting = Meeting.id");
    query.bindValue(":id_meeting", id_meeting);
    query.exec();
    QSqlRecord rec = query.record();

    smtp->connectToHost();
    smtp->login();
    while(query.next())
    {
        MimeMessage message;

        message.setSender(new EmailAddress(
                              global_settings->value("Account/user_email").toString(),
                              global_settings->value("Account/user_name").toString()
                              ));

        QString email(query.value(rec.indexOf("address")).toString());
        message.addRecipient(new EmailAddress(query.value(rec.indexOf("address")).toString(), ""));
        message.setSubject("Suppression d'une reunion");

        MimeHtml * text = new MimeHtml;
        text->setHtml("<html><b>La réunion planifié le " + date  + " a été supprimé.</b></html>");

        message.addPart(text);

        smtp->sendMail(message);
    }
    smtp->quit();

    close();
}

void DetailMeeting::sendEmailUpdateMeeting(int id_meeting,QString date)
{
    global_settings = new QSettings("../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);

    if(global_settings->value("Send/smtp_security").toInt() == 1)
        smtp = new SmtpClient(global_settings->value("Send/smtp_server").toString(), global_settings->value("Send/smtp_port").toInt(), SmtpClient::SslConnection);
    else
        smtp = new SmtpClient(global_settings->value("Send/smtp_server").toString(), global_settings->value("Send/smtp_port").toInt());

    smtp->setUser(global_settings->value("Send/smtp_user").toString());
    smtp->setPassword(global_settings->value("Send/smtp_password").toString());

    QSqlQuery query;
    QString sql("SELECT * FROM Meeting,Users,UsersMeeting where id_meeting = " + QString::number(id_meeting));
    query.prepare("SELECT * FROM Meeting,Users,UsersMeeting where id_meeting = :id_meeting AND UsersMeeting.id_user = Users.id AND UsersMeeting.id_meeting = Meeting.id");
    query.bindValue(":id_meeting", id_meeting);
    query.exec();
    QSqlRecord rec = query.record();

    smtp->connectToHost();
    smtp->login();
    while(query.next())
    {
        MimeMessage message;

        message.setSender(new EmailAddress(
                              global_settings->value("Account/user_email").toString(),
                              global_settings->value("Account/user_name").toString()
                              ));

        QString email(query.value(rec.indexOf("address")).toString());
        message.addRecipient(new EmailAddress(query.value(rec.indexOf("address")).toString(), ""));
        message.setSubject("Modification horaire d'une reunion");

        MimeHtml * text = new MimeHtml;
        text->setHtml("<html><b>La réunion planifié le " + date  + " a été modifié.</b></html>");

        message.addPart(text);

        smtp->sendMail(message);
    }
    smtp->quit();

    close();
}

void DetailMeeting::updateMeeting()
{
    int duration_minute = (meeting_duration->time().hour()*60) + meeting_duration->time().minute();

    QDateTime *date_begin_real = new QDateTime(QDate(meeting_dt_begin->date().year(),meeting_dt_begin->date().month(),meeting_dt_begin->date().day()),meeting_dt_begin->time());

    QString dt_begin;
    dt_begin = QString::number(meeting_dt_begin->date().year()) + "/" + QString::number(meeting_dt_begin->date().month()) + "/" + QString::number(meeting_dt_begin->date().day()) + " " + QString::number(meeting_dt_begin->time().hour()) + ":" + QString::number(meeting_dt_begin->time().minute());

    QString dt_end;
    dt_end = QString::number(meeting_dt_end->date().year()) + "/" + QString::number(meeting_dt_end->date().month()) + "/" + QString::number(meeting_dt_end->date().day()) + " " + QString::number(meeting_dt_end->time().hour()) + ":" + QString::number(meeting_dt_end->time().minute());

    QSqlQuery query;
    query.prepare("SELECT * FROM Meeting where room = :room");
    query.bindValue(":room", id_room);
    query.exec();
    QSqlRecord rec = query.record();

    while(query.next())
    {
        QStringList date_begin = query.value(rec.indexOf("date_begin")).toString().split(" ").at(0).split("/");
        QStringList time_begin = query.value(rec.indexOf("date_begin")).toString().split(" ").at(1).split(":");

        QDate date_begin_edit(date_begin.at(0).toInt(),date_begin.at(1).toInt(),date_begin.at(2).toInt());
        QTime time_begin_edit(time_begin.at(0).toInt(),time_begin.at(1).toInt(),0);

        QStringList date_end_bis = query.value(rec.indexOf("date_end")).toString().split(" ").at(0).split("/");
        QStringList time_end = query.value(rec.indexOf("date_end")).toString().split(" ").at(1).split(":");

        QDate date_end_edit(date_end_bis.at(0).toInt(),date_end_bis.at(1).toInt(),date_end_bis.at(2).toInt());
        QTime time_end_edit(time_end.at(0).toInt(),time_end.at(1).toInt(),0);

        QDateTime datetime_begin(date_begin_edit,time_begin_edit);
        QDateTime datetime_end(date_end_edit,time_end_edit);

        if(date_begin_real->operator >(datetime_begin) && date_begin_real->operator <(datetime_end))
        {
            QMessageBox::critical(this, "Salle indisponible", "La salle selectionné est indisponible.");
            return;
        }
    }

    query.prepare("SELECT * FROM Meeting where id_meeting = :id_meeting");
    query.bindValue(":id_meeting", meeting_id);
    query.exec();
    rec = query.record();
    query.next();

    sendEmailUpdateMeeting(meeting_id,dt_begin);

    query.prepare("Update Meeting set date_begin = :date_begin , date_end =:date_end , duration = :duration WHERE id = :id_meeting");
    query.bindValue(":date_begin", dt_begin);
    query.bindValue(":date_end", dt_end);
    query.bindValue(":duration", duration_minute);
    query.bindValue(":id_meeting", meeting_id);
    query.exec();

    this->close();
    emit notifyRefreshList();
}

void DetailMeeting::quit(){
    this->quit();
}

void DetailMeeting::deleteMeeting()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Meeting where id_meeting = :id_meeting");
    query.bindValue(":id_meeting", meeting_id);
    query.exec();
    QSqlRecord rec = query.record();
    query.next();

    sendEmailDeleteMeeting(meeting_id,query.value(rec.indexOf("date_begin")).toString());

    query.prepare("DELETE FROM UsersMeeting where id_meeting = :id_meeting");
    query.bindValue(":id_meeting", meeting_id);
    query.exec();

    query.prepare("DELETE FROM Meeting where id = :id_meeting");
    query.bindValue(":id_meeting", meeting_id);
    query.exec();

    this->close();
    emit notifyRefreshList();
}
