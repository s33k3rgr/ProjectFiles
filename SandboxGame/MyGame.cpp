#include "MyGame.h"
#include <cstdlib>
#include <Geometry.h>
using Rendering::Geometry;
using Math::Vector3D;

MyGame::MyGame()
{
	Vector3D shipVertData[] =
	{
		Math::Vector3D(+0.0f, +0.14142135623f, 1),
		Math::Vector3D(-0.1f, -0.1f, 1),
		Math::Vector3D(+0.1f, -0.1f, 1)
	};

	memcpy(shipVerts, shipVertData, sizeof(shipVertData));

	ushort shipIndiceData[] = {0, 1, 2};
	memcpy(shipIndices, shipIndiceData, sizeof(shipIndiceData));
}

bool MyGame::initialize()
{
	if(!renderer.initialize())
		return false;

	connect(&myTimer, SIGNAL(timeout()),
		this, SLOT(update()));

	Geometry* shipGeometry =
		renderer.addGeometry(
			shipVerts, NUM_SHIP_VERTS,
			shipIndices, NUM_SHIP_INDICES);

	shipRenderable =
		renderer.addRenderable(shipGeometry);

	//ship.addComponent(??

	/*Renderable* lerpInstance =
		renderer.addRenderable(shipGeometry);*/

	return true;
}

bool MyGame::shutdown()
{
	return renderer.shutdown();
}


void MyGame::update()
{
	/*shipInstance->where = Matrix2DH::translate(shipPosition);
	lerpInstance->where = Matrix2DH::translate(lerperPosition);*/
	renderer.renderScene();
}

void MyGame::go()
{
	myTimer.start();
}


