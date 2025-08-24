#pragma once
#include "TelemetryConverter.h"

#include "ACC/SharedFileOut.h"

#include <map>
#include <windows.h>

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
            bool TryConnectToGame();
            bool IsConnectedToGame() const;

        private:
            HANDLE m_SharedMemoryHandle = nullptr;
            SPageFilePhysics* m_PhysicsData = nullptr;

            HANDLE m_GraphicsMemoryHandle = nullptr;
            SPageFileGraphic* m_GraphicsData = nullptr;
        };

    }
}
