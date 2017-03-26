#include "Scheduler.h"
#include <iostream>
#include <string>
#include <fstream>

bool compare(MyProcess* a, MyProcess* b) {
	return ((*a) > (*b));
}

Scheduler::Scheduler() : m_servingProcess(false), m_timeSlotCounter(HRClock::now()), queue1(compare), queue2(compare)
{

	std::cout << "Please enter the name of the input file: " << std::endl;
	std::string fileName;
	std::cin >> fileName;

	std::ifstream ifs;
	ifs.open(fileName);

	//Waiting until file is found and open. Otherwise, prompt user again
	while (!ifs) {
		std::cout << "Could not find file. Try again" << std::endl;
		std::cin >> fileName;
		ifs.open(fileName);
	}

	ifs >> m_arraySize;

	processArray = new MyProcess[m_arraySize];

	//Parsing input file
	for (int i = 0; i < m_arraySize; i++) {
		std::string pid;
		int arrival_time;
		int burst_time;
		int priority;

		ifs >> pid;
		ifs >> arrival_time;
		ifs >> burst_time;
		ifs >> priority;

		if (priority >= SCHEDULER_MIN_PRIORITY  && priority <= SCHEDULER_MAX_PRIORITY) {
			processArray[i] = MyProcess(pid, arrival_time, burst_time, priority);
		}
		else {
			std::cout << "Process " << pid << " does not have a valid priority. Skipping..." << std::endl;
		}
	}

	sortProcessArray(m_arraySize);

	std::cout << "----------SORTED PROCESSES----------" << std::endl;
	printProcesses(m_arraySize);

	ifs.close();
}

double getCurrentTime(HRClock::time_point startTime, HRClock::time_point endTime);

void Scheduler::run(DWORD(WINAPI *dummyRoutine)(LPVOID)) {
	std::ofstream ofs = std::ofstream("output.txt");

	std::cout << "----------STARTING SCHEDULER----------" << std::endl;

	setStartTime(HRClock::now());

	int procIndex = 0;

	while (!getActiveQueue().empty() || !getExpiredQueue().empty() || procIndex < getArraySize() || m_servingProcess) {

		double timeNow = getCurrentTime(getStartTime(), HRClock::now());
		//If process has arrived, add it to the queue and create thread
		if (timeNow >= getProcess(procIndex).getArrivalTime() && procIndex < getArraySize()) {

			MyProcess& currentProc = getProcess(procIndex);
			
			ofs << "Time " << timeNow << ", " << currentProc.getPid() << ", Arrived" << std::endl;
			std::cout << "Time " << timeNow << ", " << currentProc.getPid() << ", Arrived" << std::endl;

			//Calculating time slot
			int priority = currentProc.getPriority();

			double timeSlot;

			if (priority < 100) {
				timeSlot = (140 - priority) * 20;
			}
			else {
				timeSlot = (140 - priority) * 5;
			}
			currentProc.setTimeSlot(timeSlot);
			currentProc.setWaitTimeCounter(HRClock::now());

			double burstTime = currentProc.getBurstTime();
			HANDLE t_dummy = CreateThread(
				NULL,
				0,
				dummyRoutine,
				&currentProc,
				CREATE_SUSPENDED,
				NULL);
			currentProc.setHandle(t_dummy);

			//Pushing new process into the expired queue
			getExpiredQueue().push(&getProcess(procIndex));

			procIndex++;
		}

		//Swapping queues
		if (getActiveQueue().empty()) {
			swapQueues();
		}

		// If currently idle try to get first process in ready queue and start it
		if (!m_servingProcess) {
			if (!getActiveQueue().empty()) {
				m_currentProcess = getActiveQueue().top();

				getActiveQueue().pop();

				m_currentProcess->incrementTotalWaitTime();

				//Updating priority if necessary
				//if (m_currentProcess.getTimeSlotCount() % 2 == 0 && m_currentProcess.getTimeSlotCount() > 1) {

				//TODO
				//}

				m_servingProcess = true;
				m_timeSlotCounter = HRClock::now();

				std::cout << "Time " << timeNow << ", " << m_currentProcess->getPid() << ", " << ((m_currentProcess->isNew()) ? "Started, " : "Resumed, ")
					<< "Granted " << m_currentProcess->getTimeSlot() << std::endl;

				m_currentProcess->setNew(false);

				ResumeThread(m_currentProcess->getHandle());
			}
		}
		else {
			// Check if current process is terminated or if its timeslot is finished
			if (m_currentProcess->isTerminated()) {
				std::cout << "Time " << timeNow << ", " << m_currentProcess->getPid() << ", " << "Terminated" << std::endl;
				
				m_servingProcess = false;
			}
			else if (getCurrentTime(m_timeSlotCounter, HRClock::now()) >= m_currentProcess->getTimeSlot()) {
				std::cout << "Time " << timeNow << ", " << m_currentProcess->getPid() << ", " << "Paused" << std::endl;
				getExpiredQueue().push(m_currentProcess);

				m_servingProcess = false;
			}
		}
	}

	std::cout << "----------FINISHED----------" << std::endl;
}

void Scheduler::sortProcessArray(int arraySize) {
	MyProcess temp;

	for (int i = 0; i < arraySize; i++) {
		int minIndex = i;
		
		for (int j = i + 1; j < arraySize; j++) {
			//Sorting by arrival time
			if (processArray[j].getArrivalTime() < processArray[minIndex].getArrivalTime()) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			temp = processArray[i];
			processArray[i] = processArray[minIndex];
			processArray[minIndex] = temp;
		}
	}
}

void Scheduler::printProcesses(int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		std::cout << processArray[i].getPid() << " " << processArray[i].getArrivalTime() << " " << processArray[i].getBurstTime() << " " << processArray[i].getPriority() << std::endl;
	}
}

Scheduler::~Scheduler()
{
	delete[] processArray;
}
