#include "MyProcess.h"



MyProcess::MyProcess(std::string pid, int priority, double arrival_time, double burst_time)
{
	this->pid = pid;
	this->priority = priority;
	this->arrival_time = arrival_time;
	this->burst_time = burst_time;
}


MyProcess::~MyProcess()
{
}
