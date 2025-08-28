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
            virtual void RefreshOnNewSession() override;
            virtual void ResetSession() override;
            virtual bool IsSessionsStarted() const override;
            virtual bool IsSessionsEnded() const override;

            virtual bool TryConnectToGame() override;
            virtual bool IsConnectedToGame() const override;

        private:
            HANDLE m_SharedMemoryHandle = nullptr;
            SPageFilePhysics* m_PhysicsData = nullptr;

            HANDLE m_GraphicsMemoryHandle = nullptr;
            SPageFileGraphic* m_GraphicsData = nullptr;

            HANDLE m_StaticMemoryHandle = nullptr;
            SPageFileStatic* m_StaticData = nullptr;

            int m_CurrentActiveCars;
            bool m_IsStartingNewSession;
        };
    }
}
