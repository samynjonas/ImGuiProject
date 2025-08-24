#pragma once
#include <iostream>
#include <vector>

#include "Math/Vector.h"

namespace Telemetry
{
	namespace Converter
	{
		class TelemetryConverter;
	}

	class TelemetryWriter;
	class TelemetryReader
	{
	public:
		TelemetryReader();
		~TelemetryReader();

	// Getter functions
	public:
		// returns the throttle - this will be in a 0-1 range
		inline float GetThrottle() const { return m_CurrentThrottle; }

		// returns the brake - this will be in a 0-1 range
		inline float GetBrake() const { return m_CurrentBrake; }

		// returns the steering - this will be in a -1 - 1 range
		inline float GetSteering() const { return m_CurrentSteering; }

		// returns the current gear
		inline int GetGear() const { return m_CurrentGear; }

		// returns the current speed in kmh
		inline int GetSpeedKmh() const { return m_CurrentSpeedKmh; }

		// returns the player lap percentage
		inline float GetLapPercentage() const { return m_CurrentLapPercentage; }

		// returns the current completed laps
		inline int GetCompletedLaps() const { return m_CurrentCompletedLaps; }

		// returns the last sector time in seconds
		inline float GetLastSectorTime() const { return m_LastSectorTime; }

		// returns the best lap time in seconds
		inline float GetBestLapTime() const { return m_LapBestTime; }

		// returns the last lap time in seconds
		inline float GetLastLapTime() const { return m_LastLapTime; }

		// returns the current lap time in seconds
		inline float GetCurrentLapTime() const { return m_CurrentTime; }

	// Public Functions
	public:
		void Update(bool& validTelemetry);

	private:
		void StartNewLap();
		
	// Member variables
	private:
		float m_CurrentThrottle;
		float m_CurrentBrake;
		float m_CurrentSteering;

		int m_CurrentGear;
		float m_CurrentSpeedKmh;

		int m_CurrentCompletedLaps;
		float m_LastSectorTime;
		float m_LastLapTime;
		float m_LapBestTime;
		float m_CurrentTime;

		float m_LastLapPercentage;
		float m_CurrentLapPercentage;

		std::unique_ptr<Converter::TelemetryConverter> m_TelemetryConverter;
		std::unique_ptr<TelemetryWriter> m_TelemetryWriter;
	};
}