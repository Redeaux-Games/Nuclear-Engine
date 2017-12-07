#pragma once
#include "Common.h"

class Demo5 : public Core::Game
{
protected:
	API::Shader *LampShader;
	API::VertexBuffer *LampVB;
	API::InputLayout *LampIL;

	Core::Renderer *Renderer;

	Components::Light dirlight;
	Components::Light flashlight;
	Components::Light pointlight1;
	Components::Light pointlight2;
	Components::Light pointlight3;
	Components::Light pointlight4;

	Components::Skybox* skybox;
	Components::Cube *cube;

	API::UniformBuffer *LightCubeUBO;

	API::Texture *CrateTexture_Diffuse;
	API::Texture *CrateTexture_Specular;

	Components::FlyCamera *Camera;

	// positions all containers
	Math::Vector3 cubePositions[10] = {
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
	Math::Vector3 pointLightPositions[4] = {
		Math::Vector3(0.7f,  0.2f,  2.0f),
		Math::Vector3(2.3f, -3.3f, -4.0f),
		Math::Vector3(-4.0f,  2.0f, -12.0f),
		Math::Vector3(0.0f,  0.0f, -3.0f)
	};

	float lastX = _Width_ / 2.0f;
	float lastY = _Height_ / 2.0f;
	bool firstMouse = true;

public:
	Demo5()
	{
	}
	void Load()
	{
		LampShader = new API::Shader("LampShader",
			&API::CompileShader(Core::FileSystem::LoadFileToString("Assets/Demo5/Shaders/DirectX/LampShader.vs").c_str(), ShaderType::Vertex, ShaderLanguage::HLSL),
			&API::CompileShader(Core::FileSystem::LoadFileToString("Assets/Demo5/Shaders/DirectX/LampShader.ps").c_str(), ShaderType::Pixel, ShaderLanguage::HLSL));
		
		Core::Renderer3D_Desc desc;
		desc.lightmodel = Core::LightShading::PhongShading;
		desc.tech = Core::RenderingTechnique::Forward;
		desc.effect = Core::LightEffects::None;
		
		float __vertices[] = {
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f, 
			0.5f, -0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f,  0.5f, 
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f, 
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f, 
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f, -0.5f
		};



		Camera = new Components::FlyCamera();
		Camera->Initialize(Math::Perspective(Math::ToRadians(60.0f), (float)800 / (float)600, 0.1f, 100.0f));

		LampShader->SetUniformBuffer(Camera->GetCBuffer(), 0, ShaderType::Vertex);

		Renderer = new Core::Renderer3D(desc);
		Renderer->AddLight(&dirlight);
		Renderer->AddLight(&flashlight);
		Renderer->AddLight(&pointlight1);
		Renderer->AddLight(&pointlight2);
		Renderer->AddLight(&pointlight3);
		Renderer->AddLight(&pointlight4);
		Renderer->SetCamera(Camera);
		Renderer->Bake();

		API::VertexBufferDesc vDesc;
		vDesc.data = __vertices;
		vDesc.size = sizeof(__vertices);
		vDesc.usage = BufferGPUUsage::Dynamic;
		vDesc.accessflag = BufferCPUAccess::Default;
		LampVB = new API::VertexBuffer(vDesc);

		LampIL = new API::InputLayout();
		LampIL->Push("POSITION", 0, DataType::Float3);
		LampVB->SetInputLayout(LampIL, LampShader);

		std::array<std::string, 6 > filenames = {
			"Assets/Common/Skybox/right.jpg",
			"Assets/Common/Skybox/left.jpg",
			"Assets/Common/Skybox/top.jpg",
			"Assets/Common/Skybox/bottom.jpg",
			"Assets/Common/Skybox/front.jpg" ,
			"Assets/Common/Skybox/back.jpg"
		};

		Texture_Desc _Desc;
		_Desc.Filter = TextureFilter::Linear2D;
		_Desc.Wrap = TextureWrap::ClampToEdge;
		_Desc.Format = TextureFormat::R8G8B8A8;

		//skybox = new Components::Skybox(Camera, ResourceManager::LoadTextureCubeFromFile(filenames, _Desc));

		Texture_Desc Desc;
		Desc.Filter = TextureFilter::Trilinear;
		Desc.Wrap = TextureWrap::Repeat;
		Desc.Format = TextureFormat::R8G8B8A8;

		CrateTexture_Diffuse = new API::Texture(ResourceManager::LoadTextureFromFile("Assets/Common/Textures/crate_diffuse.png", Desc), Desc);
		CrateTexture_Specular = new API::Texture(ResourceManager::LoadTextureFromFile("Assets/Common/Textures/crate_specular.png", Desc), Desc);

		Components::Material CubeMat;
		CubeMat.Diffuse = CrateTexture_Diffuse;
		CubeMat.Specular = CrateTexture_Specular;

		cube = new Components::Cube(Components::InputSignatures::Position_Normal_Texcoord, &CubeMat);

	
		Core::Context::EnableDepthBuffer(true);
		Core::Context::SetPrimitiveType(PrimitiveType::TriangleList);
	}

	void PreRender(float deltatime) override
	{     	
		if (Input::Keyboard::IsKeyPressed(Input::Keyboard::Key::W))
			Camera->ProcessMovement(Components::Camera_Movement::FORWARD, deltatime);
		if (Input::Keyboard::IsKeyPressed(Input::Keyboard::Key::A))
			Camera->ProcessMovement(Components::Camera_Movement::LEFT, deltatime);
		if (Input::Keyboard::IsKeyPressed(Input::Keyboard::Key::S))
			Camera->ProcessMovement(Components::Camera_Movement::BACKWARD, deltatime);
		if (Input::Keyboard::IsKeyPressed(Input::Keyboard::Key::D))
			Camera->ProcessMovement(Components::Camera_Movement::RIGHT, deltatime);

		Camera->Update();
	}

	void MouseMovementCallback(double xpos, double ypos) override
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		Camera->ProcessEye(xoffset, yoffset);
	}

