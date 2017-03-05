#pragma once
class MyProcess
{
public:
	MyProcess();
	~MyProcess();
private:
	int pid;
	int priority;
	double arrival_time;
	double burst_time;
};

