#include "MeetingWindow.h"
#include "meeting.h"
#include "addmeeting.h"

#include <QDebug>
#include <QtSql>

Q_DECLARE_METATYPE(Meeting);

MeetingWindow::MeetingWindow(QWidget *parent) : QDialog(parent)
{
    id_account = 1;

    this->setFixedWidth(1065);
    this->setFixedHeight(630);

    /*QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","188.165.125.160");
    db.setPort(2981);
    db.setDatabaseName( "thunderlook" );
    db.setUserName( "esgi" );
    db.setPassword( "esgi" );*/

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("meetings.db");
    if (!db.open())
    {
        QString error(db.lastError().text());

        for(int i = 0 ; i < QSqlDatabase::drivers().length() ; i++)
            qDebug() << QSqlDatabase::drivers().at(i);

        //QSqlError error = QSqlDatabase::lastError();
        qDebug() << db.lastError().text() << "Impossible de se connecter à la base de données." << endl;
        return;
    }

    qRegisterMetaType<Meeting>("Meeting");

    widget_central = new QWidget();
    model = new QStandardItemModel();

    view = new QTableView();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setFocusPolicy(Qt::NoFocus);
    view->setSelectionMode(QAbstractItemView::SingleSelection);

    calendar = new QCalendarWidget();
    calendar->setGridVisible(true);
    calendar->setMaximumWidth(280);
    calendar->setMaximumHeight(200);
    calendar->setFirstDayOfWeek(Qt::Monday);

    // on prépare le header vertical
    for(int i = 8; i < 20; ++i) { // 8h - 20h
        QString hour = QString::number(i);
        hours   << hour + "h00"
                << hour + "h30";
    }

    btn_add = new QPushButton("Organiser une réunion");

    QFont *f = new QFont( "Segoe UI", 24, QFont::Bold);
    label_week = new QLabel("");
    label_week->setFont(*f);
    label_week->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout_agenda = new QVBoxLayout();
    layout_agenda->addWidget(label_week);
    layout_agenda->addWidget(view);

    QVBoxLayout *layout_tools = new QVBoxLayout();
    layout_tools->addWidget(calendar);
    layout_tools->addWidget(btn_add);
    layout_tools->addStretch();

    QHBoxLayout *layout_main = new QHBoxLayout();
    layout_main->addLayout(layout_tools);
    layout_main->addLayout(layout_agenda);

    this->setLayout(layout_main);
    //this->setLayout(widget_central);
    //this->setCentralWidget(widget_central);

    refreshList();

    connect(calendar, SIGNAL(clicked(QDate)), this, SLOT(refreshList()));
    connect(calendar, SIGNAL(currentPageChanged(int,int)), this, SLOT(refreshList()));
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(displayInfo()));
    connect(btn_add, SIGNAL(clicked()), this, SLOT(addMeeting()));
}

MeetingWindow::~MeetingWindow()
{
}

void MeetingWindow::refreshList()
{
    view->reset();
    view->clearSpans();
    QDate date = calendar->selectedDate();

    label_week->setText("Semaine n°" + QString::number(date.weekNumber()));

    view->verticalHeader()->setDefaultSectionSize(20);

    QStringList days;
    days << "Lundi" << "Mardi" << "Mercredi" << "Jeudi" << "Vendredi" << "Samedi" << "Dimanche";
    view->verticalHeader()->show();
    view->verticalHeader()->setDefaultSectionSize(20);

    view->reset();
    view->clearSpans();

    delete model;
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(days);
    model->setVerticalHeaderLabels(hours);


    // Recherche de la date de début de semaine
    while(date.dayOfWeek() != 1){ // on cherche le lundi de la semaine
        date = date.addDays(-1);
    }

    bool ok = true;
    int i = 0;
    while(date.dayOfWeek() <= 7 && ok){ // on parcourt la semaine (1 à 7)
        QSqlQuery query;
        QSqlRecord rec;
        QString dateSQL;
        dateSQL = QString::number(date.year()) + "/" + QString::number(date.month()) + "/" + QString::number(date.day());

        QString sql("SELECT * FROM Meeting,UsersMeeting WHERE (organizer ='" + QString::number(id_account) + "' OR USersMeeting.id_user = '" + QString::number(id_account) + "')  AND  date_begin like '" + dateSQL + " %'");
        query.exec("SELECT * FROM Meeting,UsersMeeting WHERE (organizer ='" + QString::number(id_account) + "' OR USersMeeting.id_user = '" + QString::number(id_account) + "')  AND  date_begin like '" + dateSQL + " %'");
        rec = query.record();
        while(query.next())
        {
            int noCol = date.dayOfWeek() - 1;

            // Recup hour and minute
            QStringList time_begin = query.value(1).toString().split(" ").at(1).split(":");

            int no_row_begin = (time_begin.at(0).toInt() - 8) * 2 + time_begin.at(1).toInt() / 30;
            int duration = query.value(3).toInt() / 30;

            for(int pos = 0; pos < duration; pos++){
                Meeting m(query.value(rec.indexOf("id")).toInt(), pos, duration);

                QStandardItem *item = new QStandardItem();
                if(pos == 0){ item->setText(query.value(rec.indexOf("title")).toString()); }

                QColor color;
                color.setNamedColor(query.value(rec.indexOf("color")).toString());

                QVariant data;
                data.setValue(m);
                item->setData(data);
                item->setBackground(color);

                model->setItem(no_row_begin + pos, noCol, item);
            }

            view->setSpan(no_row_begin, noCol, duration, 1);

            i++;

            qDebug() << query.value(4).toString() << endl;
        }

        if(date.dayOfWeek() == 7){ ok = false; } // incrementation
        else date = date.addDays(1);
    }

    view->setModel(model);
}

void MeetingWindow::displayInfo() {
    QModelIndex index = view->selectionModel()->currentIndex();
    if(index.isValid()){
        if(model->itemFromIndex(index)->text() != "")
        {
            Meeting m = model->item(index.row(), index.column())->data().value<Meeting>();
            DetailMeeting *meeting_details = new DetailMeeting(m.id());
            connect(meeting_details, SIGNAL(notifyRefreshList()), this, SLOT(refreshList()));
            meeting_details->exec();

            qDebug() << m.id() << endl;
        }
    }
}

void MeetingWindow::addMeeting() {
    AddMeeting *meeting = new AddMeeting(this,1);
    connect(meeting, SIGNAL(notifyRefreshList()), this, SLOT(refreshList()));
    meeting->exec();
}
