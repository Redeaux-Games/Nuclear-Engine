#pragma once
#include <NE_Common.h>
#include <string>
#include <API\Shader_Types.h>
namespace NuclearEngine 
{	
	namespace API 
	{
		
		NEAPI bool CompileShader(BinaryShaderBlob* result, std::string SourceCode, API::ShaderType type, API::ShaderLanguage language = API::ShaderLanguage::HLSL);

		NEAPI BinaryShaderBlob CompileShader(std::string SourceCode, API::ShaderType type, API::ShaderLanguage language = API::ShaderLanguage::HLSL);
	}
}