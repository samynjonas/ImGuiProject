#include "MapWindow.h"

#include "TelemetryConverters/TelemetryReader.h"
#include "Math/Vector.h"

namespace ImGui
{
	namespace Telemetry
	{
		MapWindow::MapWindow(std::string windowName)
			: ImGuiWindowBase(windowName, ImGuiWindowFlags_MenuBar)
			, m_TelemetryReader()
			, m_ZoomScale(1.f)
			, m_CenterOffset()
		{

		}

		MapWindow::~MapWindow()
		{

		}

		void MapWindow::Initialise()
		{
			std::cout << "Initialise ImGui Telemetry Window " << m_WindowName << std::endl;
		}

		void MapWindow::Shutdown()
		{
			std::cout << "Shutdown ImGui Telemetry Window " << m_WindowName << std::endl;
		}

		void MapWindow::Draw()
		{
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Settings"))
				{
					ImGui::MenuItem("Menu");

					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}


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

			int const activeCars = telemetryReader->GetActiveCars();
			if (activeCars <= 0)
			{
				ImGui::Text("----NO ACTIVE CARS FOUND----");
				return;
			}

			int const playerIndex = telemetryReader->GetPlayerCarIndex();
			if (playerIndex < 0 || playerIndex >= activeCars)
			{
				ImGui::Text("----PLAYER INDEX NOT VALID----");
				return;
			}

			std::vector<Math::Vec2> const& carPositions = telemetryReader->GetCarPositions();
			if (carPositions.empty())
			{
				ImGui::Text("----NO CAR POSITIONS FOUND----");
				return;
			}

			ImGui::SliderFloat("Zoom", &m_ZoomScale, 1.f, 100.f);
			
			ImGui::SliderFloat("X", &m_CenterOffset.X, -1000.f, 1000.f);
			ImGui::SliderFloat("Y", &m_CenterOffset.Y, -1000.f, 1000.f);


			for (int index = 0; index < activeCars; ++index)
			{
				bool const isLocalPlayer = (index == playerIndex);
				Math::Vec2 const carPosition = carPositions[index];

				if (isLocalPlayer)
				{
					m_PlayerTrail.push_back(carPosition);
					for (Math::Vec2 const& trailPoint : m_PlayerTrail)
					{
						Math::Vec2 const& trailMapLocation = GetScaledToWindowLocation(trailPoint);
						ImGui::GetWindowDrawList()->AddCircleFilled({ trailMapLocation.X, trailMapLocation.Y }, 1.f, IM_COL32(255, 255, 0, 200));
					}
				}

				Math::Vec2 const& carMapLocation = GetScaledToWindowLocation(carPosition);
				ImGui::GetWindowDrawList()->AddCircleFilled({ carMapLocation.X, carMapLocation.Y }, 5.f, IM_COL32(255, 0, 0, 255));
			}
		}

		void MapWindow::SetTelemetryReader(std::weak_ptr<::Telemetry::TelemetryReader> telemtryReader)
		{
			m_TelemetryReader = telemtryReader;
		}

		Math::Vec2 const& MapWindow::GetScaledToWindowLocation(Math::Vec2 carPosition) const
		{
			ImVec2 static windowPos = ImGui::GetWindowPos();
			ImVec2 static windowSize = ImGui::GetWindowSize();
			ImVec2 static windowCenter = { windowPos.x + windowSize.x / 2.f, windowPos.y + windowSize.y / 2.f };

			float const scaledX = carPosition.X * m_ZoomScale;
			float const scaledY = carPosition.Y * m_ZoomScale;

			return { windowCenter.x + m_CenterOffset.X + scaledX, windowCenter.y + m_CenterOffset.Y + scaledY };
		}
	}
}