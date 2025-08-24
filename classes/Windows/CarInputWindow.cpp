#include "CarInputWindow.h"

#include "TelemetryConverters/TelemetryReader.h"
#include "imgui_internal.h"

#include "Math/Vector.h"

namespace ImGui
{
	namespace Telemetry
	{
		CarInputWindow::CarInputWindow(std::string windowName)
			: ImGuiWindowBase(windowName)
			, m_TelemetryReader()
		{

		}

		CarInputWindow::~CarInputWindow()
		{

		}

		void CarInputWindow::Initialise()
		{
			std::cout << "Initialise ImGui Telemetry Window " << m_WindowName << std::endl;
		}

		void CarInputWindow::Shutdown()
		{
			std::cout << "Shutdown ImGui Telemetry Window " << m_WindowName << std::endl;
		}

		void CarInputWindow::Draw()
		{
			std::shared_ptr<::Telemetry::TelemetryReader> telemetryReader = m_TelemetryReader.lock();
			if (!telemetryReader)
			{
				ImGui::Text("----NO TELEMETRY READER FOUND----");
				return;
			}


			bool validTelemetry{ false };
			telemetryReader->Update(validTelemetry);

			if (!validTelemetry)
			{
				ImGui::Text("----NO GAME RUNNING----");
			}

			float const throttle = telemetryReader->GetThrottle();
			ImGui::ProgressBar(throttle, ImVec2(200, 20), "Throttle");

			float const brake = telemetryReader->GetBrake();
			ImGui::ProgressBar(brake, ImVec2(200, 20), "Brake");

			float const steering = telemetryReader->GetSteering();
			DrawCenteredProgressBar(steering, ImVec2(200, 20));
		}

		void CarInputWindow::SetTelemetryReader(std::weak_ptr<::Telemetry::TelemetryReader> telemtryReader)
		{
			m_TelemetryReader = telemtryReader;
		}
	}
}