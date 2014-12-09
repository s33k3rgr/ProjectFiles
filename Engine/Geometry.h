#ifndef ENGINE_GEOMETRY_H
#define ENGINE_GEOMETRY_H

#include "TypeDefs.h"
namespace Math { struct Vector3D; }
using je::uint;
using je::ushort;

namespace Rendering
{
	class Geometry
	{
		friend class Renderer;
		const Math::Vector3D* vertices;
		uint numVerts;
		const ushort* indices;
		uint numIndices;
		GLenum renderMode;
	};

}
#endif
