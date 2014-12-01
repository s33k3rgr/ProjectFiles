#include <GL/glew.h>
#include "MyGlWindow.h"
#include <cassert>
#include <Vector3D.h>
#include <Matrix2DH.h>
#include <Clock.h>
#include <QKeyEvent>
#include <Profile.h>
#include <Profiler.h>
#include "TypeDefs.h"

using Math::Matrix2DH;
using Math::Vector3D;
using je::uint;


namespace
{

    Vector3D verts[] =
    {
        Vector3D(+0.0f, +0.14142135623f, 1.0f),
        Vector3D(-0.1f, -0.1f, 1.0f),
        Vector3D(+0.1f, -0.1f, 1.0f),
    };

	const uint NUM_VERTS = sizeof(verts) / sizeof(*verts);
	Vector3D transformedVerts[NUM_VERTS];
	Vector3D shipPosition;
	Vector3D shipVelocity;
	float shipOrientation = 0.0f;
	Timing::Clock clock1;
	float ACCELERATION;
	float ANGULAR_MOVEMENT = 0.3f;
	Vector3D directionToAccelerate;
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



void MyGlWindow::doGl()
{
    // Setup Viewport
    int minSize = std::min(width(), height());
	Vector3D viewportLocation;
	viewportLocation.x = width() / 2 - minSize / 2;
	viewportLocation.y = height() / 2 - minSize / 2;
	glViewport(viewportLocation.x, viewportLocation.y,
		minSize, minSize);

	// Setup data pointers
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Send data to OpenGL
	glBufferSubData(
		GL_ARRAY_BUFFER, 0,
		sizeof(transformedVerts),
		transformedVerts);

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 3);
}



void MyGlWindow::draw()
{
	Matrix2DH op;
	Matrix2DH translator = Matrix2DH::translate(shipPosition.x, shipPosition.y);
	Matrix2DH rotator = Matrix2DH::rotateZ(shipOrientation);

	{
	    PROFILE("Matrix Multiplication");
	    op = translator * rotator;
	}

	{
	    PROFILE("Transformation");
	    for(uint i = 0; i < NUM_VERTS; i++)
            transformedVerts[i] = op * verts[i];
	}
    doGl();
}


void MyGlWindow::paintGL()
{
	update();
	draw();
}


void MyGlWindow::update()
{
    clock1.lap();
	profiler.newFrame();
	UpdateVelocity();
	shipPosition += shipVelocity * clock1.lastLapTime();
}



void MyGlWindow::myUpdate()
{
    repaint();
}


bool MyGlWindow::shutdown()
{
	bool ret = true;
	profiler.shutdown();
	ret &= clock1.shutdown();
	return ret;
}

bool MyGlWindow::initialize()
{
	bool ret = true;
	profiler.initialize("profiles.csv");
	ret &= clock1.initialize();
	return ret;
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
	ACCELERATION = 0.4f * clock1.lastLapTime();
	directionToAccelerate = Vector3D(-sin(shipOrientation), cos(shipOrientation));
}
