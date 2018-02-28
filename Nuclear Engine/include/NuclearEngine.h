#pragma once
/*
          _ ._  _ , _ ._
        (_ ' ( `  )_  .__)
      ( (  (    )   `)  ) _)
     (__ (_   (_ . _) _) ,__)
         `~~`\ ' . /`~~`
              ;   ;
              /   \
_____________/BOOOM\_____________
*/
//Note: The Supported Renderers will expand when I get new hardware, currently planned in the future ( DirectX 12 , Vulkan )

//# Core Engine Headers
#include <Core/Engine.h>
#include <Core/Context.h>
#include <Core/Game.h>
#include <Core/FileSystem.h>
//--Entity Component System Headers
#include <Core/Scene.h>
#include <Core/Event.h>
#include <Core/Entity.h>
#include <Core/System.h>

//# Platform Abstraction Layer Headers
#include <Platform\Clock.h>
#include <Platform\Timer.h>
#include <Platform\Input.h>

//# XAsset & their managers Headers
#include <Managers\AssetManager.h>
#include <Managers\ShaderManager.h>

//# Asset Classes (XXAsset)
#include <XAsset\ModelAsset.h>

//# Shading Headers
#include <Shading/Material.h>


//# OneAPI Headers Begin
//---Buffers
#include <API/ConstantBuffer.h>
#include <API/VertexBuffer.h>
#include <API/IndexBuffer.h>
#include <API/InputLayout.h>
//---Textures
#include <API/Texture.h>
#include <API/Sampler.h>
#include <API/Texture_Types.h>
#include <API/RenderTarget.h>
//---RenderStates
#include <API/BlendState.h>
#include <API/RasterizerState.h>
#include <API/DepthStencilState.h>
#include <API/RenderStates_Types.h>
//---Shaders
#include <API/ShaderCompiler.h>
#include <API/VertexShader.h>
#include <API/PixelShader.h>
//---Other
#include <API/Color.h>
#include <API/Format.h>
#include <API/CommonStates.h>
//# OneAPI Headers End


//# Engine Components Headers (Can be used as Components or Entities!)
#include <Components\GenericCamera.h>
#include <Components\FlyCamera.h>
#include <Components\Skybox.h>
#include <Components\Light.h>
#include <Components\Model.h>
#include <Components\GUI\imgui.h>

//# Engine Systems Headers
#include <Systems\RenderSystem.h>