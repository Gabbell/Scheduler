#include "Scheduler.h"

Scheduler::Scheduler()
{
	std::cout << "Please enter the name of the input file: ";
	std::string fileName;
	std::cin >> fileName;


	startTime = std::chrono::high_resolution_clock::now();

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
}
