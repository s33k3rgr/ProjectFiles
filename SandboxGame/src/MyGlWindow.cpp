#include <GL/glew.h>
#include "MyGlWindow.h"
#include <cassert>
#include <Vector2D.h>
#include <Clock.h>
#include <QKeyEvent>

using Math::Vector2D;

namespace
{

	Vector2D verts[] =
{
	Vector2D(+0.0f, +0.1f),
	Vector2D(-0.1f, -0.1f),
	Vector2D(+0.1f, -0.1f),
};

	const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);
	Vector2D shipPosition;
	Vector2D shipVelocity;
	Timing::Clock clock1;
	float ACCELERATION;
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
	glViewport(0, 0, width(), height());
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	Vector2D translatedVerts[NUM_VERTS];
	for(unsigned int i = 0; i < NUM_VERTS; i++)
		translatedVerts[i] = verts[i] + shipPosition;

	glBufferSubData(
		GL_ARRAY_BUFFER, 0,
		sizeof(translatedVerts),
		translatedVerts);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}


void MyGlWindow::myUpdate()
{
	clock1.newFrame();
	UpdateVelocity();
	shipPosition = shipPosition +
		shipVelocity * clock1.timeElapsedLastFrame();
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
		shipVelocity.y += ACCELERATION;
	if (e->key() == Qt::Key_Down)
		shipVelocity.y -= ACCELERATION;
	if (e->key() == Qt::Key_Right)
		shipVelocity.x += ACCELERATION;
	if (e->key() == Qt::Key_Left)
		shipVelocity.x -= ACCELERATION;

}

void MyGlWindow::UpdateVelocity()
{
	ACCELERATION = 0.4f * clock1.timeElapsedLastFrame();
}
