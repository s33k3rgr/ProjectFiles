#include "RendererComponent.h"
#include "Renderable.h"
#include "Matrix2DH.h"
#include "Entity.h"

namespace Entities
{
	void RendererComponent::setData(Rendering::Renderable* renderable)
	{
		this->renderable = renderable;
	}

	void RendererComponent::update()
	{
		renderable->where = Math::Matrix2DH::translate(getParent()->position) *
			Math::Matrix2DH::rotateZ(getParent()->orientation);
	}

}


