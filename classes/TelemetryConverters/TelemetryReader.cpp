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
		, m_CurrentSpeedKmh(0.f)
		, m_CurrentGear(0)
		, m_CurrentCompletedLaps(0)
		, m_LastSectorTime(0.f)
		, m_LapBestTime(0.f)
		, m_LastLapTime(0.f)
		, m_CurrentTime(0.f)
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

		int const lastCompletedLaps = m_CurrentCompletedLaps;
		m_CurrentCompletedLaps = output.CompletedLaps;

		bool const startedNewLap = { m_CurrentCompletedLaps > lastCompletedLaps };
		if (startedNewLap)
		{
			StartNewLap();
		}

		m_CurrentThrottle = output.Throttle;
		m_CurrentBrake = output.Brake;
		m_CurrentSteering = output.Steering;

		m_CurrentGear = output.Gear;
		m_CurrentSpeedKmh = output.SpeedKmh;

		m_LastLapPercentage = m_CurrentLapPercentage;
		m_CurrentLapPercentage = output.LapPercentage;
		
		m_LastSectorTime = output.LastSectorTimeSeconds;
		
		m_LapBestTime = output.BestTimeSeconds;
		m_LastLapTime = output.LastTimeSeconds;
		m_CurrentTime = output.CurrentTimeSeconds;
		
		m_TelemetryWriter->TryToWrite(output);
	}

	void TelemetryReader::StartNewLap()
	{
		// Reset Per Lap Variables
	}
}