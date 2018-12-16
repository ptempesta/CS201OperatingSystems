#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/param.h>
#include "pqueue.patempes.h"

#define NONE 0
#define SJF 1
#define FCFS 2
#define RR 3

//----------------------------------------------------------------------

typedef struct {
  int pid;
  int burstTime;
  int waitTime;
  int numPreemptions;
  int lastTime;
} Process;

typedef enum EventTypeEnum {
  PROCESS_SUBMITTED,
  PROCESS_STARTS,
  PROCESS_ENDS,
  PROCESS_TIMESLICE_EXPIRES
} EventType;

typedef struct {
  EventType eventType;
  Process *process;
} Event;

int totalWaitTime;

//----------------------------------------------------------------

void print_event(Event *event) {
  if (event->eventType == PROCESS_SUBMITTED)
    printf(" PROCESS_SUBMITTED");
  else if (event->eventType == PROCESS_STARTS)
    printf(" PROCESS_STARTS");
  else if (event->eventType == PROCESS_ENDS)
    printf(" PROCESS_ENDS");
  else if (event->eventType == PROCESS_TIMESLICE_EXPIRES)
    printf(" PROCESS_TIMESLICE_EXPIRES");
  printf(" pid=%d", event->process->pid);
  if (event->eventType == PROCESS_ENDS)
    printf(" wt=%d", event->process->waitTime);
  printf(" ---\n");
}

//----------------------------------------------------------------

void runSimulation(
        int schedulerType,
        PQueue eventQueue,
        PQueue cpuQueue) {
  int currentTime;
  Event *event, *endEvent;
  Process *process;
  int active_pid;
  int readyQueueLength;

  // Added for part III.
  int quantum;
  quantum = 4;

  active_pid = -1;
  currentTime = getMinPriority(&eventQueue);

  event = (Event *) dequeue(&eventQueue);
  while (event != NULL) {
    printf("--- time=%d", currentTime);

    print_event(event);

    if (event->eventType == PROCESS_SUBMITTED) {
      process = event->process;

      printf("at time %d, enqueue process %d\n", currentTime, process->pid);

      process->lastTime = currentTime;

      if (active_pid == -1) {
        Event *newEvent = (Event *) malloc(sizeof(Event));
        newEvent->process = process;
        newEvent->eventType = PROCESS_STARTS;
        printf("new event at %d: PROCESS_STARTS(%d) pid=%d\n", currentTime, newEvent->eventType, process->pid);
        enqueue(&eventQueue, currentTime, newEvent);
        active_pid = process->pid;
      } else {
        // put process in CPU queue (= ready state)
        if (schedulerType == FCFS) {
          enqueue(&cpuQueue, 0, process);
        } else if (schedulerType == SJF) {
          enqueue(&cpuQueue, process->burstTime, process);
        } else if (schedulerType == RR) {
	  // Filled in for part III.

	  // Put the new process in the CPU queue using SJF priority.
          enqueue(&cpuQueue, 0, process);

        }
      } // if-then-else for cpu is idle
    } // PROCESS_SUBMITTED

    else if (event->eventType == PROCESS_ENDS) {
      active_pid = -1;
      process = event->process;
      printf("process %d finishes at %d, waitTime=%d\n", process->pid, currentTime, process->waitTime);
      printf("* P%d finishes at %d\n", process->pid, currentTime);
      totalWaitTime = totalWaitTime + process->waitTime;

      // check cpu queue
      process = (Process *) dequeue(&cpuQueue);
      if (process != NULL) {
        endEvent = (Event *) malloc(sizeof(Event));
        endEvent->process = process;
        endEvent->eventType = PROCESS_STARTS;
        printf("new event at %d: PROCESS_STARTS(%d) pid=%d\n", currentTime, endEvent->eventType, process->pid);
        enqueue(&eventQueue, currentTime, endEvent);
      }
    } // PROCESS_ENDS

    else if (event->eventType == PROCESS_TIMESLICE_EXPIRES) {
      // Filled in for part III.

      // Enqueue shelved process to cpuQueue.
      active_pid = -1;
      process = event->process;
      printf("process %d shelved at %d, waitTime=%d\n", process->pid, currentTime, process->waitTime);
      totalWaitTime = totalWaitTime + process->waitTime;
      enqueue(&cpuQueue, 0, process);

      // Dequeue ready process from cpuQueue to eventQueue.
      process = (Process *) dequeue(&cpuQueue);
      if (process != NULL) {
        endEvent = (Event *) malloc(sizeof(Event));
        endEvent->process = process;
        endEvent->eventType = PROCESS_STARTS;
        printf("new event at %d: PROCESS_STARTS(%d) pid=%d\n", currentTime, endEvent->eventType, process->pid);
        enqueue(&eventQueue, currentTime, endEvent);
      }

    } // PROCESS_TIMESLICE_EXPIRES

    else if (event->eventType == PROCESS_STARTS) {
      process = event->process;
      process->waitTime = process->waitTime + (currentTime - process->lastTime);
      printf("* P%d starts at %d (wt=%d, %d)\n",
             process->pid, currentTime,
             currentTime - process->lastTime, process->waitTime);

      endEvent = (Event *) malloc(sizeof(Event));
      endEvent->process = process;

      if (schedulerType == RR) {
        // Filled in for part III.
        
	// If the current process's burst time is longer than its quantum, create a PROCESS_TIMESLICE_EXPIRES
	// event, decrement the burst time by the quantum, and enqueue the event.
	if (process->burstTime > quantum) {
	  endEvent->process->burstTime -= quantum;
	  endEvent->eventType = PROCESS_TIMESLICE_EXPIRES;
	  printf("new event at %d: PROCESS_TIMESLICE_EXPIRES (%d) pid=%d\n", currentTime + quantum, endEvent->eventType, process->pid);
	  enqueue(&eventQueue, currentTime + quantum, endEvent);
	}

	// Otherwise create a PROCESS_ENDS event and enqueue the event.
        else {
          endEvent->eventType = PROCESS_ENDS;
          printf("new event at %d: PROCESS_ENDS(%d) pid=%d\n", currentTime + process->burstTime, endEvent->eventType, process->pid);
          enqueue(&eventQueue, currentTime + process->burstTime, endEvent);
	}

      } else {
        endEvent->eventType = PROCESS_ENDS;
        printf("new event at %d: PROCESS_ENDS(%d) pid=%d\n", currentTime + process->burstTime, endEvent->eventType, process->pid);
        enqueue(&eventQueue, currentTime + process->burstTime, endEvent);
      }

      active_pid = process->pid;
    } // PROCESS_STARTS

    free(event);
    currentTime = getMinPriority(&eventQueue);
    event = dequeue(&eventQueue);
  } /* while event queue is not empty */

} // runSimulation()

