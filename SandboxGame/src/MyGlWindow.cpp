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

    Vector3D shipVerts[] =
	{
		Vector3D(+0.0f, +0.14142135623f, 1),
		Vector3D(-0.1f, -0.1f, 1),
		Vector3D(+0.1f, -0.1f, 1)
	};

    Vector3D boundaryVerts[] =
	{
		Vector3D(+0.0f, +1.0f, +0.0f),
		Vector3D(-1.0f, +0.0f, +0.0f),
		Vector3D(+0.0f, -1.0f, +0.0f),
		Vector3D(+1.0f, +0.0f, +0.0f)
	};

	GLushort  boundaryIndices[] = {0, 1, 1, 2, 2, 3, 3, 0} ;

	Vector3D lerpPoints[] =
	{
		Vector3D(0.5f, 0.5f, 0.0f),
		Vector3D(-0.5f, 0.5f, 0.0f),
		Vector3D(-0.5f, -0.5f, 0.0f),
		Vector3D(0.5f, -0.5f, 0.0f),
	};
	const uint NUM_LERP_POINTS = sizeof(lerpPoints) / sizeof(*lerpPoints);
	uint sourceLerpPoint;
	uint destinationLerpPoint;
	float lerpAlpha;
	Vector3D currentLerperPosition;

	const uint NUM_SHIP_VERTS = sizeof(shipVerts) / sizeof(*shipVerts);
	const uint NUM_BOUNDARY_VERTS = sizeof(boundaryVerts) / sizeof(*boundaryVerts);
	GLuint shipVertexBufferID;
	GLuint boundaryVertexBufferID;
	GLuint boundaryIndexBufferID;
	Vector3D transformedVerts[NUM_SHIP_VERTS];
	Vector3D shipPosition;
	Vector3D oldShipPosition;
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
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &shipVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, shipVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shipVerts),
		NULL, GL_DYNAMIC_DRAW);


    glGenBuffers(1, &boundaryVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, boundaryVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boundaryVerts),
		boundaryVerts, GL_STATIC_DRAW);

	glGenBuffers(1, &boundaryIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundaryIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boundaryIndices),
		boundaryIndices, GL_STATIC_DRAW);

	connect(&myTimer, SIGNAL(timeout()),
		this, SLOT(myUpdate()));

	myTimer.start(0);
}



void MyGlWindow::doGl()
{
    // Setup Viewport
	glViewport(0, 0, width(), height());

	// Setup data pointers
	glBindBuffer(GL_ARRAY_BUFFER, shipVertexBufferID);

	// Send data to OpenGL
	glBufferSubData(
		GL_ARRAY_BUFFER, 0,
		sizeof(transformedVerts),
		transformedVerts);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Now draw the boundaries
	glBindBuffer(GL_ARRAY_BUFFER, boundaryVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, 0);
}


void MyGlWindow::lerpTheLerper()
{
	lerpAlpha += clock1.lastLapTime();
	if(lerpAlpha >= 1.0f)
	{
		lerpAlpha = 0.0f;
		targetNextLerpPoint();
	}
	const Vector3D& source = lerpPoints[sourceLerpPoint];
	const Vector3D& destination = lerpPoints[destinationLerpPoint];
	currentLerperPosition = lerp(lerpAlpha, source, destination);
}


void  MyGlWindow::targetNextLerpPoint()
{
	sourceLerpPoint = destinationLerpPoint;
	destinationLerpPoint = (destinationLerpPoint + 1) % NUM_LERP_POINTS;
}




void MyGlWindow::draw()
{
	Matrix2DH op;
	Matrix2DH translator = Matrix2DH::translate(shipPosition.x, shipPosition.y);
	Matrix2DH rotator = Matrix2DH::rotateZ(shipOrientation);

	float aspectRatio = static_cast<float>(width()) / height();
	Matrix2DH scale;

	if(aspectRatio > 1)
		scale = Matrix2DH::scale(1 / aspectRatio, 1);
	else
		scale = Matrix2DH::scale(1, aspectRatio);

    op = translator * scale * rotator;
    for(uint i = 0; i < NUM_SHIP_VERTS; i++)
        transformedVerts[i] = op * shipVerts[i];

    glClear(GL_COLOR_BUFFER_BIT);
	doGl();
	translator = Matrix2DH::translate(currentLerperPosition.x, currentLerperPosition.y);
	op = translator * scale;
	for(uint i = 0; i < NUM_SHIP_VERTS; i++)
		transformedVerts[i] = op * shipVerts[i];
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
    oldShipPosition = shipPosition;
	shipPosition += shipVelocity * clock1.lastLapTime();
	handleBoundaries();
	lerpTheLerper();
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
	if(NUM_LERP_POINTS > 1)
	{
		lerpAlpha = 0.0f;
		destinationLerpPoint = 1;
		targetNextLerpPoint();
	}
	else
	{
		ret = false;
	}
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


void MyGlWindow::handleBoundaries()
{

	for(uint i = 0; i < NUM_BOUNDARY_VERTS; i++)
	{
		const Vector3D& first = boundaryVerts[i];
		const Vector3D& second = boundaryVerts[(i + 1) % NUM_BOUNDARY_VERTS];

		Vector3D wall = second - first;
		Vector3D normal = wall.perpCcwXy().normalized();
		Vector3D respectiveShipPosition = shipPosition - first;
		float dotResult = normal.dot(respectiveShipPosition);

		if (dotResult < 0)
		{
			shipVelocity  = shipVelocity - 2 * shipVelocity.projectOnto(normal);
			shipPosition = oldShipPosition;
		}
	}

}
