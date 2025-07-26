#include "TelemetryWindow.h"

#include "TelemetryConverters/TelemetryReader.h"
#include "imgui_internal.h"

namespace ImGui
{
	namespace Telemetry
	{
		TelemetryWindow::TelemetryWindow(std::string windowName)
			: ImGuiWindowBase(windowName)
			, m_TelemetryReader()
		{

		}

		TelemetryWindow::~TelemetryWindow()
		{

		}

		void TelemetryWindow::Initialise()
		{
			std::cout << "Initialise ImGui Telemetry Window " << m_WindowName << std::endl;
			m_TelemetryReader = std::make_shared<::Telemetry::TelemetryReader>();
		}

		void TelemetryWindow::Shutdown()
		{
			std::cout << "Shutdown ImGui Telemetry Window " << m_WindowName << std::endl;
		}

		void TelemetryWindow::Draw()
		{
			bool validTelemetry{ false };
			m_TelemetryReader->Update(validTelemetry);

			ImGui::Text("----Telemetry ImGui Window----");
			if(!validTelemetry)
			{
				ImGui::Text("----NO GAME RUNNING----");
			}

			float const throttle = m_TelemetryReader->GetThrottle();
			ImGui::ProgressBar(throttle, ImVec2(200, 20), "Throttle");
			
			float const brake = m_TelemetryReader->GetBrake();
			ImGui::ProgressBar(brake, ImVec2(200, 20), "Brake");
			
			float const steering = m_TelemetryReader->GetSteering();
			DrawCenteredProgressBar(steering, ImVec2(200, 20));
		
			int const gear = m_TelemetryReader->GetGear();
			ImGui::Text("Gear: %d", gear);
		}

		void TelemetryWindow::DrawCenteredProgressBar(float value, const ImVec2& size)
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
}