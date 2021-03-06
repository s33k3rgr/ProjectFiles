#ifndef MY_GAME_H
#define MY_GAME_H
#include <QObject>
#include <QTimer>
#include <Entity.h>
#include <RendererComponent.h>
#include <PhysicsComponent.h>
#include <Renderer.h>
#include <Vector3D.h>
namespace Rendering { class Renderable; }

class MyGame : public QObject
{
	Q_OBJECT
	Entities::Entity ship;
	Entities::RendererComponent shipRenderer;
	Entities::PhysicsComponent shipPhysics;

	QTimer myTimer;
	Rendering::Renderer renderer;
	Rendering::Renderable* shipRenderable;
	Rendering::Renderable* lerpRenderable;

	static const uint NUM_SHIP_VERTS = 3;
	Math::Vector3D shipVerts[NUM_SHIP_VERTS];

	static const uint NUM_SHIP_INDICES = 3;
	ushort shipIndices[NUM_SHIP_INDICES];

private slots:
	void update();
public:
	MyGame();
	bool initialize();
	bool shutdown();
	void go();

};


#endif
