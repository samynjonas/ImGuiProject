#pragma once
#include "ImGuiWindowBase.h"

#include "Helper/TextureLoader.h"
#include "Math/Vector.h"
#include <glad/glad.h>
#include <iostream>
#include <optional>
#include <vector>

namespace Telemetry
{
	class TelemetryReader;
}

namespace ImGui
{
	namespace Telemetry
	{
		class MapWindow : public ImGuiWindowBase
		{
		public:
			MapWindow(std::string windowName);
			~MapWindow();

			void Initialise() override;

			void PreDraw() override;
			void Draw() override;
			
			void Shutdown() override;

			void SetTelemetryReader(std::weak_ptr<::Telemetry::TelemetryReader> telemtryReader);

		private:
			Math::Vec2 GetScaledToWindowLocation(Math::Vec2 carPosition) const;

		private:
			std::weak_ptr<::Telemetry::TelemetryReader> m_TelemetryReader;

			float m_ZoomScale;
			Math::Vec2 m_CenterOffset;
			std::vector<Math::Vec2> m_PlayerTrail;
		
			bool m_ToggleMapDebugging;
			bool m_ToggleLocalPlayer;
			bool m_ToggleOtherPlayers;
			bool m_ToggleTrail;

			GLImage m_MapTex = 0;
		};
	}
}