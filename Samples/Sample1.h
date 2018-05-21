#pragma once
#include "Common.h"

class Sample1 : public Core::Game
{
protected:
	std::shared_ptr<Systems::RenderSystem> Renderer;

	bool renderboxes = true;
	bool renderspheres = true;
	bool rendernanosuit = true;

	//Assets
	Assets::Texture DiffuseTex;
	Assets::Texture SpecularTex;
	Assets::Texture WhiteTex;

	Assets::Mesh CubeAsset;
	Assets::Mesh SphereAsset;
	Assets::Mesh NanosuitAsset;

	//Default states
	Graphics::API::CommonStates states;

	Components::CameraComponent Camera;

	Components::DirectionalLight dirlight;
	Components::PointLight pointlight1;
	Components::PointLight pointlight2;
	Components::PointLight pointlight3;
	Components::PointLight pointlight4;
	Components::PointLight pointlight5;
	Components::PointLight pointlight6;
	Components::PointLight pointlight7;
	Components::PointLight pointlight8;
	Components::PointLight pointlight9;

	Components::SpotLight spotLight;

	Graphics::Skybox Skybox;

	//ECS
	ECS::Scene SampleScene;
	ECS::Entity ESkybox;
	ECS::Entity ECube;
	ECS::Entity ELamp;
	ECS::Entity ENanosuit;

	Components::MeshComponent CubeModel;
	Components::MeshComponent LampModel;
	Components::MeshComponent NanosuitModel;

	// positions all containers
	Math::Vector3 cubePositions[10] = 
	{
		Math::Vector3(0.0f,  0.0f,  0.0f),
		Math::Vector3(2.0f,  5.0f, -15.0f),
		Math::Vector3(-1.5f, -2.2f, -2.5f),
		Math::Vector3(-3.8f, -2.0f, -12.3f),
		Math::Vector3(2.4f, -0.4f, -3.5f),
		Math::Vector3(-1.7f,  3.0f, -7.5f),
		Math::Vector3(1.3f, -2.0f, -2.5f),
		Math::Vector3(1.5f,  2.0f, -2.5f),
		Math::Vector3(1.5f,  0.2f, -1.5f),
		Math::Vector3(-1.3f,  1.0f, -1.5f)
	};

	// positions of the point lights
	Math::Vector3 pointLightPositions[9] =
	{
		Math::Vector3(0.7f,  0.2f,  2.0f),
		Math::Vector3(2.3f, -3.3f, -4.0f),
		Math::Vector3(-4.0f,  2.0f, -12.0f),
		Math::Vector3(0.0f,  0.0f, -3.0f),
		Math::Vector3(4.0f,  3.0f, -2.0f),
		Math::Vector3(6.2f, 2.0f, 0.0f),
		Math::Vector3(6.2f, -2.0f, 0.0f),
		Math::Vector3(-6.2f, 2.0f, 0.0f),
		Math::Vector3(-6.2f, -2.0f, 0.0f)
	};
	float lastX = _Width_ / 2.0f;
	float lastY = _Height_ / 2.0f;
	bool firstMouse = true;
public:
	Sample1()
	{
	}

