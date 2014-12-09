#ifndef ENGINE_RENDERABLE_H
#define ENGINE_RENDERABLE_H
#include "Matrix2DH.h"


namespace Rendering
{
	class Geometry;
	class Renderable
	{
		friend class Renderer;
		const Geometry* what;
	public:
		Math::Matrix2DH where;
	};
}


#endif
