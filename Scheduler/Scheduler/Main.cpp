#include <iostream>
#include <string>
#include <Windows.h>
#include "Scheduler.h"

using namespace std;

double getCurrentTime(HRClock::time_point startTime, HRClock::time_point endTime) {

	using namespace std::chrono;

	//Calculating time span between constructor starTime and now
	duration<double> time_span = duration_cast<duration<double>>(endTime - startTime);

	//Return in ms
	return time_span.count() * 1000;
}

DWORD WINAPI dummyRoutine(LPVOID p) {
	double* timeSlot = (double*)(p);

	delete timeSlot;
	return 0;
}

DWORD WINAPI overwatchRoutine(LPVOID p) {
	Scheduler scheduler;

	std::cout << "----------STARTING SEQUENCE----------" << std::endl;

	//Casting parameter to right type
	scheduler.setStartTime(HRClock::now());

	DWORD(WINAPI *dumbRoutine)(LPVOID) = &dummyRoutine;
	int procIndex = 0;

	while (!scheduler.getQueue1().empty() || !scheduler.getQueue1().empty() || procIndex < scheduler.getArraySize()) {

		//If process has arrived, add it to the queue and create initially suspended thread
		if (getCurrentTime(scheduler.getStartTime(), HRClock::now()) >= scheduler.getProcess(procIndex).getArrivalTime() 
			&& procIndex < scheduler.getArraySize()) {
			std::cout << "Process " << scheduler.getProcess(procIndex).getPid() << " arrived" << std::endl;

			//Calculating time slot
			int priority = scheduler.getProcess(procIndex).getPriority();
			double* timeSlot = nullptr;

			if (priority < 100) {
				timeSlot = new double((140 - priority) * 20);
			}
			else {
				timeSlot = new double((140 - priority) * 5);
			}

			HANDLE t_dummy = CreateThread(
				NULL,					
				0,		
				(LPTHREAD_START_ROUTINE)dumbRoutine,
				timeSlot,	
				0,										
				NULL);
			scheduler.getProcess(procIndex).setHandle(t_dummy);
			
			//Pushing new process into the expired queue
			if (scheduler.getIsActive()) {
				scheduler.getQueue2().push(scheduler.getProcess(procIndex));
			}
			else {
				scheduler.getQueue1().push(scheduler.getProcess(procIndex));
			}

			procIndex++;
		}
		
		//Swapping queues
		if (scheduler.getIsActive()) {				//This means that queue1 is active
			if (scheduler.getQueue1().empty()) {	 //Active queue is empty, switching queues
				scheduler.swapQueues();
			}
		}
		else {										//This means that queue2 is active
			if (scheduler.getQueue2().empty()) {	//Active queue is empty switching queues
				scheduler.swapQueues();
			}
		}
	}

	system("pause");

	return 0;
}

int main() {

	//Create Overwatch thread
	DWORD(WINAPI *ow_routine)(LPVOID) = &overwatchRoutine;

	HANDLE t_overwatch = CreateThread(
		NULL,										//Default security attributes
		0,											//Default executable stack size
		(LPTHREAD_START_ROUTINE)ow_routine,			//Pointer to function
		NULL,										//Don't need it
		0,											//Will start as soon as created
		NULL);										//Do not need the thread ID

	WaitForSingleObject(t_overwatch, INFINITE);

	return 0;
}