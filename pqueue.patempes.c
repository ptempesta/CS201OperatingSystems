#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.patempes.h"

int enqueue(PQueue *pqueue, int priority, void *data) {
	PQueueNode *prevNode, *curNode, *newNode;

	newNode = (PQueueNode *) malloc(sizeof(PQueueNode));
	newNode->priority = priority;
	newNode->data = data;
	newNode->next = NULL;

	// Case 1: Queue is empty.
	if (pqueue->head == NULL) {
		pqueue->head = newNode;
		pqueue->tail = newNode;
		return(0);
	}
	else {
		curNode = pqueue->head;
		// Case 2: New node goes to front of queue:
		if (priority < curNode->priority) {
			pqueue->head = newNode;
			newNode->next = curNode;
			return(0);
		}
		else {
			// Traverse until either at end or priority lower:
			while(curNode != NULL && curNode->priority <= priority) {
				prevNode = curNode;
				curNode = curNode->next;
			}
			// Case 3: New node goes between two nodes:
			if(curNode != NULL) {
				prevNode->next = newNode;
				newNode->next = curNode;
				return(0);
			}
			// Case 4: New node goes to end of queue:
			else {
				prevNode->next = newNode;
				pqueue->tail = newNode;
				return(0);
			}
		}
	}
}

void *dequeue(PQueue *pqueue) {
	PQueueNode *delNode;
	DataNode *delNodeData;

	if(pqueue->head == NULL) {
		return(NULL);
	}
	else {
		delNode = pqueue->head;
		delNodeData = delNode->data;
		pqueue->head = delNode->next;
		free(delNode);
		return(delNodeData);
	}
}

int printQueue(PQueue *pqueue) {
	PQueueNode *prevNode, *curNode;

	if(pqueue->head == NULL) {
		return(0);
	}
	else {
		curNode = pqueue->head;
		while(curNode) {
			printf("Priority: %d, ", curNode->priority);
			printf("Data: %s\n", curNode->data);
			curNode = curNode->next;
		}
	}
	return(0);
}

void *peek(PQueue *pqueue) {

	if (pqueue->head == NULL) {
		return(NULL);
	}
	else {
		return(pqueue->head->data);
	}
}

int getMinPriority(PQueue *pqueue) {

	if (pqueue->head == NULL) {
		return(-1);
	}
	else {
		return(pqueue->head->priority);
	}
}
