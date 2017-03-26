#pragma once

#include <chrono>

class Timer
{
private:
	
	double m_count;
	double m_duration;

	bool m_started;
	bool m_finished;

	std::chrono::high_resolution_clock::time_point m_lastTime;
	std::chrono::high_resolution_clock::time_point m_timePaused;

public:
	Timer(double durection);
	virtual ~Timer();

	void restart();
	void update();
	void pause();
	void resume();

	bool isFinished() {
		return m_finished;
	}
};

