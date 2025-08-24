#pragma once
#include <string>

namespace Helper
{
	struct LapTime
	{
		LapTime()
			: MilliSeconds(0)
		{}

		LapTime(int milliSeconds)
			: MilliSeconds(milliSeconds)
		{
			// Some Games return the max int when none has been set yet
			if (milliSeconds >= INT32_MAX)
			{
				MilliSeconds = 0;
			}
		}

		int MilliSeconds;
	
		float GetSeconds() const
		{
			return MilliSeconds / 1000.f;
		}
	};
}