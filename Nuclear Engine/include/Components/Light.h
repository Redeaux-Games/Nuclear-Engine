#pragma once
#include <NE_Common.h>
#include <API\Color.h>
#include <Math\Math.h>
#include <Renderer\Renderer.h>

namespace NuclearEngine {

	namespace Components {

		namespace Internal {

			struct Shader_Material_Struct
			{
				Math::Vector4  Emissive;
				Math::Vector4  Ambient;
				Math::Vector4  Diffuse;
				Math::Vector4  Specular;
				Math::Vector4  SpecularPower_UseTexture;
			};

			struct NEAPI Shader_Light_Struct
			{
				Math::Vector4 Position;
				Math::Vector4 Direction;
				Math::Vector4 Attenuation_Intensity;
				Math::Vector4 InnerCutOf_OuterCutoff;
				Math::Vector4 Color;
			};
		}

		struct NEAPI Light
		{
			friend class Core::Renderer;
		public:
			enum Type
			{
				DirectionalLight = 0,
				PointLight = 1,
				SpotLight = 2
			};

			Light(Type type);
			~Light();

			void SetType(Type type);

			void SetColor(API::Color color);

			void SetPosition(Math::Vector3 pos);

			void SetDirection(Math::Vector3 dir);

			void SetIntensity(float intensity);

			void SetAttenuation(Math::Vector3 att);

			void SetSpotlightCone(Math::Vector2 cutoff_outercutoff);

		protected:
			Internal::Shader_Light_Struct data;
		};
	}
}