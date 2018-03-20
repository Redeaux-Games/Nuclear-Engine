#pragma once

namespace NuclearEngine
{
	namespace Graphics
	{
		namespace API
		{
			enum class Format
			{
				R8_UNORM,
				R8G8_UNORM,
				R8G8B8_UNORM,
				R8G8B8A8_UNORM,
				//Gamma Corrected Texture
				R8G8B8A8_UNORM_SRGB,

				R16_FLOAT,
				R16G16_FLOAT,
				R16G16B16_FLOAT,
				R16G16B16A16_FLOAT,

				R32_FLOAT,
				R32G32_FLOAT,
				R32G32B32_FLOAT,
				R32G32B32A32_FLOAT
			};
		}
	}
}