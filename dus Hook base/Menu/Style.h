#pragma once
#include "main.h"
#include "../Deps/imgui/imgui.h"
#include "../Deps/imgui/imgui_impl_dx11.h"
#include "../Deps/imgui/imgui_impl_win32.h"

void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange | ImGuiConfigFlags_NavEnableKeyboard;
    io.MouseDrawCursor = false;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();



    style.WindowRounding = 10.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.TabRounding = 6.0f;

    
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.TabBorderSize = 1.0f;

    style.WindowPadding = ImVec2(12, 12);
    style.FramePadding = ImVec2(8, 5);
    style.ItemSpacing = ImVec2(8, 6);

    
    ImVec4 bg = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    ImVec4 dark = ImVec4(0.12f, 0.12f, 0.13f, 1.00f);
    ImVec4 light = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);
    ImVec4 accent = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);

    style.Colors[ImGuiCol_WindowBg] = bg;
    style.Colors[ImGuiCol_ChildBg] = bg;

    style.Colors[ImGuiCol_Border] = ImVec4(0, 0, 0, 0.6f);

    style.Colors[ImGuiCol_TitleBg] = dark;
    style.Colors[ImGuiCol_TitleBgActive] = light;

    style.Colors[ImGuiCol_FrameBg] = dark;
    style.Colors[ImGuiCol_FrameBgHovered] = light;
    style.Colors[ImGuiCol_FrameBgActive] = light;

    style.Colors[ImGuiCol_Button] = dark;
    style.Colors[ImGuiCol_ButtonHovered] = light;
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.25f, 0.28f, 1.00f);

    style.Colors[ImGuiCol_Tab] = dark;
    style.Colors[ImGuiCol_TabHovered] = light;
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);

    style.Colors[ImGuiCol_CheckMark] = accent;
    style.Colors[ImGuiCol_SliderGrab] = accent;
    style.Colors[ImGuiCol_SliderGrabActive] = accent;

    style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);


    io.Fonts->Clear();

    ImFont* pixelFont = io.Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\consola.ttf", 
        13.0f,
        NULL,
        io.Fonts->GetGlyphRangesDefault()
    );

    io.FontDefault = pixelFont;


    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
}