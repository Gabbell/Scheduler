#pragma once
#include <string>
#include <Windows.h>
#include <chrono>
#include <iostream>

typedef std::chrono::high_resolution_clock HRClock;

class MyProcess
{
private:
	std::string m_pid;
	double m_timeSlot;
	int m_timeSlotCount;
	int m_priority;
	double m_arrival_time;
	double m_burst_time;
	HANDLE m_handle;

	HRClock::time_point m_paused_at;
	HRClock::time_point m_started_at;
	
	double m_totalWaitTime;
	double m_totalRunTime;


	bool m_terminated;
	bool m_new;
public:
	MyProcess();
	MyProcess(std::string pid, double arrival_time, double burst_time, int priority);
	
	std::string getPid() const {
		return m_pid;
	}
	
	double getArrivalTime() const {
		return m_arrival_time;
	}
	
	double getBurstTime() const {
		return m_burst_time;
	}
	
	int getPriority() const {
		return m_priority;
	}
	
	void setPriority(int priority) {
		m_priority = priority;
	}
	
	void setHandle(HANDLE t_handle) {
		m_handle = t_handle;
	}

	void setTimeSlot(double timeSlot) {
		m_timeSlot = timeSlot;
	}

	double getTimeSlot() const {
		return m_timeSlot;
	}
	
	HANDLE getHandle() const {
		return m_handle;
	}
	
	double getTotalWaitTime() const {
		return m_totalWaitTime;
	}

	void setPausedAt(HRClock::time_point pausedAt) {
		m_paused_at = pausedAt;
	}
	void setStartedAt(HRClock::time_point startedAt) {
		m_started_at = startedAt;
	}

	void incrementTotalWaitTime() {
		using namespace std::chrono;

		m_totalWaitTime += duration_cast<duration<double>>(m_started_at - m_paused_at).count() * 1000;
	}

	HRClock::time_point getPausedAt() const {
		return m_paused_at;
	}
	HRClock::time_point getStartedAt() const {
		return m_started_at;
	}

	double getTotalRunTime() const {
		return m_totalRunTime;
	}
	~MyProcess();

	bool operator>(const MyProcess& proc) const;

	bool isNew() const {
		return m_new;
	}

	void setNew(bool isNew) {
		m_new = isNew;
	}

	bool isTerminated() const {
		return m_terminated;
	}
	void terminate() {
		m_terminated = true;
	}

	int getTimeSlotCount() const {
		return m_timeSlotCount;
	}

	void incrementTimeSlotCount() {
		m_timeSlotCount++;
	}
};

