#ifndef MYGLWINDOW_H
#define MYGLWINDOW_H
#include <QtOpenGL/QGLWidget>
#include <QTimer>

class MyGlWindow : public QGLWidget
{
	//Q_OBJECT

	GLuint vertexBufferID;
	QTimer myTimer;
protected:
	void initializeGL();
	void paintGL();
//private slots:
	//void myUpdate();

};

#endif // MYGLWINDOW_H
