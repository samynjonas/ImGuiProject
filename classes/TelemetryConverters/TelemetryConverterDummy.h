#pragma once
#include "TelemetryConverter.h"

namespace Telemetry
{
	namespace Converter
	{
		class TelemetryConverterDummy : public TelemetryConverter
		{
		public:
			TelemetryConverterDummy();
			~TelemetryConverterDummy();

			bool ReadTelemetryFromSource() override;

		private:
			float SimulateThrottle() const;
			float SimulateBrake() const;
			float SimulateSteering() const;
			int SimulateGear(float throttle) const;

			float SimulateSpeedKmh(float throttle, float brake) const;

		};
	}
}