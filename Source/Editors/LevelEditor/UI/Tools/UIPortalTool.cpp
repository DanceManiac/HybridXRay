﻿#include "stdafx.h"
UIPortalTool::UIPortalTool() {}

UIPortalTool::~UIPortalTool() {}

void UIPortalTool::Draw()
{
    ImGui::SetNextItemOpen(true, ImGuiCond_FirstUseEver);
    if (ImGui::TreeNode("Commands"_RU >> u8"Управление"))
    {
        ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
        {
            if (ImGui::Button("Invert Orientation"_RU >> u8"Инвертировать", ImVec2(-1, 0)))
            {
                ObjectList lst;
                if (Scene->GetQueryObjects(lst, OBJCLASS_PORTAL, 1, 1, 0))
                {
                    for (ObjectIt it = lst.begin(); it != lst.end(); it++)
                    {
                        CPortal* _O = (CPortal*)*it;
                        _O->InvertOrientation(true);
                    }
                }
            }
            if (ImGui::IsItemHovered())
                ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            if (ImGui::Button("Compute All Portals"_RU >> u8"Компилировать все порталы", ImVec2(-1, 0)))
            {
                if (mrYes ==
                    ELog.DlgMsg(mtConfirmation, mbYes | mbNo, "Are you sure want to destroy all existing portals and compute them again?"))
                {
                    int cnt = PortalUtils.CalculateAllPortals();
                    if (cnt)
                        ELog.DlgMsg(mtInformation, "Calculated '%d' portal(s).", cnt);
                }
            }
            if (ImGui::IsItemHovered())
                ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            if (ImGui::Button("Compute Sel. Portals"_RU >> u8"Компилировать выбранное", ImVec2(-1, 0)))
            {
                if (mrYes == ELog.DlgMsg(mtConfirmation, mbYes | mbNo, "Are you sure want to destroy all existing portals and compute them again?"))
                {
                    int cnt = PortalUtils.CalculateSelectedPortals();
                    if (cnt)
                        ELog.DlgMsg(mtInformation, "Calculated '%d' portal(s).", cnt);
                }
            }
            if (ImGui::IsItemHovered())
                ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            if (ImGui::Button("Remove Similar"_RU >> u8"Очистить", ImVec2(-1, 0)))
            {
                tool->RemoveSimilar();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        }
        ImGui::Separator();
        ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
        ImGui::TreePop();
    }
    if (ImGui::IsItemHovered())
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
}
