#pragma once
#include <Base\NE_Common.h>
#include <Engine\Assets\MaterialInstance.h>
#include <unordered_map>

namespace NuclearEngine
{
	namespace Assets
	{
		class NEAPI Material
		{
		public:
			Material();
			~Material();

			void CreateInstance(Graphics::RenderingPipeline* Pipeline);

			Assets::MaterialInstance* GetMaterialInstance(Uint32 PipelineID);

			std::vector<TextureSet> mPixelShaderTextures;

		private:
			std::unordered_map<Uint32, Assets::MaterialInstance> mMaterialInstances;
		};
	}
}