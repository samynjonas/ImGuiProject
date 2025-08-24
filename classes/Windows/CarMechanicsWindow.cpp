#include "CarMechanicsWindow.h"

#include "TelemetryConverters/TelemetryReader.h"
#include "Math/Vector.h"

namespace ImGui
{
	namespace Telemetry
	{
		CarMechanicsWindow::CarMechanicsWindow(std::string windowName)
			: ImGuiWindowBase(windowName)
			, m_TelemetryReader()
		{

		}

		CarMechanicsWindow::~CarMechanicsWindow()
		{

		}

		void CarMechanicsWindow::Initialise()
		{
			std::cout << "Initialise ImGui Telemetry Window " << m_WindowName << std::endl;
		}

		void CarMechanicsWindow::Shutdown()
		{
			std::cout << "Shutdown ImGui Telemetry Window " << m_WindowName << std::endl;
		}

		void CarMechanicsWindow::Draw()
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

			int const gear = telemetryReader->GetGear();
			ImGui::Text("Gear: %d", gear);
			
			float const speed = telemetryReader->GetSpeedKmh();
			ImGui::Text("Speed: %0.1f Kmph", speed);
		}

		void CarMechanicsWindow::SetTelemetryReader(std::weak_ptr<::Telemetry::TelemetryReader> telemtryReader)
		{
			m_TelemetryReader = telemtryReader;
		}
	}
}