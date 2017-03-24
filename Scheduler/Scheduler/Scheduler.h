#pragma once

#include <queue>
#include <chrono>
#include "MyProcess.h"

typedef std::chrono::high_resolution_clock HRClock;

class Scheduler
{
public:
	Scheduler();
	void swapQueues();
	void sortProcessArray(int arraySize);
	void printProcesses(int arraySize);
	HRClock::time_point getStartTime() {
		return m_startTime;
	}
	void setStartTime(HRClock::time_point startTime) {
		m_startTime = startTime;
	}
	std::queue<MyProcess>& getQueue1(){
		return queue1;
	}
	std::queue<MyProcess>& getQueue2(){
		return queue2;
	}
	MyProcess& getProcess(int index){
		return processArray[index];
	}
	int getArraySize() const{
		return m_arraySize;
	}
	bool getIsActive() const{
		return m_isActive;
	}
	void setIsActive(bool isActive) {
		m_isActive = isActive;
	}

	~Scheduler();

private:
	int const MAXI_PRIORITY = 139;
	int const MINI_PRIORITY = 1;
	HRClock::time_point m_startTime;
	bool m_isActive = false;			//True if queue1 is active
	std::queue<MyProcess> queue1;		//Initially expired queue
	std::queue<MyProcess> queue2;		//Initially active queue
	MyProcess* processArray;
	int m_arraySize;
};

