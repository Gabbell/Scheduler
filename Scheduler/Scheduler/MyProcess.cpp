#include "MyProcess.h"

MyProcess::MyProcess(std::string pid, double arrival_time, double burst_time, int priority)
	: m_pid(pid), m_arrival_time(arrival_time), m_burst_time(burst_time), m_priority(priority)
{
	
}

MyProcess::MyProcess()
	: m_pid(), m_arrival_time(0), m_burst_time(0), m_priority(0)
{
}

MyProcess::~MyProcess()
{
}
