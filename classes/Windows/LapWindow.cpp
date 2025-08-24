#include "LapWindow.h"

#include "TelemetryConverters/TelemetryReader.h"
#include "Math/Vector.h"

namespace ImGui
{
	namespace Telemetry
	{
		LapWindow::LapWindow(std::string windowName)
			: ImGuiWindowBase(windowName)
			, m_TelemetryReader()
		{

		}

		LapWindow::~LapWindow()
		{

		}

		void LapWindow::Initialise()
		{
			std::cout << "Initialise ImGui Telemetry Window " << m_WindowName << std::endl;
		}

		void LapWindow::Shutdown()
		{
			std::cout << "Shutdown ImGui Telemetry Window " << m_WindowName << std::endl;
		}

		void LapWindow::Draw()
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

			float const lapTime = telemetryReader->GetCurrentLapTime();
			ImGui::Text("Time: %.3fs", lapTime);

			float const lastLapTime = telemetryReader->GetLastLapTime();
			ImGui::Text("Last Time: %.3fs", lastLapTime);

			float const bestLapTime = telemetryReader->GetBestLapTime();
			ImGui::Text("Best Time: %.3fs", bestLapTime);

			float const lastSectorTime = telemetryReader->GetLastSectorTime();
			ImGui::Text("Last Sector Time: %.3fs", lastSectorTime);

			int const completedLaps = telemetryReader->GetCompletedLaps();
			ImGui::Text("Completed Laps: %d", completedLaps);

			float const lapPercentage = telemetryReader->GetLapPercentage();
			ImGui::Text("Lap percentage: %.2f%", lapPercentage * 100.f);
		}

		void LapWindow::SetTelemetryReader(std::weak_ptr<::Telemetry::TelemetryReader> telemtryReader)
		{
			m_TelemetryReader = telemtryReader;
		}
	}
}