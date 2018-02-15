#include <API\VertexShader.h>
#ifdef NE_USE_RUNTIME_RENDER_API
#include <Core\Context.h>
#include <API\ConstantBuffer.h>
namespace NuclearEngine {
	namespace API {

		VertexShader::VertexShader()
		{

		}

		VertexShader::~VertexShader()
		{

		}

		void VertexShader::Create(VertexShader* result, BinaryShaderBlob* Desc)
		{
			if (Core::Context::GetRenderAPI() == Core::RenderAPI::OpenGL3)
			{
				OpenGL::GLVertexShader::Create(&result->GLObject, Desc);
			}
			else if (Core::Context::GetRenderAPI() == Core::RenderAPI::DirectX11)
			{
				DirectX::DX11VertexShader::Create(&result->DXObject, Desc);
			}
		}

		void VertexShader::Delete(VertexShader * result)
		{
			if (Core::Context::GetRenderAPI() == Core::RenderAPI::OpenGL3)
			{
				OpenGL::GLVertexShader::Delete(&result->GLObject);
			}
			else if (Core::Context::GetRenderAPI() == Core::RenderAPI::DirectX11)
			{
				DirectX::DX11VertexShader::Delete(&result->DXObject);
			}
		}

		void VertexShader::SetConstantBuffer(ConstantBuffer * cbuffer)
		{
			if (Core::Context::GetRenderAPI() == Core::RenderAPI::OpenGL3)
			{
				GLObject.SetConstantBuffer(&cbuffer->GLObject);
			}
			else if (Core::Context::GetRenderAPI() == Core::RenderAPI::DirectX11)
			{
				DXObject.SetConstantBuffer(&cbuffer->DXObject);
			}
		}

		void VertexShader::Bind()
		{
			if (Core::Context::GetRenderAPI() == Core::RenderAPI::OpenGL3)
			{
				GLObject.Bind();
			}
			else if (Core::Context::GetRenderAPI() == Core::RenderAPI::DirectX11)
			{
				DXObject.Bind();
			}
		}
	}
}
#endif