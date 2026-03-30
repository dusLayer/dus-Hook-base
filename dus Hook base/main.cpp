#include "includes.h"
#include "natives.h"
#include <chrono>
#include <algorithm>  
#include <string>
#include <vector>
#include <thread>
#include <cstdlib>
#include "Deps/Logger/Logger.h"
#include "Menu/Menu.h"
#include "Menu/Style.h"
#include "Menu/Cursor.h"
#include "main.h"
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include "Game/HookManager/Hooking_Manager.h"





ID3D11Device* pDevice = nullptr;
ID3D11DeviceContext* pContext = nullptr;
ID3D11RenderTargetView* mainRenderTargetView = nullptr;


HWND window = nullptr;
WNDPROC oWndProc = nullptr;




std::vector<Snowflake> snowflakes;
bool init = false;
float rainbowTimer = 0.0f;


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present oPresent;


Logger logger("");



void CreateConsole()
{
    AllocConsole();

    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONOUT$", "w", stderr);
    freopen_s(&f, "CONIN$", "r", stdin);

    std::cout.clear();
}



LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    if (uMsg == WM_KEYUP && wParam == VK_DELETE)
        UI::show = !UI::show;

    if (UI::show)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

        ImGuiIO& io = ImGui::GetIO();

        if (io.WantCaptureMouse || io.WantCaptureKeyboard)
            return true; 
    }


    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}




HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;

            ID3D11Texture2D* pBackBuffer = nullptr;
            HRESULT hrBuffer = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

            if (SUCCEEDED(hrBuffer) && pBackBuffer != nullptr) {
                pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mainRenderTargetView);
                pBackBuffer->Release();
                pBackBuffer = nullptr;
            }
            else {

                return oPresent(pSwapChain, SyncInterval, Flags);
            }

            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;

       
            if (snowflakes.empty())
            {
                for (int i = 0; i < 120; i++)
                {
                    snowflakes.push_back({
                        ImVec2((float)(rand() % 750), (float)(rand() % 550)),
                        0.4f + (rand() % 100) / 200.0f,
                        1.5f + (rand() % 3)
                        });
                }
            }
        }
        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }
    static bool once = false;
    if (!once)
    {
        logger.debug("hkPresent initialized");
        once = true;
    }

    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);



    static bool wasDown = false;
    bool isDown = GetAsyncKeyState(VK_DELETE) & 0x8000;

    if (isDown && !wasDown)
    {
        UI::show = !UI::show;
    }

    wasDown = isDown;

    Menu_Initi();
    

    return oPresent(pSwapChain, SyncInterval, Flags);

}




DWORD WINAPI MainThread(LPVOID lpReserved)
{
    
    CreateConsole();
    if (MH_Initialize() != MH_OK)
    {
        logger.error("Minhook failed");
        return 0;
    }
    logger.info("Minhook MH_Initialized");


    

    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {

            logger.info("Waiting for GameAssembly...");
            while (!ModuleGA) {
                ModuleGA = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
                Sleep(500);
            }
            
            HookingManager();
            
            kiero::bind(8, (void**)&oPresent, hkPresent);
            init_hook = true;
        }
    } while (!init_hook);
    return TRUE;
}




BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
        std::thread(MainThread, hMod).detach();
        break;
    case DLL_PROCESS_DETACH:
        kiero::shutdown();
        MH_Uninitialize();
        break;
    }
    return TRUE;
}
