#include "ImGuiHelpers.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace ImGui
{
    static inline void BuildUVQuad(Math::Vec2 uv_min, Math::Vec2 uv_max, bool flip_y, GLImageRotation::Enum rotation, Math::Vec2 uv_out[4])
    {
        Math::Vec2 tl(uv_min.X, uv_min.Y);
        Math::Vec2 tr(uv_max.X, uv_min.Y);
        Math::Vec2 br(uv_max.X, uv_max.Y);
        Math::Vec2 bl(uv_min.X, uv_max.Y);

        if (flip_y) 
        {
            std::swap(tl.Y, bl.Y);
            std::swap(tr.Y, br.Y);
        }

        switch (rotation)
        {
        case GLImageRotation::R0:   uv_out[0] = tl; uv_out[1] = tr; uv_out[2] = br; uv_out[3] = bl; break;
        case GLImageRotation::R90:  uv_out[0] = bl; uv_out[1] = tl; uv_out[2] = tr; uv_out[3] = br; break;
        case GLImageRotation::R180: uv_out[0] = br; uv_out[1] = bl; uv_out[2] = tl; uv_out[3] = tr; break;
        case GLImageRotation::R270: uv_out[0] = tr; uv_out[1] = br; uv_out[2] = bl; uv_out[3] = tl; break;
        }
    }

    void AddImage(const GLImageParams& imageParams, bool drawDebugOutline)
    {
        if (!imageParams.image)
            return;

        ImDrawList* dl = ImGui::GetWindowDrawList();

        Math::Vec2 tl = imageParams.top_left;
        Math::Vec2 size = imageParams.size;

        if (size.X <= 0 || size.Y <= 0) 
        {
            tl = ImGui::GetCursorScreenPos();
            size = ImGui::GetContentRegionAvail();
        }

        Math::Vec2 center(tl.X + size.X * 0.5f, tl.Y + size.Y * 0.5f);
        Math::Vec2 half(size.X * 0.5f * imageParams.zoom, size.Y * 0.5f * imageParams.zoom);
        Math::Vec2 pan = imageParams.pan;

        Math::Vec2 p1(center.X - half.X + pan.X, center.Y - half.Y + pan.Y);
        Math::Vec2 p2(center.X + half.X + pan.X, center.Y - half.Y + pan.Y);
        Math::Vec2 p3(center.X + half.X + pan.X, center.Y + half.Y + pan.Y);
        Math::Vec2 p4(center.X - half.X + pan.X, center.Y + half.Y + pan.Y);

        Math::Vec2 uvq[4];
        BuildUVQuad(imageParams.uv_min, imageParams.uv_max,imageParams.flip_y, imageParams.rotation, uvq);

        if (drawDebugOutline) 
        {
            dl->AddRect(p1, p3, IM_COL32(0, 255, 0, 255), 0.0f, 0, 2.0f);
        }

        dl->AddImageQuad(imageParams.image, p1, p2, p3, p4,uvq[0], uvq[1], uvq[2], uvq[3]);
    }
}

