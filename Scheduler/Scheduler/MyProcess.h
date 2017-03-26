#pragma once
#include <string>
#include <Windows.h>
#include <chrono>

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

	HRClock::time_point m_waitTimeCounter;
	double m_totalWaitTime;

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

	void setWaitTimeCounter(HRClock::time_point waitTimeCounter) {
		m_waitTimeCounter = waitTimeCounter;
	}

	HRClock::time_point getWaitTimeCounter() const {
		return m_waitTimeCounter;
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

	void incrementTotalWaitTime();
};

