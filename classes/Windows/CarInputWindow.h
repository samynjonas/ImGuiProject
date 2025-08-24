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
		class CarInputWindow : public ImGuiWindowBase
		{
		public:
			CarInputWindow(std::string windowName);
			~CarInputWindow();

			void Initialise() override;
			void Draw() override;
			void Shutdown() override;

			void SetTelemetryReader(std::weak_ptr<::Telemetry::TelemetryReader> telemtryReader);

		private:
			std::weak_ptr<::Telemetry::TelemetryReader> m_TelemetryReader;

		};
	}
}