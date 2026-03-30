#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include "Deps/imgui/imgui.h"



namespace UI
{
    extern bool show;
    extern bool showFPS;
    extern bool showLog;

    extern  bool showCrosshair;
    extern ImVec4 crosshairColor;
    extern float crosshairSize;
    extern float crosshairThickness;
}