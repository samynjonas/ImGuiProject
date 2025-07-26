#include "TelemetryConverterACC.h"
#include <iostream>

namespace Telemetry 
{
    namespace Converter 
    {

        TelemetryConverterACC::TelemetryConverterACC() 
        {
            m_SharedMemoryHandle = OpenFileMappingA(FILE_MAP_READ, FALSE, "Local\\acpmf_physics");

            if (!m_SharedMemoryHandle) 
            {
                std::cerr << "[ACC] Could not open shared memory: acpmf_physics" << std::endl;
                return;
            }

            m_PhysicsData = static_cast<SPageFilePhysics*>(
                MapViewOfFile(m_SharedMemoryHandle, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics))
                );

            if (!m_PhysicsData) 
            {
                std::cerr << "[ACC] Failed to map shared memory view!" << std::endl;
            }
        }

        TelemetryConverterACC::~TelemetryConverterACC() 
        {
            if (m_PhysicsData) 
            {
                UnmapViewOfFile(m_PhysicsData);
                m_PhysicsData = nullptr;
            }
            if (m_SharedMemoryHandle) 
            {
                CloseHandle(m_SharedMemoryHandle);
                m_SharedMemoryHandle = nullptr;
            }
        }

        bool TelemetryConverterACC::ReadTelemetryFromSource() 
        {
            // No physics data to read from
            if (!m_PhysicsData)
            {
                return false;
            }

            m_Output.Throttle = m_PhysicsData->gas;
            m_Output.Brake = m_PhysicsData->brake;
            m_Output.Steering = m_PhysicsData->steerAngle;
            m_Output.Gear = m_PhysicsData->gear;
            return true;
        }

    } // namespace Converter
} // namespace Telemetry
