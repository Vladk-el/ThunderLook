#include "custommessagelist.h"

CustomMessageList::CustomMessageList(QWidget *parent) :
    QWidget(parent),_view(0){

    _view = new QListView();
    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    /*CustomItemDelegate* itemDelegate = new CustomItemDelegate(_view);
    _view->setItemDelegate( itemDelegate );
    _view->setModel(&_model);

    connect(_view,SIGNAL(clicked(QModelIndex)),this,SLOT(clicked(QModelIndex)));
    connect(itemDelegate,SIGNAL(buttonClicked(QModelIndex)),this,SLOT(listButtonClicked(QModelIndex)));

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget( _view);

    QStandardItem* item = new QStandardItem;
    item->setText("testing1");

    QStandardItem* item1 = new QStandardItem;
    item1->setText("testing2");


    QStandardItem* item2 = new QStandardItem;
    item2->setText("testing3");

    _model.appendRow(item);
    _model.appendRow(item1);
    _model.appendRow(item2);*/
}

void CustomMessageList::listButtonClicked(const QModelIndex &index)
{
    qDebug() << "######### listbutton clicked ######### " << index.row();
}

void CustomMessageList::clicked( const QModelIndex & index)
{
    //qDebug() << "$$$$$$$$$ item clicked $$$$$$$" <<index.row();
}
