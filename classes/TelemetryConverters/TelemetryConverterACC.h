#pragma once
#include "TelemetryConverter.h"
#include <windows.h>
#include "ACC/SharedFileOut.h"

namespace Telemetry 
{
    namespace Converter 
    {
        class TelemetryConverterACC : public TelemetryConverter 
        {
        public:
            TelemetryConverterACC();
            ~TelemetryConverterACC();

            bool ReadTelemetryFromSource() override;

        private:
            HANDLE m_SharedMemoryHandle = nullptr;
            SPageFilePhysics* m_PhysicsData = nullptr;
        };

    }
}
