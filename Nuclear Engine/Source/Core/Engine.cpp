#include <Core\Engine.h>
#include <Base\NE_Common.h>
#include <Base\Utilities\Timer.h>
#include <Core\Application.h>
#include <Engine\Audio\AudioEngine.h>
#include <Engine\Graphics\Context.h>
#include <Engine\Assets\DefaultMeshes.h>

#include "..\Engine\Graphics\ImGUI\imgui_impl_glfw.h"
#include "..\Engine\Graphics\ImGUI\imgui_impl.h"

//Dependencies Linking
#pragma comment(lib,"assimp-vc142-mt.lib")
#pragma comment(lib,"glfw3.lib")

//Diligent Linking
#pragma comment(lib,"Diligent-Common.lib")

#ifdef _DEBUG
#pragma comment(lib,"GraphicsEngineD3D11_64d.lib")
#pragma comment(lib,"GraphicsEngineD3D12_64d.lib")
#pragma comment(lib,"GraphicsEngineOpenGL_64d.lib")
#pragma comment(lib,"GraphicsEngineVK_64d.lib")
#else
#pragma comment(lib,"GraphicsEngineD3D11_64r.lib")
#pragma comment(lib,"GraphicsEngineD3D12_64r.lib")
#pragma comment(lib,"GraphicsEngineOpenGL_64r.lib")
#pragma comment(lib,"GraphicsEngineVK_64r.lib")
#endif

#pragma comment(lib,"Diligent-GraphicsAccessories.lib")
#pragma comment(lib,"Diligent-GraphicsTools.lib")
#pragma comment(lib,"Diligent-BasicPlatform.lib")
#pragma comment(lib,"Diligent-Win32Platform.lib")


namespace REDxEngine {
	namespace Core {

		static std::string MajorVersion = "0";
		static std::string MinorVersion = "001";

		// timing
		static float deltaTime = 0.0f;	// time between current frame and last frame
		static float lastFrame = 0.0f;

		static Game * GamePtr;
		static Game Defaultgame;

		static Engine::State Engine_State;
		static bool g_isDebug = DEBUG_TRUE_BOOL;

		void PrintIntroLog();

		bool Engine::Start(const EngineStartupDesc& desc)
		{
			PrintIntroLog();

			//Create platform specific app (window)
			Application::Start(desc.mAppdesc);
			Application::GetMainWindow()->GetInput()->SetMouseInputMode(Core::Input::MouseInputMode::Normal);
			
			if (!Graphics::GraphicsEngine::Initialize(desc.mGraphicsEngineDesc))
			{
				Log.FatalError("[Engine] GraphicsEngine Failed to initalize...\n");
				return false;
			}
			//Initialize Context
			Graphics::Context::Initialize(desc.mAppdesc, desc.mGraphicsEngineDesc);
			Assets::DefaultMeshes::Initialize();


			Graphics::ImGui::CreateContext();
			ImGui_ImplGlfw_Init(Core::Application::GetMainWindow()->GetRawWindowPtr(), true);
			ImGui_Impl_Init();
			ImGui_Impl_CreateDeviceObjects();
			Log.Info("[Engine] ImGUI Initalized.\n");


			if(desc.AutoInitAudioEngine)
				Audio::AudioEngine::Initialize();

			if (desc.AutoInitPhysXEngine)
			{
				if (!PhysX::PhysXEngine::Initialize(desc.mPhysXEngineDesc))
				{
					Log.FatalError("[Engine] PhysXEngine Failed to auto Initialize!\n");
					return false;
				}
			}
			g_isDebug = desc.Debug;

			GamePtr = &Defaultgame;

			Log.Info("[Engine] REDx Game Engine has been initalized successfully!\n");
			return true;
		}

		void Engine::Shutdown()
		{
			Log.Info("[Engine] Shutting Down Engine.\n");

			GamePtr = &Defaultgame;
			Core::Application::Shutdown();
			Audio::AudioEngine::Shutdown();
			Graphics::GraphicsEngine::Shutdown();

			//Graphics::ImGui_Renderer::Shutdown();

			Log.Info("------------------------ -Engine Has Shutdown- -----------------------\n");
			Log.Info("-------------------------- -Nuclear Engine- --------------------------\n");
		}

		void Engine::BeginFrame()
		{	
			ImGui_Impl_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			Graphics::ImGui::NewFrame();
		}

