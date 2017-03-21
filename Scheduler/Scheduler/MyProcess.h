#pragma once
#include <string>
class MyProcess
{
public:
	MyProcess();
	MyProcess(std::string pid, int priority, double arrival_time, double burst_time);
	double getArrivalTime() const;
	~MyProcess();
private:
	std::string m_pid;
	int m_priority;
	double m_arrival_time;
	double m_burst_time;
};

