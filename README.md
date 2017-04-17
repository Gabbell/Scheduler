# CPU Scheduler
COEN346 - Operating Systems - Assignment 2 & 3 - CPU Scheduler

A CPU Scheduler that simulates process scheduling using Windows threads.

## Requirements
The goal of this assignment is to successfully create a CPU scheduler that will be preemptive and priority-based. The processes are simulated using threads and the scheduler itself must be able to control the state of these threads. Time slots are given to each thread based on their priorities. This priority is also dynamic based on if two time slots were given previously. For this reason, we used Windows threads because we were able to suspend them if needed and even create them in a suspended state. The preemptive nature of the scheduler will make it so a currently running process can be interrupted by another one. Also, the program should read the instructions from a local file (ifstream) and write the output in a specified format to a text file (ofstream).

## Results
There were many issue that arose when trying to create the scheduler. One of the more prominent issues was using threads to simulate processes. Since we were using threads that were actually controlled under the hood by the OS instead of our scheduler, the timings would be off by a couple of milliseconds. There is also the issue where a process has completed its burst time but has been suspended by our scheduler before it had a chance to notify the scheduler of its completion. There was also a big issue which needed to be solved that involved calculating the amount of time a thread has been running.  The calculations of the running time were done in the thread since the scheduler doesn’t know exactly how long a process will take to complete. The problem with doing it this way is that when we suspend the thread it can no longer update its counters properly since it's using real life time that always increments whether or not a thread is suspended. In order to solve this we used the total wait time of the thread to help with this calculation.
