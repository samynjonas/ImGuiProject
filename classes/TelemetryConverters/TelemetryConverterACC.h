#pragma once
#include "TelemetryConverter.h"

#include "ACC/SharedFileOut.h"

#include <map>
#include <windows.h>

namespace Telemetry 
{
    namespace Converter 
    {
        namespace ACC
        {
            namespace Maps
            {
                enum Enum
                {
                    BelgiumSpa = 0,
                    EnumCount
                };
            }
        }

        class TelemetryConverterACC : public TelemetryConverter 
        {
        public:
            TelemetryConverterACC();
            ~TelemetryConverterACC();

            bool ReadTelemetryFromSource() override;

            Math::Vec2 GetMapOrigin(ACC::Maps::Enum map) const;
        private:
            void SetupMapOrigins();

        private:
            std::map<ACC::Maps::Enum, Math::Vec2> m_MapOrigins;

            HANDLE m_SharedMemoryHandle = nullptr;
            SPageFilePhysics* m_PhysicsData = nullptr;

            HANDLE m_GraphicsMemoryHandle = nullptr;
            SPageFileGraphic* m_GraphicsData = nullptr;
        };

    }
}
