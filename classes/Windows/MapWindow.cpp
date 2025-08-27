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
			, m_ToggleMapDebugging(false)
			, m_ToggleLocalPlayer(true)
			, m_ToggleOtherPlayers(true)
			, m_ToggleTrail(true)
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

		void MapWindow::PreDraw()
		{
			ImGuiIO& io = ImGui::GetIO();

			float constexpr c_ZoomSpeed{ 0.01f };
			m_ZoomScale += io.MouseWheel * c_ZoomSpeed;
			if (m_ZoomScale < 0)
			{
				float constexpr c_MinZoomScale{ 0.00000001f };
				m_ZoomScale = c_MinZoomScale;
			}

			if (ImGui::IsMouseDown(1))
			{
				float xDelta = io.MouseDelta.x;
				float yDelta = io.MouseDelta.y;

				m_CenterOffset.X += xDelta;
				m_CenterOffset.Y += yDelta;
			}
		}

		void MapWindow::Draw()
		{
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Settings"))
				{
					ImGui::MenuItem("Toggle Map Debugging", nullptr, &m_ToggleMapDebugging);
					ImGui::MenuItem("Toggle Local Player", nullptr, &m_ToggleLocalPlayer);
					ImGui::MenuItem("Toggle Other Players", nullptr, &m_ToggleOtherPlayers);
					ImGui::MenuItem("Toggle Trail", nullptr, &m_ToggleTrail);

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

			// PlayerCarIndex may not be the index of the player but the ID to the car(type of car)
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

			ImGui::Text("Scale %f", m_ZoomScale);
			ImGui::Text("X %f", m_CenterOffset.X);
			ImGui::Text("Y %f", m_CenterOffset.Y);

			if (m_ToggleMapDebugging)
			{
				ImVec2 const windowPos = ImGui::GetWindowPos();
				ImGui::Text("windowPos: [%.2f, %.2f]", windowPos.x, windowPos.y);

				ImVec2 const windowSize = ImGui::GetWindowSize();
				ImGui::Text("windowSize: [%.2f, %.2f]", windowSize.x, windowSize.y);

				ImVec2 const windowCenter = { windowPos.x + (windowSize.x), windowPos.y + (windowSize.y) };
				ImGui::Text("windowCenter: [%.2f, %.2f]", windowCenter.x, windowCenter.y);
			}

			for (int index = 0; index < activeCars; ++index)
			{
				bool const isLocalPlayer = (index == playerIndex);
				Math::Vec2 const carPosition = carPositions[index];

				if (m_ToggleMapDebugging)
				{
					ImGui::Text("Player %d Positions: [%.2f, %.2f]", index, carPosition.X, carPosition.Y);
				}

				if (isLocalPlayer)
				{
					m_PlayerTrail.push_back(carPosition);
					if (m_ToggleTrail)
					{
						for (Math::Vec2 const& trailPoint : m_PlayerTrail)
						{
							Math::Vec2 const& trailMapLocation = GetScaledToWindowLocation(trailPoint);
							ImGui::GetWindowDrawList()->AddCircleFilled({ trailMapLocation.X, trailMapLocation.Y }, 1.f, IM_COL32(255, 255, 0, 200));
						}
					}
				}

				if ((isLocalPlayer && m_ToggleLocalPlayer) || (!isLocalPlayer && m_ToggleLocalPlayer))
				{
					Math::Vec2 const& carMapLocation = GetScaledToWindowLocation(carPosition);

					if (m_ToggleMapDebugging)
					{
						ImGui::Text("Map Location Player %d Positions: [%.2f, %.2f]", index, carMapLocation.X, carMapLocation.Y);
					}

					ImGui::GetWindowDrawList()->AddCircleFilled({ carMapLocation.X, carMapLocation.Y }, 5.f, IM_COL32(255, 0, 0, 255));
				}
			}
		}

		void MapWindow::SetTelemetryReader(std::weak_ptr<::Telemetry::TelemetryReader> telemtryReader)
		{
			m_TelemetryReader = telemtryReader;
		}

		Math::Vec2 MapWindow::GetScaledToWindowLocation(Math::Vec2 carPosition) const
		{
			ImVec2 const windowPos = ImGui::GetWindowPos();
			ImVec2 const windowSize = ImGui::GetWindowSize();
			ImVec2 const windowCenter = { windowPos.x + windowSize.x, windowPos.y + windowSize.y };

			float const scaledX = carPosition.X * m_ZoomScale;
			float const scaledY = carPosition.Y * m_ZoomScale;

			float const mapPositionX = windowCenter.x + m_CenterOffset.X + scaledX;
			float const mapPositionY = windowCenter.y + m_CenterOffset.Y + scaledY;

			return { mapPositionX, mapPositionY };
		}
	}
}