// gen_exprand function for part II
int gen_exprand(double mean) {
	double r, t;
	int rtnval;
	r = drand48();
	t = -log(1-r) * (mean - 0.5);
	rtnval = 1 + (int) floor(t);
	return(rtnval);
}

//---------------------------------------------------------------------

int main(int argc, char *argv[]) {
  int i;
  long seed;
  int numProcesses;
  int schedulerType;
  Process *process;
  Event *event;
  PQueue eventQueue;
  PQueue cpuQueue;

//these calls will be useful for part II
time(&seed);
srand48(seed);

  totalWaitTime = 0;

  eventQueue.head = NULL;
  eventQueue.tail = NULL;
  cpuQueue.head = NULL;
  cpuQueue.tail = NULL;

  // Additional variables for part II:
  double proc_interarrival_time_mean = 10;
  double proc_burst_time_mean = 10;
  int proc_interarrival_time, t;

  numProcesses = 50; // Set this to 50 for part II.
  t = 0; // Set t = 0 for part II.

  for (i=0; i<numProcesses; ++i) {
    process = (Process *) malloc(sizeof(Process));
    process->pid = i+1; // start the PIDs at one instead of zero
    process->burstTime = gen_exprand(proc_burst_time_mean); // Random burst time for part II
    process->waitTime = 0;
    process->numPreemptions = 0;
    process->lastTime = 0;

    printf("created process %d; burstTime = %d start_time=%d\n", process->pid, process->burstTime, t);

    event = (Event *) malloc(sizeof(Event));
    event->eventType = PROCESS_SUBMITTED;
    event->process = process;

    proc_interarrival_time = gen_exprand(proc_interarrival_time_mean); // Random process "next" start time for part II
    t = t + proc_interarrival_time; // Actual random process start time for part II

    enqueue(&eventQueue, t, event);
  }

/*

  // Test Processes.
  numProcesses = 5;
  int startTimes[] = {0, 3, 4, 6, 6};
  int burstTimes[] = {6, 7, 2, 5, 2};

  for (i=0; i<numProcesses; ++i) {
    process = (Process *) malloc(sizeof(Process));
    process->pid = i+1; // start the PIDs at one instead of zero
    process->burstTime = burstTimes[i];
    process->waitTime = 0;
    process->numPreemptions = 0;
    process->lastTime = 0;

    printf("created process %d; burstTime = %d start_time=%d\n", process->pid, process->burstTime, startTimes[i]);

    event = (Event *) malloc(sizeof(Event));
    event->eventType = PROCESS_SUBMITTED;
    event->process = process;
    enqueue(&eventQueue, startTimes[i], event);
  }

*/

  schedulerType = RR; // Options: FCFS, SJF, RR

  runSimulation(schedulerType, eventQueue, cpuQueue);

  printf("\n");
  printf("total wait time = %d\n", totalWaitTime);
  printf("mean wait time = %.2f\n", (float) totalWaitTime / numProcesses);
  return(0);
}

