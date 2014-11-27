#include <GL/glew.h>
#include "MyGlWindow.h"
#include <cassert>
#include <Vector2D.h>
#include <Matrix2D.h>
#include <Clock.h>
#include <QKeyEvent>

using Math::Vector2D;
using Math::Matrix2D;
using namespace std;

namespace
{

	Vector2D verts[] =
{
	Vector2D(+0.0f, +0.141421f),
	Vector2D(-0.1f, -0.1f),
	Vector2D(+0.1f, -0.1f),
};

	const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);
	Vector2D shipPosition;
	Vector2D shipVelocity;
	float shipOrientation = 0.0f;
	Timing::Clock clock1;
	float ACCELERATION;
	float ANGULAR_MOVEMENT = 0.3f;
	Vector2D directionToAccelerate;
}

void MyGlWindow::initializeGL()
{
	GLenum errorCode = glewInit();
	assert(errorCode == 0);
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),
		NULL, GL_DYNAMIC_DRAW);

	connect(&myTimer, SIGNAL(timeout()),
		this, SLOT(myUpdate()));

	myTimer.start();
}


void MyGlWindow::paintGL()
{
	int minSize = std::min(width(), height());
	Vector2D viewportLocation;
	viewportLocation.x = width() / 2 - minSize / 2;
	viewportLocation.y = height() / 2 - minSize / 2;
	glViewport(viewportLocation.x, viewportLocation.y,
		minSize, minSize);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	Vector2D transformedVerts[NUM_VERTS];
	Matrix2D op = Matrix2D::rotate(shipOrientation);
	for(unsigned int i = 0; i < NUM_VERTS; i++)
		transformedVerts[i] = shipPosition + (op * verts[i]);

	glBufferSubData(
		GL_ARRAY_BUFFER, 0,
		sizeof(transformedVerts),
		transformedVerts);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}


void MyGlWindow::myUpdate()
{
	clock1.newFrame();
	UpdateVelocity();
	shipPosition += shipVelocity * clock1.timeElapsedLastFrame();
	repaint();
}


bool MyGlWindow::shutdown()
{
	return clock1.shutdown();
}

bool MyGlWindow::initialize()
{
	return clock1.initialize();
}


void MyGlWindow::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Up)
		shipVelocity += directionToAccelerate * ACCELERATION;
	if (e->key() == Qt::Key_Right)
		shipOrientation -= ANGULAR_MOVEMENT;
	if (e->key() == Qt::Key_Left)
		shipOrientation += ANGULAR_MOVEMENT;

}

void MyGlWindow::UpdateVelocity()
{
	ACCELERATION = 0.4f * clock1.timeElapsedLastFrame();
	directionToAccelerate = Vector2D(-sin(shipOrientation), cos(shipOrientation));
}
