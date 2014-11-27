#include <QApplication>
#include <QWidget>
#include "MyGlWindow.h"
#include <GLFW/glfw3.h>


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
	MyGlWindow myGlWindow;
	if ( !myGlWindow.initialize())
		return -1;
	myGlWindow.show();
	int errorCode = application.exec();
	if (! myGlWindow.shutdown() )
		errorCode |= 1;

	return errorCode;
}


