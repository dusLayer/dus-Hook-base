#pragma once
#include <string>
#include "../Deps/imgui/imgui.h"
#include <math.h>
#include <algorithm>
#include <algorithm>
struct Notification
{
    std::string text;
    float timer = 0.0f;
    float duration = 3.0f;

    bool active = false;
};

static Notification g_Notification;
static float g_LastNotifyTime = 0.0f;
static float g_NotifyCooldown = 1.0f;

void ShowNotification(const std::string& text, float duration = 3.0f)
{
    float currentTime = ImGui::GetTime();

   
    if (currentTime - g_LastNotifyTime < g_NotifyCooldown)
        return;

    g_LastNotifyTime = currentTime;

    g_Notification.text = text;
    g_Notification.duration = duration;
    g_Notification.timer = 0.0f;
    g_Notification.active = true;
}


inline float LerpFloat(float a, float b, float t)
{
    return a + (b - a) * t;
}

void DrawNotification()
{
    if (!g_Notification.active)
        return;

    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw = ImGui::GetForegroundDrawList();

    g_Notification.timer += io.DeltaTime;

    float animTime = 0.35f;
    float screenWidth = io.DisplaySize.x;

    ImVec2 textSize = ImGui::CalcTextSize(g_Notification.text.c_str());
    float boxWidth = textSize.x + 40.0f;
    float boxHeight = 40.0f;

    float x = (screenWidth - boxWidth) * 0.5f;
    float y = -boxHeight;

    
    if (g_Notification.timer <= animTime)
    {
        float t = g_Notification.timer / animTime;
        y = LerpFloat(-boxHeight, 40.0f, t);
    }
    
    else if (g_Notification.timer <= g_Notification.duration)
    {
        y = 40.0f;
    }
 
    else if (g_Notification.timer <= g_Notification.duration + animTime)
    {
        float t = (g_Notification.timer - g_Notification.duration) / animTime;
        y = LerpFloat(40.0f, -boxHeight, t);
    }
    else
    {
        g_Notification.active = false;
        return;
    }

    ImVec2 boxMin = ImVec2(x, y);
    ImVec2 boxMax = ImVec2(x + boxWidth, y + boxHeight);


    draw->AddRectFilled(
        boxMin,
        boxMax,
        IM_COL32(15, 15, 18, 230),
        8.0f
    );

   
    draw->AddRect(
        boxMin,
        boxMax,
        IM_COL32(255, 255, 255, 40),
        8.0f,
        0,
        1.5f
    );


    draw->AddText(
        ImVec2(x + 20.0f, y + 12.0f),
        IM_COL32(255, 255, 255, 255),
        g_Notification.text.c_str()
    );
}