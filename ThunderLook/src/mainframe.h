#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "sendnewemail.h"
#include "settings.h"
#include "initconfig.h"
#include "previewedemail.h"
#include "widgetpreviewed.h"
#include "detailledemail.h"
#include "contact.h"

#include "global.h"

#include "../includes/popClient/popclient.h"
#include "../includes/Meeting/MeetingWindow.h"
#include "../includes/SQL/sqllitehelper.h"

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
#include <QResizeEvent>
#include <QScrollArea>


class MainFrame : public QMainWindow
{
    Q_OBJECT

    public:
        MainFrame();
        ~MainFrame();

        void setSettings();

        void initConfig();
        void init();
        void setSize();
        void setMenus();
        void setActions();
        void setToolBars();
        void setLayouts();
        void setSlotsConnexions();
        bool getEmails();

        void resizeEvent(QResizeEvent *);

        // Getters
        QSettings * getSettings();

    signals:

    public slots:
        void slot_new_mail();
        void slot_refresh_mails();
        void slot_new_meeting();
        void slot_configure_account();
        void slot_launch();
        void slot_get_email_indice(int);

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
        QAction * action_new_meeting;
        QAction * action_refresh_mails;
        QAction * action_configure_account;

        // ToolBars
        QToolBar * toolbar_top;

        // QistView && Model
        QStringListModel * model_folders;
        QListView * view_list_folders;

        // Widgets
        QWidget * widget_central;
        WidgetPreviewed * widget_previewed;
        QWidget * widget_detailled;

        // Layouts
        QHBoxLayout * layout_main;
        QVBoxLayout * layout_detailled;

        // QList<MimeMessage *>
        QList<MimeMessage *> messages;

        // DetailledEmail
        DetailledEmail * detailledEmail;

        // Database
        QSqlDatabase db;

};

#endif // MAINFRAME_H














