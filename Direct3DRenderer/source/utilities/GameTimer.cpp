#include "GameTimer.h"
#include "windows/win.h"

namespace wl
{
	GameTimer::GameTimer()
		:m_secondsPerCount(0.0), m_deltaTime(-1.0), m_startTime(0),
		m_totalPausedTime(0), m_previousTime(0), m_currentTime(0), m_pauseTime(0), m_isPaused(false)
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER *)&countsPerSec);
		m_secondsPerCount = 1.0 / (double)countsPerSec;
	}

	float GameTimer::TotalTime() const
	{
		// If we are stopped, do not count the time that has passed
		// since we stopped. Moreover, if we previously already had
		// a pause, the distance m_pauseTime - m_startTime includes paused
		// time,which we do not want to count. To correct this, we can
		// subtract the paused time from mStopTime:
		//
		// previous paused time
		// |<----------->|
		// ---*------------*-------------*-------*-----------*------> time
		// mBaseTime mStopTime mCurrTime
		if (m_isPaused)
		{
			return (float)(((m_pauseTime - m_totalPausedTime) -
				m_startTime) * m_secondsPerCount);
		}
		// The distance m_currentTime - m_startTime includes paused time,
		// which we do not want to count. To correct this, we can subtract
		// the paused time from m_currentTime:
		//
		// (m_currentTime - m_totalPausedTime) - m_startTime
		//
		// |<--paused time-->|
		// ----*---------------*-----------------*------------*------> time
		// m_startTime m_pauseTime startTime mCurrTime
		else
		{
			return (float)(((m_currentTime - m_totalPausedTime) -
				m_startTime) * m_secondsPerCount);
		}
	}

	float GameTimer::DeltaTime() const
	{
		return static_cast<float>(m_deltaTime);
	}

	void GameTimer::Reset()
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER *)&currTime);
		m_startTime = currTime;
		m_previousTime = currTime;
		m_pauseTime = 0;
		m_isPaused = false;
	}

	void GameTimer::Start()
	{
		if (!m_isPaused) return;

		__int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);

		// Accumulate the time elapsed between stop and start pairs.
		//
		//                     |<-------d------->|
		// ----*---------------*-----------------*------------> time
		//  mBaseTime       mStopTime        currentTime     

		m_totalPausedTime += (currentTime - m_pauseTime);

		m_previousTime = currentTime;
		m_pauseTime = 0;
		m_isPaused = false;
	}

	void GameTimer::Stop()
	{
		if (m_isPaused) return;
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER *)&currTime);

		m_pauseTime = currTime;
		m_isPaused = true;
	}

	void GameTimer::Tick()
	{
		if (m_isPaused)
		{
			m_deltaTime = 0.0;
			return;
		}
		// Get the time this frame.
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER *)&currTime);
		m_currentTime = currTime;
		// Time difference between this frame and the previous.
		m_deltaTime = (m_currentTime - m_previousTime) * m_secondsPerCount;
		// Prepare for next frame.
		m_previousTime = m_currentTime;
		// Force nonnegative. The DXSDK's CDXUTTimer mentions that if the
		// processor goes into a power save mode or we get shuffled to another
		// processor, then mDeltaTime can be negative.
		if (m_deltaTime < 0.0)
		{
			m_deltaTime = 0.0;
		}
	}
}