	void SetupLights()
	{
		dirlight.SetDirection(Math::Vector3(-0.2f, -1.0f, -0.3f));
		dirlight.SetColor(Graphics::Color(0.4f, 0.4f, 0.4f, 0.0f));

		pointlight1.SetPosition(pointLightPositions[0]);
		pointlight1.SetColor(Graphics::Color(1.0f, 1.0f, 1.0f, 0.0f));

		pointlight2.SetPosition(pointLightPositions[1]);
		pointlight2.SetColor(Graphics::Color(0.8f, 0.8f, 0.8f, 0.0f));

		pointlight3.SetPosition(pointLightPositions[2]);
		pointlight3.SetColor(Graphics::Color(0.8f, 0.8f, 0.8f, 0.0f));

		pointlight4.SetPosition(pointLightPositions[3]);
		pointlight4.SetColor(Graphics::Color(0.8f, 0.8f, 0.8f, 0.0f));

		pointlight5.SetPosition(pointLightPositions[4]);
		pointlight5.SetColor(Graphics::Color(0.8f, 0.8f, 0.8f, 0.0f));

		pointlight6.SetPosition(pointLightPositions[5]);
		pointlight6.SetColor(Graphics::Color(0.8f, 0.8f, 0.8f, 0.0f));

		pointlight7.SetPosition(pointLightPositions[6]);
		pointlight7.SetColor(Graphics::Color(0.8f, 0.8f, 0.8f, 0.0f));

		pointlight8.SetPosition(pointLightPositions[7]);
		pointlight8.SetColor(Graphics::Color(0.8f, 0.8f, 0.8f, 0.0f));

		pointlight9.SetPosition(pointLightPositions[8]);
		pointlight9.SetColor(Graphics::Color(0.8f, 0.8f, 0.8f, 0.0f));
	}
	void SetupTextures()
	{
		DiffuseTex = Managers::AssetManager::Import("Assets/Common/Textures/crate_diffuse.png", Assets::TextureUsageType::Diffuse);
		SpecularTex = Managers::AssetManager::Import("Assets/Common/Textures/crate_specular.png", Assets::TextureUsageType::Specular);
		WhiteTex = Managers::AssetManager::Import("Assets/Common/Textures/white.png");
	}
	void SetupAssets()
	{
		SetupTextures();

		std::vector<Assets::Texture> Textures;
		Textures.push_back(DiffuseTex);
		Textures.push_back(SpecularTex);

		Assets::Mesh::CreateCube(&CubeAsset, Textures);
		CubeAsset.Initialize(&Renderer->GetVertexShader());

		Textures.clear();

		std::vector<Assets::Texture> SphereTextures;
		WhiteTex.SetUsageType(Assets::TextureUsageType::Diffuse);
		SphereTextures.push_back(WhiteTex);
		WhiteTex.SetUsageType(Assets::TextureUsageType::Specular);
		SphereTextures.push_back(WhiteTex);

		Assets::Mesh::CreateSphere(&SphereAsset, SphereTextures);
		SphereAsset.Initialize(&Renderer->GetVertexShader());

		Managers::MeshLoadingDesc ModelDesc;
		ModelDesc.LoadDiffuseTextures = true;
		ModelDesc.LoadSpecularTextures = true;
		NanosuitAsset = Managers::AssetManager::Import("Assets/Common/Models/CrytekNanosuit/nanosuit.obj", ModelDesc);
		NanosuitAsset.Initialize(&Renderer->GetVertexShader());

		//Create The skybox
		std::array<std::string, 6> SkyBoxTexturePaths
		{
			std::string("Assets/Common/Skybox/right.jpg"),
			std::string("Assets/Common/Skybox/left.jpg"),
			std::string("Assets/Common/Skybox/top.jpg"),
			std::string("Assets/Common/Skybox/bottom.jpg"),
			std::string("Assets/Common/Skybox/front.jpg"),
			std::string("Assets/Common/Skybox/back.jpg")
		};

		Skybox.Initialize(&Camera, SkyBoxTexturePaths);
	}
	void SetupEntities()
	{
		CubeModel.mMesh = &CubeAsset;
		//ECube = SampleScene.Entities.Create();
		//ECube.Assign<Components::MeshComponent>(CubeModel);
		LampModel.mMesh = &SphereAsset;
		//ELamp = SampleScene.Entities.Create();
		//ELamp.Assign<Components::MeshComponent>(LampModel);
		NanosuitModel.mMesh = &NanosuitAsset;
		//ENanosuit = SampleScene.Entities.Create();
		//ENanosuit.Assign<Components::MeshComponent>(NanosuitModel);

	}
	void Load()
	{
		Systems::RenderSystemDesc desc;
		Renderer = SampleScene.Systems.Add<Systems::RenderSystem>(desc);
		SampleScene.Systems.Configure();

		Camera.Initialize(Math::Perspective(Math::radians(45.0f), Core::Application::GetAspectRatiof(), 0.1f, 100.0f));

		Renderer->SetCamera(&Camera);
		Renderer->AddLight(&spotLight);
		Renderer->AddLight(&pointlight1);
		Renderer->AddLight(&pointlight2);
		Renderer->AddLight(&pointlight3);
		Renderer->AddLight(&pointlight4);
		Renderer->AddLight(&pointlight5);
		Renderer->AddLight(&pointlight6);
		Renderer->AddLight(&pointlight7);
		Renderer->AddLight(&pointlight8);
		Renderer->AddLight(&pointlight9);
		Renderer->AddLight(&dirlight);
		Renderer->Bake();


		Assets::Material mat;
		mat.SetPixelShader(Renderer->GetPixelShader());

		Managers::AssetManager::mSaveTextureNames = true;

		SetupLights();

		SetupAssets();
	
		SetupEntities();

		for (auto x : Managers::AssetManager::mHashedTexturesNames)
		{
			Log.Info("HASH: " + std::to_string(x.first) + " PATH: " + x.second + "\n");
		}
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 16.0f);

