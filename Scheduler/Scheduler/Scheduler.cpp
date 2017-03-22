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
	while (!ifs) {
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
		int arrival_time;
		int burst_time;
		int priority;

		ifs >> pid;
		ifs >> arrival_time;
		ifs >> burst_time;
		ifs >> priority;

		if (priority >= MINI_PRIORITY  && priority <= MAXI_PRIORITY) {
			processArray[i] = MyProcess(pid, arrival_time, burst_time, priority);
		}
		else {
			std::cout << "Process " << pid << " does not have a valid priority. Skipping..." << std::endl;
		}
	}

	sortProcessArray(arraySize);
	printProcesses(arraySize);
	ifs.close();
}

void Scheduler::sortProcessArray(int arraySize) {
	int init = 0;
	MyProcess temp;

	for (int i = 0; i < arraySize; i++) {
		for (int j = 0; j < arraySize; j++) {
			//Sorting by arrival time
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

void Scheduler::printProcesses(int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		std::cout << processArray[i].getPid() << " " << processArray[i].getArrivalTime() << " " << processArray[i].getBurstTime() << " " << processArray[i].getPriority() << std::endl;
	}
}

void Scheduler::swapQueues() {
	std::swap(queue1, queue2);
}

Scheduler::~Scheduler()
{
	delete[] processArray;
}
