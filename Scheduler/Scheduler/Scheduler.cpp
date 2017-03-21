#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <string>

Scheduler::Scheduler()
{
	
	std::cout << "Please enter the name of the input file: " << std::endl;
	std::string fileName;
	std::cin >> fileName;
	
	std::ifstream ifs;
	ifs.open(fileName);

	//Waiting until file is found an open. Otherwise, prompt user again
	while(!ifs){
		std::cout << "Could not find file. Try again" << std::endl;
		std::cin >> fileName;
		ifs.open(fileName);
	}
	
	int arraySize;
	ifs >> arraySize;

	processArray = new MyProcess[arraySize];

	std::cout << "----------STARTING SEQUENCE----------" << std::endl;
	for (int i = 0; i < arraySize; i++) {
		std::string pid;
		int priority;
		int arrival_time;
		int burst_time;

		ifs >> pid;
		ifs >> arrival_time;
		ifs >> burst_time;
		ifs >> priority;

		processArray[i] = MyProcess(pid, priority, arrival_time, burst_time);
	}

	sortProcessArray(arraySize);
	
	ifs.close();

	startTime = std::chrono::high_resolution_clock::now();
}

void Scheduler::sortProcessArray(int arraySize) {
	int init = 0;
	MyProcess temp;

	for (int i = 0; i < arraySize; i++) {
		for (int j = 0; j < arraySize; j++) {
			if (processArray[j].getArrivalTime() > processArray[init].getArrivalTime()) {
				init = j;
			}
		}
		temp = processArray[init];
		processArray[init] = processArray[i];
		processArray[i] = temp;
	}
	return;
}

double Scheduler::getCurrentTime() {

	using namespace std::chrono;
	high_resolution_clock::time_point endTime = high_resolution_clock::now();

	//Calculating time span between constructor starTime and now
	duration<double> time_span = duration_cast<duration<double>>(endTime - startTime);

	//Return in ms
	return time_span.count() * 1000;
}

void Scheduler::swapQueues() {
	std::swap(queue1, queue2);
}

Scheduler::~Scheduler()
{
	delete[] processArray;
}
