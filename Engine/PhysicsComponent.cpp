#include "PhysicsComponent.h"
#include "Entity.h"
#include "GameClock.h"

namespace Entities
{
	void PhysicsComponent::update()
	{
//		velocity += acceleration * gameClock.dt();
//		acceleration = Math::Vector3D;
		getParent()->position += velocity;
//		getParent()->orientation += angularVelocity;
	}

}
