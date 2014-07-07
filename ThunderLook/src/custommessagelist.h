#ifndef CUSTOMMESSAGELIST_H
#define CUSTOMMESSAGELIST_H

#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QDebug>

class CustomMessageList : public QWidget
{
    Q_OBJECT

    public:
        CustomMessageList(QWidget *parent = 0);

    signals:

    public slots:
        void clicked( const QModelIndex & index);

        void listButtonClicked(const QModelIndex &index);

    private:

        QListView* _view;
        QStandardItemModel _model;
};

#endif // CUSTOMMESSAGELIST_H