	void Render()
	{
		Core::Context::Begin();

		//Change Background Color to Blue in RGBA format
		Core::Context::ClearColor(API::Color(0.1f, 0.1f, 0.1f, 1.0f));
		//Don't Forget to clear the depth buffer each frame
		Core::Context::ClearDepthBuffer();

		// directional light
		dirlight.SetDirection(Math::Vector3(-0.2f, -1.0f, -0.3f));
		dirlight.SetColor(API::Color(0.4f, 0.4f, 0.4f, 0.0f));

		// point light 1
		pointlight1.SetPosition(pointLightPositions[0]);
		pointlight1.SetColor(API::Color(1.0f, 1.0f, 1.0f, 0.0f));

		//point light 2
		pointlight2.SetPosition(pointLightPositions[1]);
		pointlight2.SetColor(API::Color(0.8f, 0.8f, 0.8f, 0.0f));

		// point light 3
		pointlight3.SetPosition(pointLightPositions[2]);
		pointlight3.SetColor(API::Color(0.8f, 0.8f, 0.8f, 0.0f));

		// point light 4
		pointlight4.SetPosition(pointLightPositions[3]);
		pointlight4.SetColor(API::Color(0.8f, 0.8f, 0.8f, 0.0f));

		// spotLight
		flashlight.SetPosition(Camera->GetPosition());
		flashlight.SetDirection(Camera->GetFrontView());
		flashlight.SetColor(API::Color(1.0f, 1.0f, 1.0f, 0.0f));

		Renderer->GetShader()->Bind();

		/* Render Textured Cube*/
		CrateTexture_Diffuse->PSBind("NE_Diffuse_Map", Renderer->GetShader(), 0);
		CrateTexture_Specular->PSBind("NE_Specular_Map", Renderer->GetShader(), 1);


		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			Math::Matrix4 model;
			model = Math::Translate(model, cubePositions[i]);
			//float angle = 20.0f * i;
			//model = Math::Rotate(model, Math::Vector3(1.0f, 0.3f, 0.5f), Math::ToRadians(angle));
			Camera->SetModelMatrix(model);

			cube->Draw(Renderer->GetShader());
		}

		Renderer->GetShader()->Unbind();

		/* Render Lamp Cube*/
		LampShader->Bind();

		Camera->SetModelMatrix(Math::Translate(Math::Vector3(1.2f, 1.0f, 2.0f)) * Math::Scale(Math::Vector3(0.2f)));

		LampVB->Bind();

		for (unsigned int i = 0; i < 4; i++)
		{
			Math::Matrix4 model;
			model = Math::Translate(model, pointLightPositions[i]);
			model = Math::Scale(model, Math::Vector3(0.2f));
			Camera->SetModelMatrix(model);
			Core::Context::Draw(36);
		}

		LampVB->Unbind();
		LampShader->Unbind();

		Renderer->Render();

		//skybox->Render();

		Core::Context::End();
	}
	void ExitRendering()	// Exit Rendering
	{
		delete CrateTexture_Diffuse;
		delete CrateTexture_Specular;
	}
};