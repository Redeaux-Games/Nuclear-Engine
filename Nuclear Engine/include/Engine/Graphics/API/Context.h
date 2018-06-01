#pragma once
#include <Base\NE_Common.h>
#include <Engine/Graphics/Color.h>
#include <Core\ApplicationDesc.h>

#define	ClearColorBuffer 0b00000001
#define	ClearDepthBuffer 0b00000010
#define	ClearStencilBuffer 0b00000100

namespace NuclearEngine
{
	namespace Graphics
	{

		enum PrimitiveType
		{
			PointList = 0,
			LineList = 1,
			LineStrip = 2,
			TriangleList = 3,
			TriangeStrip = 4
		};

		namespace API {
			namespace ContextDesc
			{
				//IF 0 then Ansiotrpopic isnot supported
				static float MaxAnisotropicLevel = 0.0f;
			}

			class NEAPI Context
			{
			public:
				static Core::RenderAPI GetRenderAPI();

				static void SetPrimitiveType(PrimitiveType primitivetype);

				static void Clear(Graphics::Color color, Uint32 flags, float depth = 1.0f, unsigned int stencil = 0);

				//Render the frame to the window
				static void PresentFrame();

				static void Draw(unsigned int count);
				static void DrawIndexed(unsigned int vertexCount);

				static void SetViewPort(int x, int y, int width, int height);

				static bool isOpenGL3RenderAPI();
				static bool isDirectX11RenderAPI();

				static void SetRenderAPI(const Core::RenderAPI & renderer);
			};
		}
	}
}