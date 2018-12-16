#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.patempes.h"

#define START_TIME 0
#define NUM_PROCESSES 5
#define FCFS_PRIORITY 0

#define P1_SUBMISSION_TIME 0
#define P2_SUBMISSION_TIME 3
#define P3_SUBMISSION_TIME 4
#define P4_SUBMISSION_TIME 6
#define P5_SUBMISSION_TIME 6

// Data Structures and Enum:
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

// Main:
int main() {

	printf("First Come First Serve:\n");

	// Initialization of Processes:
	Process *P1, *P2, *P3, *P4, *P5;
	P1 = (Process *)malloc(sizeof(Process));
	P2 = (Process *)malloc(sizeof(Process));
	P3 = (Process *)malloc(sizeof(Process));
	P4 = (Process *)malloc(sizeof(Process));
	P5 = (Process *)malloc(sizeof(Process));

	P1->pid = 1;
	P2->pid = 2;
	P3->pid = 3;
	P4->pid = 4;
	P5->pid = 5;

	P1->burstTime = 6;
	P2->burstTime = 7;
	P3->burstTime = 2;
	P4->burstTime = 5;
	P5->burstTime = 2;

	P1->waitTime, P2->waitTime, P3->waitTime, P4->waitTime, P5->waitTime,
	P1->numPreemptions, P2->numPreemptions, P3->numPreemptions, P4->numPreemptions, P5->numPreemptions,
	P1->lastTime, P2->lastTime, P3->lastTime, P4->lastTime, P5->lastTime = 0;

	// Initialization of Priority Queues:
	PQueue *eventQueue;
	PQueue *cpuQueue;
	eventQueue = (PQueue *)malloc(sizeof(PQueue));
	cpuQueue = (PQueue *)malloc(sizeof(PQueue));

	eventQueue->head = NULL;
	eventQueue->tail = NULL;
	cpuQueue->head = NULL;
	cpuQueue->tail = NULL;

	// Initialization of Events:
	Event *processOneEvent, *processTwoEvent, *processThreeEvent, *processFourEvent, *processFiveEvent;
	processOneEvent = (Event *)malloc(sizeof(Event));
	processTwoEvent = (Event *)malloc(sizeof(Event));
	processThreeEvent = (Event *)malloc(sizeof(Event));
	processFourEvent = (Event *)malloc(sizeof(Event));
	processFiveEvent = (Event *)malloc(sizeof(Event));

	processOneEvent->eventType, processTwoEvent->eventType, processThreeEvent->eventType,
	processFourEvent->eventType, processFiveEvent->eventType = PROCESS_SUBMITTED;
	processOneEvent->process = P1; processTwoEvent->process = P2; processThreeEvent->process = P3;
	processFourEvent->process = P4; processFiveEvent->process = P5;

	enqueue(eventQueue, P1_SUBMISSION_TIME, processOneEvent);
	enqueue(eventQueue, P2_SUBMISSION_TIME, processTwoEvent);
	enqueue(eventQueue, P3_SUBMISSION_TIME, processThreeEvent);
	enqueue(eventQueue, P4_SUBMISSION_TIME, processFourEvent);
	enqueue(eventQueue, P5_SUBMISSION_TIME, processFiveEvent);

	// While Loop Section:
	int cpuIdleBoolean = 1;
	int cpuQueueCount = 0;
	int elapsedBurstTime = 0;
	int currentTime = START_TIME;
	int processesInProgress = NUM_PROCESSES;
	Event *currentEvent;

	currentTime = getMinPriority(eventQueue);
	currentEvent = (Event *)(dequeue(eventQueue));

	while(processesInProgress != 0) {
		// Case: PROCESS_SUBMITTED, Idle CPU:
		if (currentEvent->eventType == PROCESS_SUBMITTED && cpuIdleBoolean == 1) {
			currentEvent->eventType = PROCESS_STARTS;
			enqueue(eventQueue, currentTime, currentEvent);
			cpuIdleBoolean = 0;

			printf("t = %d PROCESS_SUBMITTED pid = %d\n", currentTime, currentEvent->process->pid);

			currentTime = getMinPriority(eventQueue);
			currentEvent = (Event *)(dequeue(eventQueue));

		// Case: PROCESS_SUBMITTED, Busy CPU:
		} else if (currentEvent->eventType == PROCESS_SUBMITTED && cpuIdleBoolean == 0) {
			currentEvent->process->waitTime = currentTime;
			enqueue(cpuQueue, FCFS_PRIORITY, currentEvent->process);
			++cpuQueueCount;

			printf("t = %d PROCESS_SUBMITTED pid = %d\n", currentTime, currentEvent->process->pid);

			currentTime = getMinPriority(eventQueue);
			currentEvent = (Event *)(dequeue(eventQueue));
	
		// Case: PROCESS_STARTS:
		} else if (currentEvent->eventType == PROCESS_STARTS) {
			currentEvent->eventType = PROCESS_ENDS;
			enqueue(eventQueue, currentTime + currentEvent->process->burstTime, currentEvent);
			cpuIdleBoolean = 0;

			printf("t = %d PROCESS_STARTS    pid = %d\n", elapsedBurstTime, currentEvent->process->pid);

			currentTime = getMinPriority(eventQueue);
			currentEvent = (Event *)(dequeue(eventQueue));

		// Case: PROCESS_ENDS:
		} else if (currentEvent->eventType == PROCESS_ENDS) {			
			cpuIdleBoolean = 1;
			--processesInProgress;
			elapsedBurstTime += currentEvent->process->burstTime;
			currentEvent->process->waitTime = elapsedBurstTime - currentEvent->process->burstTime - currentEvent->process->waitTime;
			
			printf("t = %d PROCESS_ENDS      pid = %d waitTime = %d\n", elapsedBurstTime, currentEvent->process->pid, currentEvent->process->waitTime);

			if (cpuQueueCount > 0) {
				currentEvent->process = (Process *)(dequeue(cpuQueue));
				currentEvent->eventType = PROCESS_STARTS;
				enqueue(eventQueue, currentTime, currentEvent);
				--cpuQueueCount;
			} else {
				currentTime = getMinPriority(eventQueue);
				currentEvent = (Event *)(dequeue(eventQueue));
			}
	
		// Case: PROCESS_TIMESLICE_EXPIRES:
		} else if (1 != 1) { //Intentionally False Placeholder

			currentTime = getMinPriority(eventQueue);
			currentEvent = (Event *)(dequeue(eventQueue));

		}
	}

	printf("\nShortest Job First:\n");

	// Initialization of Processes:
	Process *P1SJF, *P2SJF, *P3SJF, *P4SJF, *P5SJF;
	P1SJF = (Process *)malloc(sizeof(Process));
	P2SJF = (Process *)malloc(sizeof(Process));
	P3SJF = (Process *)malloc(sizeof(Process));
	P4SJF = (Process *)malloc(sizeof(Process));
	P5SJF = (Process *)malloc(sizeof(Process));

	P1SJF->pid = 1;
	P2SJF->pid = 2;
	P3SJF->pid = 3;
	P4SJF->pid = 4;
	P5SJF->pid = 5;

	P1SJF->burstTime = 6;
	P2SJF->burstTime = 7;
	P3SJF->burstTime = 2;
	P4SJF->burstTime = 5;
	P5SJF->burstTime = 2;

	P1SJF->waitTime, P2SJF->waitTime, P3SJF->waitTime, P4SJF->waitTime, P5SJF->waitTime,
	P1SJF->numPreemptions, P2SJF->numPreemptions, P3SJF->numPreemptions, P4SJF->numPreemptions, P5SJF->numPreemptions,
	P1SJF->lastTime, P2SJF->lastTime, P3SJF->lastTime, P4SJF->lastTime, P5SJF->lastTime = 0;

	// For some strange reason, the above paragraph of initialization code applies junk values to the fields, but
	// when I explicitly declare each individual field as 0 the error subsides.
	P1SJF->waitTime = 0;
	P2SJF->waitTime = 0;
	P3SJF->waitTime = 0;
	P4SJF->waitTime = 0;
	P5SJF->waitTime = 0;

	// Initialization of Priority Queues:
	PQueue *eventQueueSJF;
	PQueue *cpuQueueSJF;
	eventQueueSJF = (PQueue *)malloc(sizeof(PQueue));
	cpuQueueSJF = (PQueue *)malloc(sizeof(PQueue));

	eventQueueSJF->head = NULL;
	eventQueueSJF->tail = NULL;
	cpuQueueSJF->head = NULL;
	cpuQueueSJF->tail = NULL;

	// Initialization of Events:
	Event *processOneEventSJF, *processTwoEventSJF, *processThreeEventSJF, *processFourEventSJF, *processFiveEventSJF;
	processOneEventSJF = (Event *)malloc(sizeof(Event));
	processTwoEventSJF = (Event *)malloc(sizeof(Event));
	processThreeEventSJF = (Event *)malloc(sizeof(Event));
	processFourEventSJF = (Event *)malloc(sizeof(Event));
	processFiveEventSJF = (Event *)malloc(sizeof(Event));

	processOneEventSJF->eventType, processTwoEventSJF->eventType, processThreeEventSJF->eventType,
	processFourEventSJF->eventType, processFiveEventSJF->eventType = PROCESS_SUBMITTED;
	processOneEventSJF->process = P1SJF; processTwoEventSJF->process = P2SJF; processThreeEventSJF->process = P3SJF;
	processFourEventSJF->process = P4SJF; processFiveEventSJF->process = P5SJF;

	enqueue(eventQueueSJF, P1_SUBMISSION_TIME, processOneEventSJF);
	enqueue(eventQueueSJF, P2_SUBMISSION_TIME, processTwoEventSJF);
	enqueue(eventQueueSJF, P3_SUBMISSION_TIME, processThreeEventSJF);
	enqueue(eventQueueSJF, P4_SUBMISSION_TIME, processFourEventSJF);
	enqueue(eventQueueSJF, P5_SUBMISSION_TIME, processFiveEventSJF);

	// While Loop Section:
	int cpuIdleBooleanSJF = 1;
	int cpuQueueCountSJF = 0;
	int elapsedBurstTimeSJF = 0;
	int currentTimeSJF = START_TIME;
	int processesInProgressSJF = NUM_PROCESSES;
	Event *currentEventSJF;

	currentTimeSJF = getMinPriority(eventQueueSJF);
	currentEventSJF = (Event *)(dequeue(eventQueueSJF));

	while(processesInProgressSJF != 0) {
		// Case: PROCESS_SUBMITTED, Idle CPU:
		if (currentEventSJF->eventType == PROCESS_SUBMITTED && cpuIdleBooleanSJF == 1) {
			currentEventSJF->eventType = PROCESS_STARTS;
			enqueue(eventQueueSJF, currentTimeSJF, currentEventSJF);
			cpuIdleBooleanSJF = 0;

			printf("t = %d PROCESS_SUBMITTED pid = %d\n", currentTimeSJF, currentEventSJF->process->pid);

			currentTimeSJF = getMinPriority(eventQueueSJF);
			currentEventSJF = (Event *)(dequeue(eventQueueSJF));

		// Case: PROCESS_SUBMITTED, Busy CPU:
		} else if (currentEventSJF->eventType == PROCESS_SUBMITTED && cpuIdleBooleanSJF == 0) {
			currentEventSJF->process->waitTime = currentTimeSJF;
			enqueue(cpuQueueSJF, currentEventSJF->process->burstTime, currentEventSJF->process); //For SJF, priority is the burstTime.
			++cpuQueueCountSJF;

			printf("t = %d PROCESS_SUBMITTED pid = %d\n", currentTimeSJF, currentEventSJF->process->pid);

			currentTimeSJF = getMinPriority(eventQueueSJF);
			currentEventSJF = (Event *)(dequeue(eventQueueSJF));
	
		// Case: PROCESS_STARTS:
		} else if (currentEventSJF->eventType == PROCESS_STARTS) {
			currentEventSJF->eventType = PROCESS_ENDS;
			enqueue(eventQueueSJF, currentTimeSJF + currentEventSJF->process->burstTime, currentEventSJF);
			cpuIdleBooleanSJF = 0;

			printf("t = %d PROCESS_STARTS    pid = %d\n", elapsedBurstTimeSJF, currentEventSJF->process->pid);

			currentTimeSJF = getMinPriority(eventQueueSJF);
			currentEventSJF = (Event *)(dequeue(eventQueueSJF));

		// Case: PROCESS_ENDS:
		} else if (currentEventSJF->eventType == PROCESS_ENDS) {			
			cpuIdleBooleanSJF = 1;
			--processesInProgressSJF;
			elapsedBurstTimeSJF += currentEventSJF->process->burstTime;
			currentEventSJF->process->waitTime = elapsedBurstTimeSJF - currentEventSJF->process->burstTime - currentEventSJF->process->waitTime;
			
			printf("t = %d PROCESS_ENDS      pid = %d waitTime = %d\n", elapsedBurstTimeSJF, currentEventSJF->process->pid, currentEventSJF->process->waitTime);

			if (cpuQueueCountSJF > 0) {
				currentEventSJF->process = (Process *)(dequeue(cpuQueueSJF));
				currentEventSJF->eventType = PROCESS_STARTS;
				enqueue(eventQueueSJF, currentTimeSJF, currentEventSJF);
				--cpuQueueCountSJF;
			} else {
				currentTimeSJF= getMinPriority(eventQueueSJF);
				currentEventSJF = (Event *)(dequeue(eventQueueSJF));
			}
	
		// Case: PROCESS_TIMESLICE_EXPIRES:
		} else if (1 != 1) { //Intentionally False Placeholder

			currentTimeSJF = getMinPriority(eventQueueSJF);
			currentEventSJF = (Event *)(dequeue(eventQueueSJF));

		}
	}

	return(0);
}

