#pragma once

#include <queue>
#include <vector>
#include <chrono>
#include "MyProcess.h"

typedef std::chrono::high_resolution_clock HRClock;

class Scheduler
{
private:
	static const int SCHEDULER_MAX_PRIORITY = 139;
	static const int SCHEDULER_MIN_PRIORITY = 1;
	HRClock::time_point m_startTime;

	HRClock::time_point m_timeSlotCounter;

	std::priority_queue<MyProcess*, std::vector<MyProcess*>, bool(*)(MyProcess*,MyProcess*)> queue1;		// Initially expired queue
	std::priority_queue<MyProcess*, std::vector<MyProcess*>, bool(*)(MyProcess*, MyProcess*)> queue2;		// Initially active queue
	bool m_queuesSwapped = true;		// True if queue1 is active
	
	MyProcess* processArray;
	int m_arraySize;

	MyProcess* m_currentProcess;
	bool m_servingProcess;

public:
	Scheduler();
	void run(DWORD(WINAPI *dummyRoutine)(LPVOID));
	void sortProcessArray(int arraySize);
	void printProcesses(int arraySize);
	
	HRClock::time_point getStartTime() {
		return m_startTime;
	}
	
	void setStartTime(HRClock::time_point startTime) {
		m_startTime = startTime;
	}

	std::priority_queue<MyProcess*, std::vector<MyProcess*>, bool(*)(MyProcess*, MyProcess*)>& getActiveQueue() {
		return (m_queuesSwapped) ? queue1 : queue2;
	}

	std::priority_queue<MyProcess*, std::vector<MyProcess*>, bool(*)(MyProcess*, MyProcess*)>& getExpiredQueue() {
		return (m_queuesSwapped) ? queue2 : queue1;
	}

	MyProcess& getProcess(int index){
		return processArray[index];
	}
	int getArraySize() const{
		return m_arraySize;
	}
	bool getIsActive() const{
		return m_queuesSwapped;
	}
	void setIsActive(bool isActive) {
		m_queuesSwapped = isActive;
	}

	void swapQueues() {
		//Swapping flags
		m_queuesSwapped = !m_queuesSwapped;
	}

	~Scheduler();
};

