#pragma once

#include <string>
#include <Windows.h>
#include <chrono>
#include <iostream>

typedef std::chrono::high_resolution_clock HRClock;

class MyProcess
{
private:
	std::string m_pid;					// Unique identifier for the process	
	double m_timeSlot;					// Currently allocated time slot for this process
	int m_timeSlotCount;				// Time slots that have been executed by the process
	int m_priority;						// Priority of the process
	double m_arrival_time;				// Arrival time of the process
	double m_burst_time;				// Execution time of the process
	HANDLE m_handle;					// Handle to thread provided by Windows

	HRClock::time_point m_paused_at;	// Time when process was last paused
	HRClock::time_point m_started_at;	// Time when process was last started
	
	double m_totalWaitTime;				// Total time the process has waited


	bool m_terminated;					// True if the process has terminated
	bool m_new;							// True if the process is brand new
public:
	MyProcess();
	MyProcess(std::string pid, double arrival_time, double burst_time, int priority);
	~MyProcess();

	void terminate() {
		m_terminated = true;
	}

	void incrementTimeSlotCount() {
		m_timeSlotCount++;
	}


	// Operators
	bool operator>(const MyProcess& proc) const;

	// Getters
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

	double getTimeSlot() const {
		return m_timeSlot;
	}
	
	HANDLE getHandle() const {
		return m_handle;
	}
	
	double getTotalWaitTime() const {
		return m_totalWaitTime;
	}

	HRClock::time_point getPausedAt() const {
		return m_paused_at;
	}
	HRClock::time_point getStartedAt() const {
		return m_started_at;
	}

	bool isNew() const {
		return m_new;
	}

	bool isTerminated() const {
		return m_terminated;
	}

	int getTimeSlotCount() const {
		return m_timeSlotCount;
	}

	// Setters
	void setPriority(int priority) {
		m_priority = priority;
	}

	void setHandle(HANDLE t_handle) {
		m_handle = t_handle;
	}

	void setTimeSlot(double timeSlot) {
		m_timeSlot = timeSlot;
	}

	void setPausedAt(HRClock::time_point pausedAt) {
		m_paused_at = pausedAt;
	}
	void setStartedAt(HRClock::time_point startedAt) {
		using namespace std::chrono;
		m_started_at = startedAt;
		
		if (!isNew())
			m_totalWaitTime += duration_cast<duration<double>>(m_started_at - m_paused_at).count() * 1000;
	}
	
	void setNew(bool isNew) {
		m_new = isNew;
	}
};

