#include "Timer.h"

Timer::Timer(double duration) : m_count(0), m_duration(duration), m_started(true), m_finished(false)
{
	m_lastTime = std::chrono::high_resolution_clock::now();
}


Timer::~Timer()
{
}

double getCurrentTime1(std::chrono::high_resolution_clock::time_point startTime, std::chrono::high_resolution_clock::time_point endTime) {

	using namespace std::chrono;

	//Calculating time span between constructor starTime and now
	duration<double> time_span = duration_cast<duration<double>>(endTime - startTime);

	//Return in ms
	return time_span.count() * 1000;
}

void Timer::restart() {
	m_count = 0;
	m_started = true;
	m_lastTime = std::chrono::high_resolution_clock::now();
}

void Timer::update() {
	
	m_count += getCurrentTime1(m_lastTime, std::chrono::high_resolution_clock::now());
	
	if (m_count >= m_duration) {
		m_started = false;
		m_finished = true;
	}

	m_lastTime = std::chrono::high_resolution_clock::now();
}

void Timer::pause() {
	m_timePaused = std::chrono::high_resolution_clock::now();
}

void Timer::resume() {
	m_lastTime = std::chrono::high_resolution_clock::now() + m_timePaused;
}