#ifndef PQUEUE_PATEMPES_H_
#define PQUEUE_PATEMPES_H_

// Structures

typedef struct {
	char name[16];
} DataNode;

typedef struct PQN {
	int priority;
	void *data;
	struct PQN *next;
} PQueueNode;

typedef struct {
	PQueueNode *head;
	PQueueNode *tail;
} PQueue;

// Functions

int enqueue(PQueue *pqueue, int priority, void *data);
// Put node in queue in priority order; in case of tie in priority, put node
// after all nodes with the specified priority; this function should always
// return zero.

void *dequeue(PQueue *pqueue);
// Return NULL if queue is empty; otherwise return the data (the DataNode) from
// the first node in the queue (since the queue is maintained in priority order--
// from lowest to highest--this will be the data from the node having the
// smallest priority value).

int printQueue(PQueue *pqueue);
// Print queue from head to tail; this function should always return zero.

void *peek(PQueue *pqueue);
// Return the first node in the queue, but do not remove it; return NULL if the
// queue is empty.

int getMinPriority(PQueue *pqueue);
// Return priority of first node in queue; return -1 if queue is empty.

#endif

