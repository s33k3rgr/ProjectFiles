#include <QApplication>
#include <QWidget>
#include "MyGlWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGlWindow myGlWindow;
    myGlWindow.show();
    return a.exec();
}


