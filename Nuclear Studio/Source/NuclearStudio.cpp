// NuclearStudio.cpp
#include <NuclearEngine.h>
using namespace NuclearEngine;

class NuclearStudioEditor : public Core::Editor
{
protected:
	
public:
	NuclearStudioEditor()
	{
	}
	void Load() override
	{
		Core::Application::Display();
		Graphics::API::Context::SetPrimitiveType(Graphics::PrimitiveType::TriangleList);
	}

	void Render(float) override		// Render The Game
	{
		//Begin Frame
		Graphics::API::Context::Clear(Graphics::Color(0.0f, 0.0f, 0.0f, 1.0f), ClearColorBuffer | ClearDepthBuffer);
		ImGui::NE_NewFrame();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::Render();
		Graphics::API::Context::PresentFrame();
	}

	void Shutdown() override
	{

	}
};
void Start()
{
	char choice;
	std::cout << "--Choose A Renderer: \nA) OpenGL 3 \nB) DirectX 11\n";
	std::cin >> choice;
	Core::EngineStartupDesc desc;
	if (choice == 'a') {
		desc.mAppdesc.renderer = Core::RenderAPI::OpenGL3;
	}
	else if (choice == 'b')
	{
		desc.mAppdesc.renderer = Core::RenderAPI::DirectX11;
	}
	else {
		std::cout << "Wrong choice thus setting to DirectX 11 as default on window.\n";
		desc.mAppdesc.renderer = Core::RenderAPI::DirectX11;
	}
	Core::Engine::Start(desc);
}



int main()
{
	Start();
	NuclearStudioEditor instance;
	Core::Engine::RunGame(&instance);
    return 0;
}

