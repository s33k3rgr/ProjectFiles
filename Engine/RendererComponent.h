#ifndef ENGINE_RENDERER_COMPONENT_H
#define ENGINE_RENDERER_COMPONENT_H
#include "Component.h"
namespace Rendering { class Renderable; }

namespace Entities
{
	class RendererComponent : public Component
	{
        Rendering::Renderable* renderable;
	public:
        void setData(Rendering::Renderable* renderable);
		void update();
	};
}

#endif

