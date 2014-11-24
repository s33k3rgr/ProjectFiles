#include <QApplication>
#include <QWidget>
#include "MyGlWindow.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGlWindow myGlWindow;
    myGlWindow.show();
    return a.exec();
}


