#include <QApplication>
#include <QWidget>
#include "MyGame.h"


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

	MyGame myGame;

	if(!myGame.initialize())
		return -1;
	myGame.go();

	int errorCode = application.exec();
	if (! myGame.shutdown() )
		errorCode |= 1;
	return errorCode;
}


