#pragma once
#include <string>

namespace NuclearEngine {

	enum class DataType { Float, Float2, Float3, Float4 };

	enum class Comparison_Func {
		NEVER,
		LESS,
		EQUAL,
		LESS_EQUAL,
		GREATER,
		NOT_EQUAL,
		GREATER_EQUAL,
		ALWAYS
	};
	enum class Stencil_OP
	{
		KEEP,
		ZERO,
		REPLACE,
		INCREASE_SAT,
		DECREASE_SAT,
		INVERT,
		INCREASE,
		DECREASE
	};

	struct Stencil_Face_Desc {
		Stencil_OP StencilFailOp = Stencil_OP::KEEP;
		Stencil_OP StencilDepthFailOp = Stencil_OP::KEEP;
		Stencil_OP StencilPassOp = Stencil_OP::KEEP;
		Comparison_Func StencilFunc = Comparison_Func::NOT_EQUAL;
	};

	struct DepthStencilStateDesc {
		bool DepthStencilEnabled = false;
		bool DepthMaskEnabled = false;
		Comparison_Func DepthFunc = Comparison_Func::LESS;

		unsigned char StencilReadMask = 0xFF;
		unsigned char StencilWriteMask = 0xFF;

		Stencil_Face_Desc StencilFrontFace;
		Stencil_Face_Desc StencilBackFace;
	};


	enum class NEAPI ClearFlags
	{
		None,
		Depth,
		Stencil,
		Depth_Stencil
	};

	enum class BufferGPUUsage {
		Default,
		Static,
		Dynamic
	};

	enum class BufferCPUAccess {
		Default,
		ReadOnly,
		WriteOnly
	};
	struct VertexBufferDesc {
		const void* data;
		unsigned int size;
		BufferGPUUsage usage = BufferGPUUsage::Default;
		BufferCPUAccess access = BufferCPUAccess::Default;
	};


}