#include "detailmeeting.h"

Q_DECLARE_METATYPE(User);

DetailMeeting::DetailMeeting(int _meeting_id, QWidget *parent) : QDialog(parent)
{
    meeting_id = _meeting_id;

    setWindowTitle("Détails de la réunion");

    QSqlQuery *req = new QSqlQuery();
    req->prepare("SELECT * FROM meeting m WHERE id = :meeting_id");
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

    btn_action = new QPushButton("Ok");
    btn_cancel = new QPushButton("Annuler");
    btn_del = new QPushButton("Supprimer cette réunion");
    btn_del->setToolTip("Seul l'organisateur peut supprimer la réunion.");

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

    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
    //connect(btn_action, SIGNAL(clicked()), this, SLOT(accept()));
}

void DetailMeeting::quit(){
    this->quit();
}

void DetailMeeting::deleteMeeting(){

}
