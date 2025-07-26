#include "TelemetryConverterDummy.h"

namespace Telemetry
{
	namespace Converter
	{
		TelemetryConverterDummy::TelemetryConverterDummy()
			: TelemetryConverter()
		{

		}

		TelemetryConverterDummy::~TelemetryConverterDummy()
		{

		}

		bool TelemetryConverterDummy::ReadTelemetryFromSource()
		{
			m_Output.Throttle = SimulateThrottle();
			m_Output.Brake = SimulateBrake();
			m_Output.Steering = SimulateSteering();

			m_Output.Gear = SimulateGear(m_Output.Throttle);
			
			return true;
		}

		float TelemetryConverterDummy::SimulateThrottle() const
		{
			float simulatedValue{ m_Output.Throttle };
			
			static bool reverse = false;
			if (simulatedValue > 1)
			{
				reverse = true;
			}
			else if (simulatedValue < 0)
			{
				reverse = false;
			}

			simulatedValue += reverse ? -0.01f : 0.01f;
			return simulatedValue;
		}

		float TelemetryConverterDummy::SimulateBrake() const
		{
			float simulatedValue{ m_Output.Brake };

			static bool reverse = false;
			if (simulatedValue > 1)
			{
				reverse = true;
			}
			else if (simulatedValue < 0)
			{
				reverse = false;
			}

			simulatedValue += reverse ? -0.01f : 0.01f;
			return simulatedValue;
		}

		float TelemetryConverterDummy::SimulateSteering() const
		{
			float simulatedValue{ m_Output.Steering };

			static bool reverse = false;
			if (simulatedValue > 1)
			{
				reverse = true;
			}
			else if (simulatedValue < -1)
			{
				reverse = false;
			}

			simulatedValue += reverse ? -0.01f : 0.01f;
			return simulatedValue;
		}

		int TelemetryConverterDummy::SimulateGear(float throttle) const
		{
			int simulatedGear{ m_Output.Gear };
			if (throttle >= 1)
			{
				++simulatedGear;
			}
			else if (throttle <= 0)
			{
				--simulatedGear;
			}
			return simulatedGear;
		}
	}
}