#include "TelemetryReader.h"

#include "TelemetryWriter.h"

#include "TelemetryConverters/TelemetryConverterDummy.h"
#include "TelemetryConverters/TelemetryConverterACC.h"

namespace Telemetry
{
	TelemetryReader::TelemetryReader()
		: m_TelemetryConverter()
		, m_CurrentThrottle(0.f)
		, m_CurrentBrake(0.f)
		, m_CurrentSteering(0.f)
		, m_CurrentLocation()
		, m_OriginLocation()
	{
		m_TelemetryWriter = std::make_unique<TelemetryWriter>();
		m_TelemetryWriter->StartWriter();

		//m_TelemetryConverter = std::make_unique<Converter::TelemetryConverterDummy>();
		m_TelemetryConverter = std::make_unique<Converter::TelemetryConverterACC>();
	}

	TelemetryReader::~TelemetryReader()
	{
		m_TelemetryWriter->StopWriter();
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
		
		m_CurrentLocation = output.Location;
		m_OriginLocation = output.Origin;

		m_LastLapPercentage = m_CurrentLapPercentage;
		m_CurrentLapPercentage = output.LapPercentage;
		
		m_TelemetryWriter->TryToWrite(output);
	}

	void TelemetryReader::SetOriginFromCurrent()
	{
		m_OriginLocation = m_CurrentLocation;
	}
}