#include "MyProcess.h"

MyProcess::MyProcess(std::string pid, double arrival_time, double burst_time, int priority)
	: m_pid(pid), m_arrival_time(arrival_time), m_burst_time(burst_time), m_priority(priority)
{
	
}

MyProcess::MyProcess()
	: m_pid(), m_arrival_time(0), m_burst_time(0), m_priority(0)
{
}

std::string MyProcess::getPid() const {
	return m_pid;
}

double MyProcess::getArrivalTime() const {
	return m_arrival_time;
}

double MyProcess::getBurstTime() const {
	return m_burst_time;
}

int MyProcess::getPriority() const {
	return m_priority;
}

MyProcess::~MyProcess()
{
}
