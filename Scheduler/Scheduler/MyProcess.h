#pragma once
#include <string>
class MyProcess
{
public:
	MyProcess(std::string pid, int priority, double arrival_time, double burst_time);
	~MyProcess();
private:
	std::string pid;
	int priority;
	double arrival_time;
	double burst_time;
};

