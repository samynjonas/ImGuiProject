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
		class TelemetryWindow : public ImGuiWindowBase
		{
		public:
			TelemetryWindow(std::string windowName);
			~TelemetryWindow();

			void Initialise() override;
			void Draw() override;
			void Shutdown() override;

		private:
			void DrawCenteredProgressBar(float value, const ImVec2& size);
			void DrawMap(const ImVec2& size, float padding = 1.f);

		private:
			std::shared_ptr<::Telemetry::TelemetryReader> m_TelemetryReader;

		};
	}
}