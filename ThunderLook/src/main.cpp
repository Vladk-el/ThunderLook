#include <QApplication>
#include "global.h"

int smtp_test();

int main(int argc, char * argv[]){
    QApplication app(argc, argv);

    MainFrame frame;

    //Settings settings;

    return app.exec();
}
