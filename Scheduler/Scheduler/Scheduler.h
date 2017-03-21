#pragma once

#include <queue>
#include <chrono>
#include "MyProcess.h"

class Scheduler
{
public:
	Scheduler();
	void swapQueues();
	void sortProcessArray(int arraySize);
	double getCurrentTime();

	~Scheduler();
private:
	int const MAX_PRIORITY = 139;
	int const MIN_PRIORITY = 1;

	std::chrono::high_resolution_clock::time_point startTime;
	std::queue<MyProcess> queue1; //Initially active queue
	std::queue<MyProcess> queue2; //Initially expired queue
	MyProcess* processArray;
};

