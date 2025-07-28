#include "TelemetryWindow.h"

#include "TelemetryConverters/TelemetryReader.h"
#include "imgui_internal.h"

#include "Math/Vector.h"

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
			
			if (ImGui::Button("Set Origin from here"))
			{
				m_TelemetryReader->SetOriginFromCurrent();
			}
			
			Math::Vec2 const actualLocation = m_TelemetryReader->GetActualLocation();
			ImGui::Text("Actual Location: [%f;%f]", actualLocation.X, actualLocation.Y);
		
			Math::Vec2 const relativeLocation = m_TelemetryReader->GetRelativeLocation();
			ImGui::Text("Relative Location: [%f;%f]", relativeLocation.X, relativeLocation.Y);

			ImVec2 const contentPos = ImGui::GetCursorScreenPos();
			ImVec2 scaledLocation = { relativeLocation.X / 100.f, relativeLocation.Y / 100.f};
			ImGui::Text("Scaled Location: [%f;%f]", scaledLocation.x, scaledLocation.y);

			ImGui::GetWindowDrawList()->AddCircleFilled({ scaledLocation.x + contentPos.x + 50.f, scaledLocation.y + contentPos.y + 50.f }, 5.f, IM_COL32(255, 0, 0, 255));
			
			float const lapPercentage = m_TelemetryReader->GetLapPercentage();
			ImGui::ProgressBar(lapPercentage, ImVec2(200, 20), "LapPercentage");

			DrawMap({ 350.f, 250.f }, 25.f);
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
	
		void TelemetryWindow::DrawMap(const ImVec2& size, float padding)
		{
			ImVec2 windowPos = ImGui::GetWindowPos();
			ImVec2 windowSize = ImGui::GetWindowSize();

			// --- Top-right corner of ImGui window
			ImVec2 const mapTopLeft = ImVec2(
				windowPos.x + windowSize.x - size.x - padding,
				windowPos.y + padding
			);

			// Draw the outer box (just for debug)
			ImGui::GetForegroundDrawList()->AddRect(mapTopLeft,
				ImVec2(mapTopLeft.x + size.x, mapTopLeft.y + size.y),
				IM_COL32(255, 255, 255, 255), 0.0f, 0, 2.0f);
		}

	}
}