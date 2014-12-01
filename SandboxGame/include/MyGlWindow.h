#ifndef MYGLWINDOW_H
#define MYGLWINDOW_H
#include <QtOpenGL/QGLWidget>
#include <QTimer>

class MyGlWindow : public QGLWidget
{
	Q_OBJECT

	QTimer myTimer;
protected:
	void initializeGL();
	void paintGL();
	void keyPressEvent(QKeyEvent*);
private slots:
	void myUpdate();
	void UpdateVelocity();
	void handleBoundaries();
private:
    void update();
    void draw();
    void doGl();
public:
	bool initialize();
	bool shutdown();

};

#endif // MYGLWINDOW_H
