#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H
#include "TypeDefs.h"
#include "Vector3D.h"

namespace Entities
{
	class Component;
	class Entity
	{
		static const je::uint NUM_MAX_COMPONENTS = 10;
		Component* components[NUM_MAX_COMPONENTS];
		je::uint numComponents;
	public:
		Math::Vector3D position;
		float orientation;
		Entity();
		bool initialize();
		bool shutdown();
		void addComponent(Component* component);
		void update();
		template<class T>
		T* getComponent() const;
	};

	template<class T>
	T* Entity::getComponent() const
	{
		for(je::uint i = 0; i < numComponents; i++)
		{
			T* ret = dynamic_cast<T*>(components[i]);
			if(ret != 0)
				return ret;
		}
		return 0;
	}
}

#endif
