#include <iostream>
#include <string>
#include <Windows.h>
#include "Scheduler.h"

using namespace std;

double getCurrentTime(std::chrono::high_resolution_clock::time_point startTime, std::chrono::high_resolution_clock::time_point endTime) {

	using namespace std::chrono;

	//Calculating time span between constructor starTime and now
	duration<double> time_span = duration_cast<duration<double>>(endTime - startTime);

	//Return in ms
	return time_span.count() * 1000;
}

DWORD WINAPI overwatchRoutine(LPVOID p) {
	Scheduler scheduler;

	//Casting parameter to right type
	scheduler.startTime = std::chrono::high_resolution_clock::now();

	while (getCurrentTime(scheduler.startTime, std::chrono::high_resolution_clock::now()) < 3000);

	std::cout << "It has been 3 seconds" << std::endl;

	return 0;
}

int main() {

	//Create Overwatch thread
	void(*routine) = &overwatchRoutine;

	HANDLE t_overwatch = CreateThread(
		NULL,										//Default security attributes
		0,											//Default executable stack size
		(LPTHREAD_START_ROUTINE)routine,			//Pointer to function
		NULL,										//Don't need it
		0,											//Will start as soon as created
		NULL);										//Do not need the thread ID

	WaitForSingleObject(t_overwatch, INFINITE);

	return 0;
}