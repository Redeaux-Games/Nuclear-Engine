#include "Engine\Components/EntityInfoComponent.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <Base/Math/gtx/quaternion.hpp>
namespace REDxEngine
{
	namespace Components
	{
		EntityInfoComponent::EntityInfoComponent()
		{

		}

		EntityInfoComponent::EntityInfoComponent(Math::Matrix4 Transform)
			: mTransform(Transform)
		{
		}

		EntityInfoComponent::EntityInfoComponent(Math::Vector3 position, Math::Quaternion rotation)
			: mTransform(position, rotation)
		{
		}

		EntityInfoComponent::~EntityInfoComponent()
		{
		}
	}
}