		void Engine::EndFrame()
		{
			Graphics::ImGui::Render();
			ImGui_Impl_RenderDrawData(Graphics::ImGui::GetDrawData());
			Graphics::Context::GetSwapChain()->Present();
		}

		void Engine::RunGame(Game * _YourGame)
		{
			GamePtr = _YourGame;
			if (GamePtr != nullptr)
			{
				Log.Info("[Engine] Running Game.\n");

				if (GamePtr->GetGameInfo() != nullptr)
				{
					Log.Info(std::string("[Engine] Game Name: " + std::string(GamePtr->GetGameInfo()->Name) + "\n"));
					Log.Info(std::string("[Engine] Game Version: " + std::string(GamePtr->GetGameInfo()->Version) + "\n"));
					Log.Info(std::string("[Engine] Game Developer: " + std::string(GamePtr->GetGameInfo()->Developer) + "\n"));
				}

				SetState(Engine::State::Initializing);
				GamePtr->Initialize();
				SetState(Engine::State::Loading);
				GamePtr->Load();
				Engine::Game_Loop_Render();
				if (GamePtr != nullptr)
				{
					SetState(Engine::State::ExitingRendering);
					GamePtr->ExitRendering();
					SetState(Engine::State::Shuttingdown);
					GamePtr->Shutdown();
				}
				GamePtr = nullptr;
			}
		}
		
		bool Engine::ShouldClose()
		{
			return Core::Application::GetMainWindow()->ShouldClose();
		}

		bool Engine::isDebug()
		{
			return g_isDebug;
		}

		Game * Engine::GetGame()
		{
			return GamePtr;
		}
	
		void Engine::Game_Loop_Render()
		{
			SetState(Engine::State::Rendering);

			Base::Utilities::Timer timer;

			double SavedX = 0, SavedY = 0;

			//Main Game Loop
			while (!Core::Application::PollEvents())
			{
				// per-frame time logic (ensure speed is constant through all platforms)
				float currentFrame = static_cast<float>(timer.GetElapsedTimeInSeconds());
				deltaTime = currentFrame - lastFrame;
				lastFrame = currentFrame;
				GamePtr->ClockTime = static_cast<float>(timer.GetElapsedTimeInSeconds());

				BeginFrame();

				//Mouse Movement Callback
				double MousePosX, MousePosY;
				Core::Application::GetMainWindow()->GetInput()->GetMousePosition(&MousePosX, &MousePosY);
				if (SavedX != MousePosX || SavedY != MousePosY)
				{
					SavedX = MousePosX;
					SavedY = MousePosY;
					GamePtr->OnMouseMovement(static_cast<int>(SavedX), static_cast<int>(SavedY));
				}

				GamePtr->Update(deltaTime);
				GamePtr->Render(deltaTime);

				EndFrame();
			}
		}

		void Engine::SetState(const State & state)
		{
			Engine_State = state;
			std::string name;
			switch (Engine_State)
			{
				case Engine::State::Initializing:
					name = "Initializing";
					break;
				case Engine::State::Loading:
					name = "Loading";
					break;
				case Engine::State::Rendering:
					name = "Rendering";
					break;
				case Engine::State::ExitingRendering:
					name = "Exiting Rendering";
					break;
				case Engine::State::Shuttingdown:
					name = "Shutting down";
					break;
				default:
					name = "Unknown";
					break;
			}

			Log.Info("[Engine] Game state changed to " + name + "\n");
		}

		void PrintIntroLog()
		{
			Log.Info("-------------------------- -REDx Game Engine- --------------------------\n");
			Log.Info("-------------------------- Redeaux Interactive --------------------------\n");
			Log.Info("[Engine] Starting Engine...\n");
			Log.Info("[Engine] Engine Build: ");
			Log.Info(MajorVersion);
			Log.Info(".");
			Log.Info(MinorVersion);
			Log.Info("  On: ");
			Log.Info(__DATE__);
			Log.Info("  At: ");
			Log.Info(__TIME__);
			Log.EndLine();

			Log.Info("[Engine] Built For: ");

#ifdef 	NUCLEAR_PLATFORM_WINDOWS_PC_32BIT
			Log.Info("Windows-PC 32 Bit");
#endif

#ifdef 	NUCLEAR_PLATFORM_WINDOWS_PC_64BIT
			Log.Info("Windows-PC 64 bit");
#endif

#ifdef 	_DEBUG
			Log.Info("  [DEBUG Build]\n");
#endif

#ifdef 	NDEBUG
			Log.Info("  [RELEASE Build]\n");
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4067)
#endif
		}
	}
}
