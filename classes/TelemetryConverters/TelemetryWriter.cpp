#include "TelemetryWriter.h"

#include <filesystem>
#include <iomanip>
#include <iostream>

namespace Telemetry
{
	TelemetryWriter::TelemetryWriter()
		: m_FileName("telemetry_log.csv")
	{

	}

	TelemetryWriter::~TelemetryWriter()
	{

	}

	void TelemetryWriter::StartWriter()
	{
		// Go up from build directory to project root
		std::filesystem::path const logPath = std::filesystem::current_path().parent_path() / m_FileName;
		m_TelemetryLog = std::ofstream(logPath);

		if (m_TelemetryLog.is_open())
		{
			std::cout << "Succesfully opened: " << logPath << std::endl;
		}
		else
		{
			std::cout << "Failed to open: " << logPath << std::endl;
		}

		m_TelemetryLog << "Time,LapPercent,X,Y,Throttle,Brake,Steer\n";
	}

	void TelemetryWriter::StopWriter()
	{
		if (m_TelemetryLog.is_open())
		{
			m_TelemetryLog.close();
		}
	}

	bool TelemetryWriter::TryToWrite(Converter::DataStruct const& dataToWrite)
	{
		if (!m_TelemetryLog.is_open())
		{
			return false;
		}

		float const time{ 0.f };
		float const lapPercentage{ dataToWrite.LapPercentage };
		float const positionX{ dataToWrite.Location.X };
		float const positionY{ dataToWrite.Location.Y };
		float const throttle{ dataToWrite.Throttle };
		float const brake{ dataToWrite.Brake };
		float const steering{ dataToWrite.Steering };

		m_TelemetryLog << std::fixed << std::setprecision(4)
			<< time << "," << lapPercentage << "," << positionX << "," << positionY << ","
			<< throttle << "," << brake << "," << steering << "\n";

		return true;
	}
}