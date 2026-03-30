#pragma once
#include "main.h"
#include "Cursor.h"
#include "Style.h"
#include "../Deps/imgui/imgui.h"
#include <cstdlib>
#include <string>
#include <vector>
#include "../natives.h"
#include "../Deps/Logger/Logger.h"

#include "Notification.h"

#include <algorithm>
#include <cctype>



Logger logger1("Log.log");



void HandleMenuToggle()
{
    static bool wasDown = false;
    bool isDown = GetAsyncKeyState(VK_DELETE) & 0x8000;


    if (isDown && !wasDown)
    {
        UI::show = !UI::show;
        UI::showLog = !UI::show;
    }


    wasDown = isDown;
}


void DrawFPS()
{
    if (!UI::showFPS)
        return;

    ImGuiIO& io = ImGui::GetIO();
    float fps = io.Framerate;

    char buffer[64];
    sprintf_s(buffer, "dus Hook base FPS: %.0f", fps);

    ImDrawList* draw = ImGui::GetForegroundDrawList();

    ImVec2 textSize = ImGui::CalcTextSize(buffer);
    ImVec2 screenSize = io.DisplaySize;

    float paddingX = 8.0f;
    float paddingY = 4.0f;

    float boxWidth = textSize.x + paddingX * 2;
    float boxHeight = textSize.y + paddingY * 2;

   
    float x = floorf((screenSize.x * 0.5f) - (boxWidth * 0.5f));
    float y = 12.0f;

    ImVec2 boxMin(x, y);
    ImVec2 boxMax(x + boxWidth, y + boxHeight);

  
    draw->AddRectFilled(
        boxMin,
        boxMax,
        IM_COL32(0, 0, 0, 140), 
        0.0f 
    );

  
    draw->AddRect(
        boxMin,
        boxMax,
        IM_COL32(255, 255, 255, 60),
        0.0f,
        0,
        1.0f
    );


    draw->AddText(
        ImVec2(x + paddingX, y + paddingY),
        IM_COL32(255, 255, 255, 255),
        buffer
    );
}

void DrawCrosshair()
{
    if (!UI::showCrosshair)
        return;

    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw = ImGui::GetForegroundDrawList();

    float cx = io.DisplaySize.x * 0.5f;
    float cy = io.DisplaySize.y * 0.5f;


    ImU32 color = IM_COL32(
        (int)(UI::crosshairColor.x * 255),
        (int)(UI::crosshairColor.y * 255),
        (int)(UI::crosshairColor.z * 255),
        (int)(UI::crosshairColor.w * 255)
    );

    float size = UI::crosshairSize;
    float thickness = UI::crosshairThickness;

    
    draw->AddLine(ImVec2(cx - size, cy), ImVec2(cx + size, cy), color, thickness);

 
    draw->AddLine(ImVec2(cx, cy - size), ImVec2(cx, cy + size), color, thickness);
}





void Menu_Initi() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    DrawFPS();
    HandleMenuToggle();
    DrawCrosshair();
    DrawNotification();



    if (UI::show)
    {
        ShowCursor(FALSE);
        DrawCustomCursor();

        ImGui::SetNextWindowSize(ImVec2(850, 550), ImGuiCond_Always);
        ImGui::Begin("dus Hook base By dusLayer", &UI::show,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoTitleBar);

        ImDrawList* draw = ImGui::GetWindowDrawList();
        ImVec2 winPos = ImGui::GetWindowPos();
        ImVec2 winSize = ImGui::GetWindowSize();

        float rounding = 10.0f;

        
        draw->AddRect(
            winPos,
            ImVec2(winPos.x + winSize.x, winPos.y + winSize.y),
            IM_COL32(0, 0, 0, 200),
            rounding,
            0,
            2.0f
        );

      
        draw->AddRectFilled(
            winPos,
            ImVec2(winPos.x + winSize.x, winPos.y + 45),
            IM_COL32(25, 25, 28, 255),
            rounding,
            ImDrawFlags_RoundCornersTop
        );

        
        ImVec2 titleSize = ImGui::CalcTextSize("dus Hook base By dusLayer");
        draw->AddText(
            ImVec2(
                winPos.x + (winSize.x / 2) - (titleSize.x / 2),
                winPos.y + 12
            ),
            IM_COL32(255, 255, 255, 255),
            "dus Hook base By dusLayer"
        );

        ImGui::Dummy(ImVec2(0, 30)); 

        if (ImGui::BeginTabBar("##MainTabBar"))
        {
            
            ImVec2 contentMin = ImGui::GetWindowPos();
            ImVec2 contentMax = ImVec2(
                contentMin.x + ImGui::GetWindowSize().x,
                contentMin.y + ImGui::GetWindowSize().y
            );

            
            draw->PushClipRect(
                ImVec2(contentMin.x, contentMin.y + 45),
                contentMax,
                true
            );

            for (auto& s : snowflakes)
            {
                s.pos.y += s.speed;

                if (s.pos.y > ImGui::GetWindowSize().y)
                {
                    s.pos.y = 0;
                    s.pos.x = (float)(rand() % (int)ImGui::GetWindowSize().x);
                }

                float px = contentMin.x + s.pos.x;
                float py = contentMin.y + 45 + s.pos.y; 

                draw->AddRectFilled(
                    ImVec2(px, py),
                    ImVec2(px + s.size, py + s.size),
                    IM_COL32(255, 255, 255, 180),
                    2.0f
                );
            }

            draw->PopClipRect();




            if (ImGui::BeginTabItem("Tab 1"))
            {
                

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Tab 2"))
            {


                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("Tab 3"))
            {


                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("Settings"))
            {
                ImGui::Checkbox("Show FPS", &UI::showFPS);

                if (ImGui::CollapsingHeader("Crosshair"))
                {
                    ImGui::Checkbox("Show Crosshair", &UI::showCrosshair);
                    ImGui::ColorEdit4("Crosshair Color", (float*)&UI::crosshairColor);
                    ImGui::SliderFloat("Size", &UI::crosshairSize, 5.0f, 30.0f);
                    ImGui::SliderFloat("Thickness", &UI::crosshairThickness, 1.0f, 5.0f);
                }

                ImGui::EndTabItem();
            }





            ImGui::EndTabBar();
        }

        ImGui::End();
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}