		SampleScene.Entities;

		ImGui::StyleColorsDark();

		states.EnabledDepth_DisabledStencil.Bind();
		Graphics::API::Context::SetPrimitiveType(Graphics::PrimitiveType::TriangleList);

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
		//Core::Application::SetTitle("Nuclear Engine FPS: " + std::to_string(FPS) + " FrameTime: " + std::to_string(FrameTime));

		if (Core::Input::Keyboard::IsKeyPressed(Core::Input::Keyboard::Key::W))
			Camera.ProcessMovement(Components::Camera_Movement::FORWARD, deltatime);
		if (Core::Input::Keyboard::IsKeyPressed(Core::Input::Keyboard::Key::A))
			Camera.ProcessMovement(Components::Camera_Movement::LEFT, deltatime);
		if (Core::Input::Keyboard::IsKeyPressed(Core::Input::Keyboard::Key::S))
			Camera.ProcessMovement(Components::Camera_Movement::BACKWARD, deltatime);
		if (Core::Input::Keyboard::IsKeyPressed(Core::Input::Keyboard::Key::D))
			Camera.ProcessMovement(Components::Camera_Movement::RIGHT, deltatime);

		Camera.Update();
	}
	void ShowOverlay(bool show)
	{
		const float DISTANCE = 10.0f;
		static int corner = 0;
		ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.3f)); // Transparent background
		if (ImGui::Begin("FPS Overlay", &show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::Text("FPS Overlay\n");
			ImGui::Separator();
			ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();

		}
		ImGui::PopStyleColor();
	}
	void Render(float dt) override
	{

		ImGui::NE_NewFrame();

		Graphics::API::Context::Clear(Graphics::Color(0.1f, 0.1f, 0.1f, 1.0f), ClearColorBuffer | ClearDepthBuffer);
		Renderer->GetVertexShader().Bind();
		Renderer->GetPixelShader().Bind();

		states.DefaultSampler.PSBind(0);
		states.DefaultSampler.PSBind(1);

		if (renderboxes)
		{
			for (unsigned int i = 0; i < 10; i++)
			{
				// calculate the model matrix for each object and pass it to shader before drawing
				Math::Matrix4 model(1.0f);
				model = Math::Translate(model, cubePositions[i]);
				float angle = 20.0f * i * ClockTime;

				model = Math::Rotate(model, Math::radians(angle), Math::Vector3(1.0f, 0.3f, 0.5f));
				Camera.SetModelMatrix(model);

				Renderer->InstantRender(&CubeModel);
			}
		}
		if (renderspheres)
		{
			for (unsigned int i = 0; i < 9; i++)
			{
				Math::Matrix4 model(1.0f);
				model = Math::Translate(model, pointLightPositions[i]);
				model = Math::Scale(model, Math::Vector3(0.25f));
				Camera.SetModelMatrix(model);
				Renderer->InstantRender(&LampModel);
			}
		}
		if (rendernanosuit)
		{
			Math::Matrix4 NanosuitMatrix(1.0f);
			NanosuitMatrix = Math::Translate(NanosuitMatrix, Math::Vector3(5.0f, -1.75f, 0.0f));
			NanosuitMatrix = Math::Scale(NanosuitMatrix, Math::Vector3(0.25f));
			NanosuitMatrix = Math::Rotate(NanosuitMatrix, ClockTime, Math::Vector3(0.0f, 1.0f, 0.0f));
			Camera.SetModelMatrix(NanosuitMatrix);
			Renderer->InstantRender(&NanosuitModel);
		}
		spotLight.SetPosition(Camera.GetPosition());
		spotLight.SetDirection(Camera.GetFrontView());

		Renderer->Update_Light();

		SampleScene.Systems.Update_All(dt);


		Skybox.Render();
		states.EnabledDepth_DisabledStencil.Bind();

		ImGui::Checkbox("Render Boxes", &renderboxes);
		ImGui::Checkbox("Render Lamps Spheres", &renderspheres);
		ImGui::Checkbox("Render Nanosuit", &rendernanosuit);
				
		ShowOverlay(true);
		
		ImGui::Render();
		Graphics::API::Context::PresentFrame();
	}
};