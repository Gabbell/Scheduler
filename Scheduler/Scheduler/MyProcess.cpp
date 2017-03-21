#include "MyProcess.h"

MyProcess::MyProcess(std::string pid, int priority, double arrival_time, double burst_time)
	: m_pid(pid), m_priority(priority), m_arrival_time(arrival_time), m_burst_time(burst_time)
{
	
}

MyProcess::MyProcess()
	: m_pid(), m_priority(0), m_arrival_time(0), m_burst_time(0)
{
}

double MyProcess::getArrivalTime() const {
	return m_arrival_time;
}

MyProcess::~MyProcess()
{
}
