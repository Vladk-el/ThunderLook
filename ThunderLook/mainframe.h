#ifndef MAINFRAME_H
#define MAINFRAME_H

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

        void addMenus();
        void addActions();
        void addToolBars();
        void addLayouts();
        void addSlotsConnexions();

    signals:

    public slots:

    private:
        // Menus
        QMenu * menu_thunderlook;
        QMenu * menu_file;

        // Actions
        QAction * action_quit;
        QAction * action_new_mail;

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














