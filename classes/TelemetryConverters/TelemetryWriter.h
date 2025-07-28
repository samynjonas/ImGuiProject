#pragma once
#include <string>
#include <fstream>

#include "TelemetryConverter.h"

namespace Telemetry
{
	class TelemetryWriter
	{
	public:
		TelemetryWriter();
		~TelemetryWriter();

	public:
		void StartWriter();
		void StopWriter();

		bool TryToWrite(Converter::DataStruct const& dataToWrite);

	private:
		std::string m_FileName;
		std::ofstream m_TelemetryLog;
		
	};
}