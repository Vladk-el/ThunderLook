#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>

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

        // ToolBars
        QToolBar * toolbar_top;


};

#endif // MAINFRAME_H
