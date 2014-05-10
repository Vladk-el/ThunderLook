#include <QApplication>
#include "global.h"

int smtp_test();

int main(int argc, char * argv[]){
    QApplication app(argc, argv);

    //MainFrame frame;

    QSettings * global_settings = new QSettings("../Thunderlook/data/settings/settings.ini", QSettings::IniFormat);

    Settings settings(global_settings);

    //smtp_test();

    return app.exec();
}
