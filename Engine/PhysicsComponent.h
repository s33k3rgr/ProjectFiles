#ifndef ENGINE_PHYSICS_COMPONENT_H
#define ENGINE_PHYSICS_COMPONENT_H
#include "Component.h"
#include "Vector3D.h"

namespace Entities
{

	class PhysicsComponent : public Component
	{
	public:
		Math::Vector3D velocity;
		float angularVelocity;
		Math::Vector3D acceleration;
		PhysicsComponent() { angularVelocity = 0; }
		void update();
	};

}
#endif

