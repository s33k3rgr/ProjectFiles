#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H


namespace Entities
{

	class Entity;
	class Component
	{
	    friend class Entity;
		Entity* parent;
	public:
        Entity* getParent() const { return parent; }
		virtual bool initialize() { return true; }
		virtual bool shutdown() { return true; }
		virtual void update() {}
	};

}
#endif
