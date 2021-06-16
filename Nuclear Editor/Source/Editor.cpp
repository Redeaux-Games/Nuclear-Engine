#include "CNuclearEditor.h"

namespace REDxEditor
{
	void Start()
	{
		Core::EngineStartupDesc desc;
		Core::Engine::Start(desc);
		CNuclearEditor Editor;
		Core::Engine::RunGame(&Editor);
		Core::Engine::Shutdown();
	}
}
