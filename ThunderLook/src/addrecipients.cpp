#include "addrecipients.h"

Q_DECLARE_METATYPE(User);

AddRecipients::AddRecipients(QLineEdit & listRecipients,QWidget *parent) :
    QDialog(parent)
{
    setFixedWidth(300);
    setWindowTitle("Ajouter un destinataire");

    currentListRecipients = &listRecipients;

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

    btn_add_user = new QPushButton("Ajouter le contact");

    QVBoxLayout *layout_btn_add_users = new QVBoxLayout();
    layout_btn_add_users->addWidget(btn_add_user);

    list_users = new QGroupBox("Contacts");
    form_list_users = new QFormLayout();
    form_list_users->addRow("Liste des contacts : ", listView_users);
    form_list_users->addRow("", layout_btn_add_users);

    list_users->setLayout(form_list_users);

    QVBoxLayout *layout_main = new QVBoxLayout;
    layout_main->addWidget(list_users);

    setLayout(layout_main);

    connect(btn_add_user, SIGNAL(clicked()), this, SLOT(addUser()));
    show();
}

void AddRecipients::addUser()
{
    QItemSelectionModel *selectionModel = listView_users->selectionModel();
    currentListRecipients->setText(currentListRecipients->text() + selectionModel->selectedIndexes().at(0).data().toString() + ";");
}
