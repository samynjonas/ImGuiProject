#include "TelemetryConverterACC.h"
#include <iostream>

#include "Helper/Time.h"

namespace Telemetry 
{
    namespace Converter 
    {
        TelemetryConverterACC::TelemetryConverterACC() 
        {
            
        }

        TelemetryConverterACC::~TelemetryConverterACC() 
        {
            if (m_PhysicsData) UnmapViewOfFile(m_PhysicsData);
            if (m_SharedMemoryHandle) CloseHandle(m_SharedMemoryHandle);

            if (m_GraphicsData) UnmapViewOfFile(m_GraphicsData);
            if (m_GraphicsMemoryHandle) CloseHandle(m_GraphicsMemoryHandle);
        }

        bool TelemetryConverterACC::TryConnectToGame()
        {
            if (IsConnectedToGame())
            {
                return true;
            }

            bool connected{ true };

            // Physics data
            m_SharedMemoryHandle = OpenFileMappingA(FILE_MAP_READ, FALSE, "Local\\acpmf_physics");
            if (!m_SharedMemoryHandle)
            {
                std::cerr << "[ACC] Could not open shared memory: acpmf_physics" << std::endl;
                connected = false;
            }
            else
            {
                m_PhysicsData = static_cast<SPageFilePhysics*>(
                    MapViewOfFile(m_SharedMemoryHandle, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics))
                    );

                if (!m_PhysicsData)
                {
                    std::cerr << "[ACC] Failed to map shared memory view!" << std::endl;
                    connected = false;
                }
            }

            // Graphics data
            m_GraphicsMemoryHandle = OpenFileMappingA(FILE_MAP_READ, FALSE, "Local\\acpmf_graphics");
            if (!m_GraphicsMemoryHandle)
            {
                std::cerr << "[ACC] Could not open shared memory: acpmf_graphics" << std::endl;
                connected = false;
            }
            else
            {
                m_GraphicsData = static_cast<SPageFileGraphic*>(
                    MapViewOfFile(m_GraphicsMemoryHandle, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphic))
                    );
                if (!m_GraphicsData)
                {
                    std::cerr << "[ACC] Failed to map graphics memory view!" << std::endl;
                    connected = false;
                }
            }

            return connected;
        }

        bool TelemetryConverterACC::IsConnectedToGame() const
        {
            // No physics data to read from
            if (!m_PhysicsData || !m_GraphicsData)
            {
                return false;
            }
            return true;
        }

        bool TelemetryConverterACC::ReadTelemetryFromSource() 
        {
            if (!IsConnectedToGame())
            {
                if (!TryConnectToGame())
                {
                    return false;
                }
            }

            m_Output.Throttle = m_PhysicsData->gas;
            m_Output.Brake = m_PhysicsData->brake;
            m_Output.Steering = m_PhysicsData->steerAngle;

            m_Output.Gear = m_PhysicsData->gear;
            m_Output.SpeedKmh = m_PhysicsData->speedKmh;
            
            m_Output.LapPercentage = m_GraphicsData->normalizedCarPosition;
            m_Output.CompletedLaps = m_GraphicsData->completedLaps;

            Helper::LapTime lastSectorTime(m_GraphicsData->lastSectorTime);
            m_Output.LastSectorTimeSeconds = lastSectorTime.GetSeconds();

            Helper::LapTime bestTime(m_GraphicsData->iBestTime);
            m_Output.BestTimeSeconds = bestTime.GetSeconds();

            Helper::LapTime currentLapTime(m_GraphicsData->iCurrentTime);
            m_Output.CurrentTimeSeconds = currentLapTime.GetSeconds();

            Helper::LapTime lastLapTime(m_GraphicsData->iLastTime);
            m_Output.LastTimeSeconds = lastLapTime.GetSeconds();

            m_Output.ActiveCars = m_GraphicsData->activeCars;
            m_Output.PlayerCarIndex = m_GraphicsData->playerCarID;

            m_Output.CarPositions.clear();
            for (size_t index = 0; index < m_GraphicsData->activeCars; ++index)
            {
                float const x = m_GraphicsData->carCoordinates[index][0];
                //float const y = m_GraphicsData->carCoordinates[index][1];
                float const z = m_GraphicsData->carCoordinates[index][2];

                Math::Vec2 carPosition{ x, z };
                m_Output.CarPositions.push_back(carPosition);
            }

            return true;
        }

    } // namespace Converter
} // namespace Telemetry
