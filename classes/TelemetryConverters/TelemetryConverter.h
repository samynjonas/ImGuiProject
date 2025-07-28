#pragma once
#include "Math/Vector.h"

namespace Telemetry
{
	namespace Converter
	{
		struct DataStruct
		{
			DataStruct() {}

			float Throttle{ 0.f };
			float Brake{ 0.f };
			float Steering{ 0.f };
			int Gear{ 0 };

			float LapPercentage{ 0.f };

			Math::Vec2 Location{};
			Math::Vec2 Origin{};
		};

		class TelemetryConverter
		{
		public:
			TelemetryConverter() : m_Output() {}
			virtual ~TelemetryConverter() {};

			virtual bool ReadTelemetryFromSource() = 0;
			inline DataStruct GetOutput() const { return m_Output; }

		protected:
			DataStruct m_Output;
		};
	}
}