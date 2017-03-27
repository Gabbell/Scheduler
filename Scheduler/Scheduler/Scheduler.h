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
	
	HRClock::time_point m_startTime;		// Time point used to keep count of the total amount of time the scheduler has been running
	HRClock::time_point m_timeSlotCounter;	// Time point used to keep count of the amount of time a process has been running

	std::priority_queue<MyProcess*, std::vector<MyProcess*>, bool(*)(MyProcess*,MyProcess*)> queue1;		// Initially expired queue
	std::priority_queue<MyProcess*, std::vector<MyProcess*>, bool(*)(MyProcess*, MyProcess*)> queue2;		// Initially active queue
	bool m_queuesSwapped = true;		// True if queue1 is active
	

	MyProcess* processArray; // Array containing all the processes, sorted by arrival time
	int m_arraySize;

	MyProcess* m_currentProcess;	// Current process being executed
	bool m_servingProcess;			// True if a process is currently being executed

public:
	Scheduler();
	~Scheduler();
	void run(DWORD(WINAPI *dummyRoutine)(LPVOID));
	void sortProcessArray(int arraySize);
	void printProcesses(int arraySize);
	
	void swapQueues() {
		//Swapping flags
		m_queuesSwapped = !m_queuesSwapped;
	}

	// Getters
	MyProcess& getProcess(int index){
		return processArray[index];
	}
	int getArraySize() const{
		return m_arraySize;
	}
	bool getIsActive() const{
		return m_queuesSwapped;
	}

	HRClock::time_point getStartTime() {
		return m_startTime;
	}


	std::priority_queue<MyProcess*, std::vector<MyProcess*>, bool(*)(MyProcess*, MyProcess*)>& getActiveQueue() {
		return (m_queuesSwapped) ? queue1 : queue2;
	}

	std::priority_queue<MyProcess*, std::vector<MyProcess*>, bool(*)(MyProcess*, MyProcess*)>& getExpiredQueue() {
		return (m_queuesSwapped) ? queue2 : queue1;
	}

	// Setters
	void setStartTime(HRClock::time_point startTime) {
		m_startTime = startTime;
	}
};

