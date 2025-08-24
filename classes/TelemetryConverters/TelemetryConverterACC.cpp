#include "TelemetryConverterACC.h"
#include <iostream>

namespace Telemetry 
{
    namespace Converter 
    {
        TelemetryConverterACC::TelemetryConverterACC() 
        {
            // Physics data
            m_SharedMemoryHandle = OpenFileMappingA(FILE_MAP_READ, FALSE, "Local\\acpmf_physics");
            if (!m_SharedMemoryHandle) 
            {
                std::cerr << "[ACC] Could not open shared memory: acpmf_physics" << std::endl;
            }
            else 
            {
                m_PhysicsData = static_cast<SPageFilePhysics*>(
                    MapViewOfFile(m_SharedMemoryHandle, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics))
                    );
                if (!m_PhysicsData)
                    std::cerr << "[ACC] Failed to map shared memory view!" << std::endl;
            }

            // Graphics data
            m_GraphicsMemoryHandle = OpenFileMappingA(FILE_MAP_READ, FALSE, "Local\\acpmf_graphics");
            if (!m_GraphicsMemoryHandle) 
            {
                std::cerr << "[ACC] Could not open shared memory: acpmf_graphics" << std::endl;
            }
            else 
            {
                m_GraphicsData = static_cast<SPageFileGraphic*>(
                    MapViewOfFile(m_GraphicsMemoryHandle, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphic))
                    );
                if (!m_GraphicsData)
                    std::cerr << "[ACC] Failed to map graphics memory view!" << std::endl;
            }
        }

        TelemetryConverterACC::~TelemetryConverterACC() 
        {
            if (m_PhysicsData) UnmapViewOfFile(m_PhysicsData);
            if (m_SharedMemoryHandle) CloseHandle(m_SharedMemoryHandle);

            if (m_GraphicsData) UnmapViewOfFile(m_GraphicsData);
            if (m_GraphicsMemoryHandle) CloseHandle(m_GraphicsMemoryHandle);
        }

        void TelemetryConverterACC::SetupMapOrigins()
        {
            // SPA
            /*
                minX: -1074.26
                maxX: -1074.26
                minY: -1893.82
                maxY: -1893.82
            */
            Math::Vec2 const spaOrigin{-985.744f, -1431.45f};
            m_MapOrigins[ACC::Maps::BelgiumSpa] = spaOrigin;
        }

        Math::Vec2 TelemetryConverterACC::GetMapOrigin(ACC::Maps::Enum map) const
        {
            Math::Vec2 mapOrigin{};

            if (m_MapOrigins.contains(map))
            {
                mapOrigin = m_MapOrigins.at(map);
            }

            return mapOrigin;
        }

        bool TelemetryConverterACC::ReadTelemetryFromSource() 
        {
            // No physics data to read from
            if (!m_PhysicsData || !m_GraphicsData)
            {
                return false;
            }

            m_Output.Throttle = m_PhysicsData->gas;
            m_Output.Brake = m_PhysicsData->brake;
            m_Output.Steering = m_PhysicsData->steerAngle;

            m_Output.Gear = m_PhysicsData->gear;
            m_Output.SpeedKmh = m_PhysicsData->speedKmh;
            
            int const id = m_GraphicsData->playerCarID;
            if (id >= 0 && id < 60) 
            {
                float x = m_GraphicsData->carCoordinates[id][0];
                float z = m_GraphicsData->carCoordinates[id][2];
                m_Output.Location = Math::Vec2(x, z);
            }
            else 
            {
                m_Output.Location = Math::Vec2(0, 0);
            }

            m_Output.LapPercentage = m_GraphicsData->normalizedCarPosition;
            m_Output.CompletedLaps = m_GraphicsData->completedLaps;
            m_Output.LastSectorTime = m_GraphicsData->lastSectorTime;
            m_Output.BestTime = m_GraphicsData->iBestTime;
            m_Output.CurrentTime = m_GraphicsData->iCurrentTime;

            // Find out the current map
            ACC::Maps::Enum const currentMap = ACC::Maps::BelgiumSpa;
            m_Output.Origin = GetMapOrigin(currentMap);

            return true;
        }

    } // namespace Converter
} // namespace Telemetry
