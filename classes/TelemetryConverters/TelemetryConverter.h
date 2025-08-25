#pragma once
#include "Math/Vector.h"
#include <vector>

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
			float SpeedKmh{ 0.f };

			float LapPercentage{ 0.f };
			int CompletedLaps{ 0 };
			float LastSectorTimeSeconds{ 0.f };
			float LastTimeSeconds{ 0.f };
			float BestTimeSeconds{ 0.f };
			float CurrentTimeSeconds{ 0.f };
		
			int	TyresOutOfTrack{ 0 };

			int ActiveCars{ 0 };
			int PlayerCarIndex{ 0 };
			std::vector<Math::Vec2> CarPositions;
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