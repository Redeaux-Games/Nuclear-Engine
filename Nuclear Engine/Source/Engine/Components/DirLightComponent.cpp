#include "Engine\Components\DirLightComponent.h"

namespace REDxEngine
{
	namespace Components
	{
		DirLightComponent::DirLightComponent()
		{
			data.Direction = Math::Vector4(-0.5f, -0.5f, -0.5f, 1.0f);
			data.Color = Math::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		}
		DirLightComponent::~DirLightComponent()
		{
		}
		void DirLightComponent::SetColor(Graphics::Color color)
		{
			data.Color = Math::Vector4(color.r, color.g, color.b, 1.0f);
		}
		void DirLightComponent::SetDirection(Math::Vector3 dir)
		{
			data.Direction = Math::Vector4(dir, 1.0f);
		}
		Internal::Shader_DirLight_Struct DirLightComponent::GetInternalData()
		{
			return data;
		}
	}
}
