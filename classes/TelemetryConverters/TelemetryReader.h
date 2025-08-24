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

		// returns the player location
		inline Math::Vec2 GetActualLocation() const { return m_CurrentLocation; }
		inline Math::Vec2 GetRelativeLocation() const { return m_CurrentLocation - m_OriginLocation; }

		// returns the player lap percentage
		inline float GetLapPercentage() const { return m_CurrentLapPercentage; }

		// returns the current completed laps
		inline int GetCompletedLaps() const { return m_CurrentCompletedLaps; }

		// returns the last sector time
		inline int GetLastSectorTime() const { return m_LastSectorTime; }

		// returns the current best time
		inline int GetBestTime() const { return m_CurrentBestTime; }

		// returns the current lap time
		inline int GetCurrentLapTime() const { return m_CurrentTime; }

	// Public Functions
	public:
		void Update(bool& validTelemetry);

		void SetOriginFromCurrent();

	// Private Functions
	private:
		void RecordLap();

	// Member variables
	private:
		float m_CurrentThrottle;
		float m_CurrentBrake;
		float m_CurrentSteering;

		int m_CurrentGear;
		float m_CurrentSpeedKmh;

		Math::Vec2 m_OriginLocation;
		Math::Vec2 m_CurrentLocation;

		int m_CurrentCompletedLaps;
		int m_LastSectorTime;
		int m_CurrentBestTime;
		int m_CurrentTime;

		float m_LastLapPercentage;
		float m_CurrentLapPercentage;

		std::unique_ptr<Converter::TelemetryConverter> m_TelemetryConverter;
		std::unique_ptr<TelemetryWriter> m_TelemetryWriter;
	};
}