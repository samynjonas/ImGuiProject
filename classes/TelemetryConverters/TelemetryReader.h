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

		// returns the player location
		inline Math::Vec2 GetActualLocation() const { return m_CurrentLocation; }
		inline Math::Vec2 GetRelativeLocation() const { return m_CurrentLocation - m_OriginLocation; }

		// returns the player lap percentage
		inline float GetLapPercentage() const { return m_CurrentLapPercentage; }

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

		Math::Vec2 m_OriginLocation;
		Math::Vec2 m_CurrentLocation;

		float m_LastLapPercentage;
		float m_CurrentLapPercentage;

		std::unique_ptr<Converter::TelemetryConverter> m_TelemetryConverter;
		std::unique_ptr<TelemetryWriter> m_TelemetryWriter;
	};
}