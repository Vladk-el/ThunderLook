#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "sendnewemail.h"

#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QListView>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QStringList>


class MainFrame : public QMainWindow
{
    Q_OBJECT

    public:
        MainFrame();

        void setSize();
        void setMenus();
        void setActions();
        void setToolBars();
        void setLayouts();
        void setSlotsConnexions();

    signals:

    public slots:
        void slot_new_mail();
        void slot_refresh_mails();

    private:
        // Menus
        QMenu * menu_thunderlook;
        QMenu * menu_email;

        // Actions
        QAction * action_quit;
        QAction * action_new_mail;
        QAction * action_refresh_mails;

        // ToolBars
        QToolBar * toolbar_top;

        // QistView && Model
        QStringListModel * model_folders;
        QListView * view_list_folders;

        QStringListModel * model_mails;
        QListView * view_list_mails;

        // Central Widget
        QWidget * widget_central;

        // Layouts
        QHBoxLayout * layout_main;





};

#endif // MAINFRAME_H














