#pragma once
#include "Common.h"

class Playground : public Core::Game
{
protected:
	std::shared_ptr<Systems::RenderSystem> Renderer;

	//XAsset
	API::Texture DiffuseTex;
	API::Texture SpecularTex;
	API::Texture NormalTex;

	XAsset::ModelAsset CubeAsset;

	//Default states
	API::CommonStates states;

	Components::FlyCamera Camera;

	Components::PointLight pointlight1;

	//ECS
	Core::Scene SampleScene;

	Components::Model CubeModel;

	// positions of the point lights
	Math::Vector3 pointLightPositions[4] =
	{
		Math::Vector3(0.7f,  0.2f,  2.0f)
	};
	float lastX = _Width_ / 2.0f;
	float lastY = _Height_ / 2.0f;
	bool firstMouse = true;
public:
	Playground()
	{
	}

	void SetupLights()
	{
		pointlight1.SetPosition(pointLightPositions[0]);
		pointlight1.SetColor(API::Color(1.0f, 1.0f, 1.0f, 0.0f));
	}
	void SetupTextures()
	{
		API::Texture_Desc Desc;
		Desc.Format = API::Format::R8G8B8A8_UNORM;
		Desc.Type = API::TextureType::Texture2D;
		Managers::AssetManager::CreateTextureFromFile("Assets/Common/Textures/brickwall.jpg", &DiffuseTex, Desc);
		Managers::AssetManager::CreateTextureFromFile("Assets/Common/Textures/brickwall_normal.jpg", &NormalTex, Desc);
		Managers::AssetManager::CreateTextureFromFile("Assets/Common/Textures/black.png", &SpecularTex, Desc);

	}
	void SetupXAsset()
	{
		SetupTextures();

		std::vector<XAsset::MeshTexture> textures;

		XAsset::MeshTexture DTexture;
		DTexture.Texture = DiffuseTex;
		DTexture.type = XAsset::MeshTextureType::Diffuse;
		textures.push_back(DTexture);
		DTexture.Texture = SpecularTex;
		DTexture.type = XAsset::MeshTextureType::Specular;
		textures.push_back(DTexture);
		DTexture.Texture = NormalTex;
		DTexture.type = XAsset::MeshTextureType::Normal;
		textures.push_back(DTexture);

		XAsset::ModelAssetVertexDesc descm;
		descm.Tangents = true;
		XAsset::ModelAsset::CreateCube(&CubeAsset, textures, descm);
		CubeAsset.Initialize(&Renderer->GetVertexShader());
		CubeModel.SetAsset(&CubeAsset);
	}

	void Load()
	{
		Systems::RenderSystemDesc desc;
		desc.Normals = true;
		Renderer = SampleScene.Systems.Add<Systems::RenderSystem>(desc);
		SampleScene.Systems.Configure();

		Camera.Initialize(Math::Perspective(Math::ToRadians(45.0f), Core::Application::GetAspectRatiof(), 0.1f, 100.0f));

		Renderer->SetCamera(&Camera);
		Renderer->AddLight(&pointlight1);
		Renderer->Bake();

		SetupLights();

		SetupXAsset();

		states.EnabledDepth_DisabledStencil.Bind();
		Core::Context::SetPrimitiveType(PrimitiveType::TriangleList);

		Core::Application::SetMouseInputMode(Core::MouseInputMode::Virtual);
		Core::Application::Display();
	}

	void OnMouseMovement(double xpos_a, double ypos_a) override
	{
		float xpos = static_cast<float>(xpos_a);
		float ypos = static_cast<float>(ypos_a);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		Camera.ProcessEye(xoffset, yoffset);
	}

	void Update(float deltatime) override
	{
		if (Platform::Input::Keyboard::IsKeyPressed(Platform::Input::Keyboard::Key::W))
			Camera.ProcessMovement(Components::Camera_Movement::FORWARD, deltatime);
		if (Platform::Input::Keyboard::IsKeyPressed(Platform::Input::Keyboard::Key::A))
			Camera.ProcessMovement(Components::Camera_Movement::LEFT, deltatime);
		if (Platform::Input::Keyboard::IsKeyPressed(Platform::Input::Keyboard::Key::S))
			Camera.ProcessMovement(Components::Camera_Movement::BACKWARD, deltatime);
		if (Platform::Input::Keyboard::IsKeyPressed(Platform::Input::Keyboard::Key::D))
			Camera.ProcessMovement(Components::Camera_Movement::RIGHT, deltatime);

		Camera.Update();
	}

	void Render(float dt) override
	{
		Core::Context::Begin();

		Core::Context::Clear(API::Color(0.1f, 0.1f, 0.1f, 1.0f), ClearColorBuffer | ClearDepthBuffer);
		Renderer->GetVertexShader().Bind();
		Renderer->GetPixelShader().Bind();

		states.DefaultSampler.PSBind(0);
		states.DefaultSampler.PSBind(1);
		states.DefaultSampler.PSBind(2);

		Renderer->InstantRender(&CubeModel);
		
		pointlight1.SetPosition(Camera.GetPosition());

		Renderer->Update_Light();

		SampleScene.Systems.Update_All(dt);

		states.EnabledDepth_DisabledStencil.Bind();

		Core::Context::End();
	}
};