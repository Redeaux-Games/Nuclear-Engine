#pragma once
#include <Engine/Graphics/API/DirectX\DX11Common.h>
#ifdef NE_COMPILE_DIRECTX11
namespace NuclearEngine
{
	namespace Graphics
	{
		namespace API
		{
			class InputLayout;
			struct VertexBufferDesc;

			namespace DirectX
			{
				class DX11VertexShader;

				class NEAPI DX11VertexBuffer
				{
				public:
					DX11VertexBuffer();
					~DX11VertexBuffer();

					static void Create(DX11VertexBuffer* buffer, const VertexBufferDesc& desc);
					static void Delete(DX11VertexBuffer* buffer);

					void Update(const void* data, unsigned int size);

					void SetInputLayout(InputLayout * layout, DX11VertexShader *shader);

					void Bind();
					void* Map();
					void Unmap();

					ID3D11Buffer * mVBuffer;
					ID3D11InputLayout* mInputLayout;

					unsigned int mOffset, mStride;
				};
			}
		}
	}
}
#endif