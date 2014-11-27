#ifndef MYGLWINDOW_H
#define MYGLWINDOW_H
#include <QtOpenGL/QGLWidget>
#include <QTimer>

class MyGlWindow : public QGLWidget
{
	Q_OBJECT

	GLuint vertexBufferID;
	QTimer myTimer;
protected:
	void initializeGL();
	void paintGL();
	void keyPressEvent(QKeyEvent*);
private slots:
	void myUpdate();
	void UpdateVelocity();
public:
	bool initialize();
	bool shutdown();

};

#endif // MYGLWINDOW_H
