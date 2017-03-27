#include "MyProcess.h"

MyProcess::MyProcess(std::string pid, double arrival_time, double burst_time, int priority)
	: m_pid(pid), m_arrival_time(arrival_time), m_burst_time(burst_time), m_priority(priority), m_timeSlot(0), m_timeSlotCount(0), m_totalWaitTime(0), m_terminated(false), m_new(true)
{
	
}

MyProcess::MyProcess()
	: m_pid(), m_arrival_time(0), m_burst_time(0), m_priority(0), m_timeSlot(0), m_timeSlotCount(0), m_totalWaitTime(0), m_terminated(false), m_new(false)
{
}

MyProcess::~MyProcess()
{
}

bool MyProcess::operator>(const MyProcess& proc) const {
	return (m_priority > proc.getPriority());
}

double getCurrentTime(HRClock::time_point startTime, HRClock::time_point endTime);
