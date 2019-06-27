// dear imgui: Renderer for DirectX11
// This needs to be used along with a Platform Binding (e.g. Win32)

// Implemented features:
//  [X] Renderer: User texture binding. Use 'ID3D11ShaderResourceView*' as ImTextureID. Read the FAQ about ImTextureID in imgui.cpp.
//  [X] Renderer: Support for large meshes (64k+ vertices) with 16-bits indices.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you are new to dear imgui, read examples/README.txt and read the documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

#pragma once
#include "ImGUI/imgui.h"

IMGUI_IMPL_API bool     ImGui_Impl_Init();
IMGUI_IMPL_API void     ImGui_Impl_Shutdown();
IMGUI_IMPL_API void     ImGui_Impl_NewFrame();
IMGUI_IMPL_API void     ImGui_Impl_RenderDrawData(ImDrawData* draw_data);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_IMPL_API void     ImGui_Impl_InvalidateDeviceObjects();
IMGUI_IMPL_API bool     ImGui_Impl_CreateDeviceObjects();
