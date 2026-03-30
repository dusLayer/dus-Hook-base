#pragma once


void DrawCustomCursor()
{
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw = ImGui::GetForegroundDrawList();
    ImVec2 p = io.MousePos;

    float size = 6.0f;


    draw->AddLine(ImVec2(p.x - size, p.y), ImVec2(p.x + size, p.y),
        IM_COL32(255, 255, 255, 255), 1.0f);

    draw->AddLine(ImVec2(p.x, p.y - size), ImVec2(p.x, p.y + size),
        IM_COL32(255, 255, 255, 255), 1.0f);
}