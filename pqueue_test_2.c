#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.patempes.h"

void pqueue_test_2() {
  PQueue pqueue;
  DataNode *data;
  int priority;

  printf("start of test_2()\n");

  // initialize a priority queue
  pqueue.head = NULL;
  pqueue.tail = NULL;

  // enqueue data with priority = 8
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data four-a");
  priority = 4;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  // enqueue data with priority = 3
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data three");
  priority = 3;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  // enqueue data with priority = 10
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data ten");
  priority = 10;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  priority = getMinPriority(&pqueue);
  data = (DataNode *) dequeue(&pqueue);
  if (data == NULL) {
    printf("ERROR: expect data to be non-null\n");
  } else {
    printf("dequeue: %s, priority = %d\n", data->name, priority);
  }

  // enqueue data with priority = 4
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data four-b");
  priority = 4;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  // enqueue data with priority = 6
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data six");
  priority = 6;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  priority = getMinPriority(&pqueue);
  data = (DataNode *) dequeue(&pqueue);
  if (data == NULL) {
    printf("ERROR: expect data to be non-null\n");
  } else {
    printf("dequeue: %s, priority = %d\n", data->name, priority);
  }

  // enqueue data with priority = 1
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data one");
  priority = 1;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  priority = getMinPriority(&pqueue);
  data = (DataNode *) dequeue(&pqueue);
  if (data == NULL) {
    printf("ERROR: expect data to be non-null\n");
  } else {
    printf("dequeue: %s, priority = %d\n", data->name, priority);
  }

  // enqueue data with priority = 9
  data = (DataNode *) malloc(sizeof(DataNode));
  strcpy(data->name, "data nine");
  priority = 9;
  printf("enqueue %s %d\n", data->name, priority);
  enqueue(&pqueue, priority, data);

  priority = getMinPriority(&pqueue);
  data = (DataNode *) peek(&pqueue);
  if (data == NULL) {
    printf("ERROR: expect data to be non-null\n");
  } else {
    printf("peek: %s, priority = %d\n", data->name, priority);
  }

  priority = getMinPriority(&pqueue);
  printQueue(&pqueue);
  data = (DataNode *) dequeue(&pqueue);
  while (data != NULL) {
    printf("dequeue: %s, priority = %d\n", data->name, priority);
    priority = getMinPriority(&pqueue);
    data = (DataNode *) dequeue(&pqueue);
  }

  printf("end of test_2()\n");
  printf("\n");
}
