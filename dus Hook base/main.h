#pragma once
#include <d3d11.h>
#include <windows.h>
#include <vector>
#include "Deps/imgui/imgui.h"


extern ID3D11Device* pDevice;
extern ID3D11DeviceContext* pContext;
extern ID3D11RenderTargetView* mainRenderTargetView;


extern HWND window;
extern WNDPROC oWndProc;


namespace UI
{
    extern bool show;
}


struct Snowflake
{
    ImVec2 pos;
    float speed;
    float size;
};


extern std::vector<Snowflake> snowflakes;
