#pragma once

#include <Engine\Components\Renderable2D.h>
#include <Engine\Graphics\SpriteSheet.h>
#include <Engine\Graphics\Animator2D.h>
#include <Engine/Graphics/API/Texture.h>
#include <Base\Math\Math.h>

namespace NuclearEngine
{
	namespace Components
	{	
		class Sprite : public Renderable2D {
		public:
			Graphics::Animator2D Animations;

			Sprite(int x, int y, Graphics::API::Texture *texture, const std::vector<Uint32> &frames);
			Sprite(int x, int y, Graphics::API::Texture *texture, Uint32 frame = 0);
			Sprite(int x, int y, int w, int h, Graphics::API::Texture *texture,
				Uint32 frame = 0);
			~Sprite();

			void Update();

			// Getters
			inline unsigned int GetColor() const { return Color; }
			inline Uint32 GetCurrentFrame() const { return Frame; }
			inline Graphics::SpriteSheet GetSpriteSheet() const { return *Sprites; }
			inline Math::Vector2 GetFrameCoords() const { return Sprites->GetUV(this->Frame); }

			// Setters
			void SetFrame(Uint32 frame);
			void SetDirectFrame(Uint32 frame);
			void SetColorRGB(int r, int g, int b);
			void SetColorRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
			void SetAlpha(int a);
			void Flip() { this->SetScale(Math::Vector2(-1.f, 0.f)); }

		private:
			//glm::vec4 Color;
			unsigned int Color;
			std::vector<Uint32> Frames;
			Uint32 Frame = 0, NumberOfFrames;
			Graphics::SpriteSheet *Sprites;
		};
	}
}