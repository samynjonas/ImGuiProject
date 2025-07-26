#pragma once
#include <iostream>

namespace Telemetry
{
	namespace Converter
	{
		class TelemetryConverter;
	}

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

		inline int GetGear() const { return m_CurrentGear; }

	// Public Functions
	public:
		void Update(bool& validTelemetry);

	// Private Functions
	private:

	// Member variables
	private:
		float m_CurrentThrottle;
		float m_CurrentBrake;
		float m_CurrentSteering;
		int m_CurrentGear;

		std::unique_ptr<Converter::TelemetryConverter> m_TelemetryConverter;
	};
}