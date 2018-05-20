#pragma once
#include <Base\Math\Math.h>
#include <Engine/Graphics/API/Texture.h>
#include <Engine/Graphics/API/Sampler.h>
#include <vector>
#include <string>

namespace NuclearEngine {
	namespace Assets {
		enum TextureUsageType : Uint8
		{
			Diffuse = 1,
			Specular = 2,
			Normal = 3,

			Unknown = 255
		};

		class NEAPI Texture
		{
		public:
			Texture();
			~Texture();

			Math::Vector2ui GetDimensions();
			unsigned int GetWidth();
			unsigned int GetHeight();
			Uint32 GetHashedName();
			Uint8 GetUsageType();

			void SetHashedName(Uint32 name);
			void SetName(const std::string& str);
			void SetUsageType(Uint8 type);
			void SetUsageType(TextureUsageType type);

			inline void VSBind(Uint32 slot, Graphics::API::Sampler& sampler)
			{
				sampler.VSBind(slot);
				mTexture.VSBind(slot);
			}
			inline void PSBind(Uint32 slot, Graphics::API::Sampler& sampler)
			{
				sampler.PSBind(slot);
				mTexture.PSBind(slot);
			}
			inline void VSBind(Uint32 slot)
			{
				return mTexture.VSBind(slot);
			}
			inline void PSBind(Uint32 slot)
			{
				return mTexture.PSBind(slot);
			}

			Graphics::API::Texture mTexture;

		private:
			Math::Vector2ui mDimensions;
			Uint32 mHashedName;
			Uint8 mUsageType;
		};
	}
}