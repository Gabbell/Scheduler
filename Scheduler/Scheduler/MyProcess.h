#pragma once
#include <string>
class MyProcess
{
public:
	MyProcess();
	MyProcess(std::string pid, double arrival_time, double burst_time, int priority);
	std::string getPid() const;
	double getArrivalTime() const;
	double getBurstTime() const;
	int getPriority() const;
	~MyProcess();
private:
	std::string m_pid;
	int m_priority;
	double m_arrival_time;
	double m_burst_time;
};

