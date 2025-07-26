#include "TelemetryReader.h"

#include "TelemetryConverters/TelemetryConverterDummy.h"
#include "TelemetryConverters/TelemetryConverterACC.h"

namespace Telemetry
{
	TelemetryReader::TelemetryReader()
		: m_TelemetryConverter()
		, m_CurrentThrottle(0.f)
		, m_CurrentBrake(0.f)
		, m_CurrentSteering(0.f)
	{
		m_TelemetryConverter = std::make_unique<Converter::TelemetryConverterDummy>();
		//m_TelemetryConverter = std::make_unique<Converter::TelemetryConverterACC>();
	}

	TelemetryReader::~TelemetryReader()
	{

	}

	void TelemetryReader::Update(bool& validTelemetry)
	{
		validTelemetry = m_TelemetryConverter->ReadTelemetryFromSource();
		
		Converter::DataStruct output{};
		if (validTelemetry)
		{
			output = m_TelemetryConverter->GetOutput();
		}

		m_CurrentThrottle = output.Throttle;
		m_CurrentBrake = output.Brake;
		m_CurrentSteering = output.Steering;
		m_CurrentGear = output.Gear;
	}
}