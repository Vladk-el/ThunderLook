#include "contact.h"

Q_DECLARE_METATYPE(User);

Contact::Contact(QWidget *parent) :
    QDialog(parent)
{
    setFixedWidth(600);
    setWindowTitle("Contacts");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    if (!db.open())
    {
        qDebug() << "Impossible de se connecter à la base de données." << endl;
        return;
    }

    listView_users = new QListView();
    listView_users->setEditTriggers(0);

    QSqlQuery query;
    query.exec("SELECT * FROM Contacts");

    modelListUsers = new QStandardItemModel();

    int index = 0;
    while(query.next())
    {
        User user(query.value(1).toInt(),QString(query.value(2).toString()));

        QStandardItem *item = new QStandardItem();
        item->setText(user.address());

        QVariant data;
        data.setValue(user);
        item->setData(data);

        modelListUsers->setItem(index,item);
        index++;
    }

    listView_users->setModel(modelListUsers);

    QVBoxLayout *layout_add_users = new QVBoxLayout();
    layout_add_users->addWidget(listView_users);

    btn_delete_user = new QPushButton("Supprimer le contact");

    list_users = new QGroupBox("Contacts");
    list_users->setFixedWidth(320);
    form_list_users = new QFormLayout();
    form_list_users->addRow("Liste des contacts : ", listView_users);

    list_users->setLayout(form_list_users);

    name = new QLineEdit();
    firstname = new QLineEdit();
    city = new QLineEdit();
    tel = new QLineEdit();
    fax = new QLineEdit();
    addr = new QLineEdit();

    add_user = new QGroupBox("Ajouter un contact");
    form_add_user = new QFormLayout();
    form_add_user->addRow("Nom : ", name);
    form_add_user->addRow("Prénom : ", firstname);
    form_add_user->addRow("Ville : ", city);
    form_add_user->addRow("Numéro de téléphone : ", tel);
    form_add_user->addRow("Numéro de fax : ", fax);
    form_add_user->addRow("Adresse email : ", addr);
    add_user->setLayout(form_add_user);

    btn_add_user = new QPushButton("Ajouter");

    QVBoxLayout *layout_vertical_add_user = new QVBoxLayout;
    layout_vertical_add_user->addWidget(add_user);
    layout_vertical_add_user->addWidget(btn_add_user);

    QVBoxLayout *layout_vertical_users = new QVBoxLayout;
    layout_vertical_users->addWidget(list_users);
    layout_vertical_users->addWidget(btn_delete_user);

    QHBoxLayout *layout_users = new QHBoxLayout;
    layout_users->addLayout(layout_vertical_users);
    layout_users->addLayout(layout_vertical_add_user);

    QVBoxLayout *layout_main = new QVBoxLayout;
    layout_main->addLayout(layout_users);

    setLayout(layout_main);

    connect(btn_add_user, SIGNAL(clicked()), this, SLOT(addUser()));
    show();
}

void Contact::addUser()
{
    QSqlQuery query;

    query.prepare("INSERT INTO Contacts (name,address,firstname,city,fax,tel) "
                  "VALUES (:name,:address,:firstname,:city,:fax,:tel)");
    query.bindValue(":name", name->text());
    query.bindValue(":address", addr->text());
    query.bindValue(":firstname", firstname->text());
    query.bindValue(":city", city->text());
    query.bindValue(":fax",fax->text());
    query.bindValue(":tel", tel->text());
    query.exec();

    query.exec("SELECT * FROM Contacts");
    modelListUsers = new QStandardItemModel();

    int index = 0;
    while(query.next())
    {
        User user(query.value(1).toInt(),QString(query.value(2).toString()));

        QStandardItem *item = new QStandardItem();
        item->setText(user.address());

        QVariant data;
        data.setValue(user);
        item->setData(data);

        modelListUsers->setItem(index,item);
        index++;
    }

    listView_users->setModel(modelListUsers);
}
