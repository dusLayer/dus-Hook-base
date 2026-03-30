#include <Windows.h>
#include <vector>
#include <string>
#include "natives.h"
#include "Deps/imgui/imgui.h"



namespace UI
{
    bool show = false;
    bool showFPS = true;
    bool showLog = false;

    bool showCrosshair = false;
    ImVec4 crosshairColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    float crosshairSize = 10.0f;
    float crosshairThickness = 1.5f;
}