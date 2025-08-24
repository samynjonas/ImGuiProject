#pragma once
#include "ImGuiWindowBase.h"
#include <iostream>

namespace Telemetry
{
	class TelemetryReader;
}

namespace ImGui
{
	namespace Telemetry
	{
		class LapWindow : public ImGuiWindowBase
		{
		public:
			LapWindow(std::string windowName);
			~LapWindow();

			void Initialise() override;
			void Draw() override;
			void Shutdown() override;

			void SetTelemetryReader(std::weak_ptr<::Telemetry::TelemetryReader> telemtryReader);

		private:
			std::weak_ptr<::Telemetry::TelemetryReader> m_TelemetryReader;

		};
	}
}