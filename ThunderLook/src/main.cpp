#include <QApplication>
#include "global.h"

int smtp_test();

int main(int argc, char * argv[]){
    QApplication app(argc, argv);

    //MainFrame frame;

    Settings frame;


    frame.show();


    //smtp_test();

    return app.exec();
}
