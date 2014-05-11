#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "sendnewemail.h"
#include "settings.h"
#include "initconfig.h"

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
#include <QSettings>


class MainFrame : public QMainWindow
{
    Q_OBJECT

    public:
        MainFrame();

        void setSettings();

        void initConfig();
        void init();
        void setSize();
        void setMenus();
        void setActions();
        void setToolBars();
        void setLayouts();
        void setSlotsConnexions();

        // Getters
        QSettings * getSettings();

    signals:

    public slots:
        void slot_new_mail();
        void slot_refresh_mails();
        void slot_configure_account();

    private:
        // QSettings
        QSettings * global_settings;

        // Menus
        QMenu * menu_thunderlook;
        QMenu * menu_email;
        QMenu * menu_account;

        // Actions
        QAction * action_quit;
        QAction * action_new_mail;
        QAction * action_refresh_mails;
        QAction * action_configure_account;

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














