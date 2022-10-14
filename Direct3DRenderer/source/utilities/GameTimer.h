#pragma once

namespace wl
{
	class GameTimer
	{
	public:
		GameTimer();
		// Returns the total time the app has been running, not counting paused time.
		float TotalTime() const;
		// Returns time since the last frame.
		float DeltaTime() const;
		// Starts the timer at 0.
		void Reset();
		// Starts the timer after it has been paused.
		void Start();
		// Pauses the timer.
		void Stop();
		// Marks a new frame.
		void Tick();
	private:
		double m_secondsPerCount;	// Seconds per count of QueryPerformanceFrequency
		double m_deltaTime;			// Time since last frame.
		__int64 m_startTime;		// Time at which the timer started.
		__int64 m_totalPausedTime;	// Total time the app has been paused.
		__int64 m_pauseTime;		// The time at which the game was paused.
		__int64 m_previousTime;		// Time at last tick.
		__int64 m_currentTime;		// The current time.
		bool m_isPaused;			// If the timer is paused.
	};
}