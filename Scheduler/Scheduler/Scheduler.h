#pragma once

#include <queue>
#include <iostream>
#include <string>
#include <chrono>
#include "MyProcess.h"

#define MAX_PRIORITY 139
#define MIN_PRIORITY 0

class Scheduler
{
public:
	Scheduler();
	void swapQueues();
	double getCurrentTime();

	~Scheduler();
private:
	std::chrono::high_resolution_clock::time_point startTime;
	std::queue<MyProcess> queue1; //Initially active queue
	std::queue<MyProcess> queue2; //Initially expired queue
};

