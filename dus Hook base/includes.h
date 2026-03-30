#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "Deps/kiero/kiero.h"
#include "Deps/imgui/imgui.h"
#include "Deps/imgui/imgui_impl_win32.h"
#include "Deps/imgui/imgui_impl_dx11.h"
#include <thread>
#include <string>
#include <iostream>
#include <cmath>

uintptr_t ModuleGA = (uintptr_t)GetModuleHandleA(("GameAssembly.dll"));



typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;



struct Quaternion {
	float x, y, z, w;
};

struct Vector3 {
	float x, y, z;
};

struct Vector2 {
	float x, y;
};