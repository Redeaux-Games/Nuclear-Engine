#include "API\Texture.h"
#include "API\Shader.h"
#include <Core\Context.h>
#include <NuclearRendererBase\NRBTexture.h>


namespace NuclearEngine {
	namespace API {
		Texture::Texture()
		{
		}
		Texture::Texture(const Texture_Data& TexData, const Texture_Desc& Desc)
		{
			tex = Core::Context::ConstructTexture(tex);
			
			tex->Create(TexData, Desc);
		}
		Texture::Texture(const std::array<NuclearEngine::Texture_Data, 6>& data, NuclearEngine::Texture_Desc Desc)
		{
			tex = Core::Context::ConstructTexture(tex);

			tex->Create(data, Desc);
		}
		Texture::~Texture()
		{
			if (tex != nullptr)
			{
				tex->Delete();
				delete tex;
				tex = nullptr;
			}
		}	
		void Texture::VSBind(unsigned int index)
		{
			tex->VSBind(index);
		}
		void Texture::VSBind(const char * samplerName, API::Shader* shader, unsigned int index)
		{
			tex->VSBind(samplerName, shader->GetBase(), index);
		}
		void Texture::PSBind(unsigned int index)
		{
			tex->PSBind(index);
		}
		void Texture::PSBind(const char * samplerName, API::Shader* shader, unsigned int index)
		{
			tex->PSBind(samplerName, shader->GetBase(), index);
		}	
		void Texture::GSBind(unsigned int index)
		{
			tex->GSBind(index);
		}
		void Texture::GSBind(const char * samplerName, API::Shader* shader, unsigned int index)
		{
			tex->GSBind(samplerName, shader->GetBase(), index);
		}

		NuclearRenderer::NRBTexture * Texture::GetBase()
		{
			return tex;
		}
	}
}