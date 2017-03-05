#pragma once

#include <queue>
#include "MyProcess.h"

#define MAX_PRIORITY 139
#define MIN_PRIORITY 0

class Scheduler
{
public:
	Scheduler();
	~Scheduler();
private:
	std::queue<MyProcess> queue1;
	std::queue<MyProcess> queue2;

};

