#include <QApplication>
#include <QWidget>

using namespace std;

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QWidget myWidget;
    myWidget.show();
    return a.exec();
}


