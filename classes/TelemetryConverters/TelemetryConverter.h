#pragma once

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