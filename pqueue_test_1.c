#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.patempes.h"

void pqueue_test_1() {
  PQueue pqueue;
  DataNode *data;
  int priority;

  printf("start of test_1()\n");

  // initialize a priority queue
  pqueue.head = NULL;
  pqueue.tail = NULL;

  // enqueue data with priority = 1
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data one");
  priority = 1;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  // enqueue data with priority = 4
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data four-a");
  priority = 4;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  // enqueue data with priority = 2
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data two");
  priority = 2;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  // enqueue data with priority = 8
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data eight");
  priority = 8;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  // enqueue data with priority = 4
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data four-b");
  priority = 4;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  printQueue(&pqueue);
  priority = getMinPriority(&pqueue);
  data = (DataNode *) dequeue(&pqueue);
  while (data != NULL) {
    printf("dequeue: %s, priority = %d\n", data->name, priority);
    priority = getMinPriority(&pqueue);
    data = (DataNode *) dequeue(&pqueue);
  }

  data = (DataNode *) dequeue(&pqueue);
  if (data != NULL) {
    printf("ERROR: expected empty queue\n");
  }

  printf("end of test_1()\n");
  printf("\n");
}
