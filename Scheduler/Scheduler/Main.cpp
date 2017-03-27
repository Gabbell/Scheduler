#include <iostream>
#include <fstream>
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
	HRClock::time_point t_start = HRClock::now();
	MyProcess* process = (MyProcess*)(p);

	//Busy waiting
	while (getCurrentTime(t_start, HRClock::now()) - process->getTotalWaitTime() < process->getBurstTime());

	//std::cout << "Previous process terminated" << std::endl;
	process->terminate();

	return 0;
}

DWORD WINAPI overwatchRoutine(LPVOID p) {
	Scheduler scheduler;
	
	scheduler.run(&dummyRoutine);
	

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

	system("pause");

	return 0;
}