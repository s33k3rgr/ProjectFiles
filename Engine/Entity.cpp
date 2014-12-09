#include "Entity.h"
#include <cassert>
#include "Component.h"
#include "TypeDefs.h"

namespace Entities
{

	Entity::Entity()
	{
		numComponents = 0;
		orientation = 0;
	}

	bool Entity::initialize()
	{
		for(je::uint i = 0; i < numComponents; i++)
		{
			if(!components[i]->initialize())
				return false;
		}
		return true;
	}

	bool Entity::shutdown()
	{
		for(je::uint i = 0; i < numComponents; i++)
		{
			if(!components[i]->shutdown())
				return false;
		}
		return true;
	}

	void Entity::addComponent(Component* component)
	{
		assert(numComponents != NUM_MAX_COMPONENTS);
		components[numComponents++] = component;
		component->parent = this;
	}

	void Entity::update()
	{
		for(je::uint i = 0; i < numComponents; i++)
		{
			components[i]->update();
		}
	}


}

