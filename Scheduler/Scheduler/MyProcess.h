#pragma once
#include <string>
#include <Windows.h>
class MyProcess
{
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
	void setHandle(HANDLE t_handle) {
		m_handle = t_handle;
	}
	HANDLE getHandle() {
		return m_handle;
	}
	~MyProcess();
private:
	std::string m_pid;
	int m_priority;
	double m_arrival_time;
	double m_burst_time;
	HANDLE m_handle;
};

