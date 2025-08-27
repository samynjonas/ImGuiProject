#include "ImGuiWindowBase.h"
#include "ImGuiManager.h"
#include "imgui_internal.h"

// Base
namespace ImGui
{
	ImGuiWindowBase::ImGuiWindowBase(std::string windowName)
		: ImGuiWindowBase(windowName, {})
	{

	}

	ImGuiWindowBase::ImGuiWindowBase(std::string windowName, ImGuiWindowFlags windowFlags)
		: m_WindowName(windowName)
		, m_WindowFlags(windowFlags)
	{

	}

	ImGuiWindowBase::~ImGuiWindowBase()
	{

	}

	void ImGuiWindowBase::SetDraw()
	{
		ImGui::Begin(m_WindowName.c_str(), nullptr, m_WindowFlags);
	}

	void ImGuiWindowBase::UnsetDraw()
	{
		ImGui::End();
	}

	void ImGuiWindowBase::PreDraw()
	{
		// This is where you could do input checks
		// You can get the input through the ImGuiIO& io = ImGui::GetIO(); call
	}

	void ImGuiWindowBase::DrawCenteredProgressBar(float value, const ImVec2& size)
	{
		// Clamp the input range to [-1.0, 1.0]
		value = ImClamp(value, -1.0f, 1.0f);

		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 full_size = size;
		ImVec2 center = ImVec2(pos.x + full_size.x * 0.5f, pos.y);
		ImVec2 frame_bb_max = ImVec2(pos.x + full_size.x, pos.y + full_size.y);
		ImRect bb(pos, frame_bb_max);

		ImGui::ItemSize(bb);
		if (!ImGui::ItemAdd(bb, 0))
			return;

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		// Draw background
		draw_list->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg), 4.0f);

		// Calculate bar region
		float mid = pos.x + full_size.x * 0.5f;
		float bar_extent = (full_size.x * 0.5f) * fabsf(value);
		float bar_min = (value >= 0) ? mid : mid - bar_extent;
		float bar_max = (value >= 0) ? mid + bar_extent : mid;

		ImVec2 bar_a(bar_min, pos.y);
		ImVec2 bar_b(bar_max, pos.y + full_size.y);

		// Draw progress portion
		draw_list->AddRectFilled(bar_a, bar_b, ImGui::GetColorU32(ImGuiCol_PlotHistogram), 4.0f);
	}
}

// Example
namespace ImGui
{
	ImGuiWindowExample::ImGuiWindowExample(std::string windowName)
		: ImGuiWindowBase(windowName, {})
	{

	}

	ImGuiWindowExample::ImGuiWindowExample(std::string windowName, ImGuiWindowFlags windowFlags)
		: ImGuiWindowBase(windowName, windowFlags)
	{

	}

	ImGuiWindowExample::~ImGuiWindowExample()
	{

	}

	void ImGuiWindowExample::Initialise()
	{
		std::cout << "Initialise ImGui Example Window " << m_WindowName << std::endl;
	}

	void ImGuiWindowExample::Shutdown()
	{
		std::cout << "Shutdown ImGui Example Window " << m_WindowName << std::endl;
	}

	void ImGuiWindowExample::Draw()
	{
		ImGui::Text("Example ImGui Window" __FUNCTION__);
	}

	void ImGuiWindowExample::PreDraw()
	{
		ImGui::Text("Example ImGui Window" __FUNCTION__);
	}
}