#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.patempes.h"

//----------------------------------------------------------------------

void pqueue_test_3() {
  PQueue pqueue;
  DataNode *data;
  char buf[16];
  int i, ival, numvals;
  int vals[16];
  int priority;

  printf("start of pqueue_test_3()\n");

  vals[0] = 5;
  vals[1] = 3;
  vals[2] = 17;
  vals[3] = 35;
  vals[4]=  10;
  vals[5] = 8;
  vals[6] = 20;
  vals[7] = 41;
  vals[8] = 9;
  vals[9] = 2;

  pqueue.head = NULL;
  pqueue.tail = NULL;

  numvals = 10;
  for (i=0; i<numvals; ++i) {
    ival = vals[i];
    sprintf(buf, "%dA", ival);
    data = (DataNode *) malloc(sizeof(DataNode));
    strcpy(data->name, buf);
    //printf("insert %d\n", ival);
    enqueue(&pqueue, ival, data);

    if ( i % 2 == 0 ) {
      priority = getMinPriority(&pqueue);
      data = (DataNode *) dequeue(&pqueue);
      if (data != NULL) {
        //printf("dequeued %d %s\n", priority, data->name);
      }
    }
  }

  // should see |2 2A|17 17A|20 20A|35 35A|41 41A|
  printQueue(&pqueue);

  for (i=0; i<6; ++i) {
    data = (DataNode *) dequeue(&pqueue);
  }

  printf("An empty queue should follow:\n");
  // should see empty queue
  printQueue(&pqueue);
  printf("Check: empty above?\n");
}

//----------------------------------------------------------------------

void pqueue_test_4() {
  PQueue pqueue;
  DataNode *data;
  char buf[16];
  int i, ival, numvals;
  int vals[16];

  printf("start of pqueue_test_4()\n");

  vals[0] = 5;
  vals[1] = 3;
  vals[2] = 17;
  vals[3] = 35;
  vals[4] = 10;
  numvals = 5;

  pqueue.head = NULL;
  pqueue.tail = NULL;

  for (i=0; i<numvals; ++i) {
    ival = vals[i];
    sprintf(buf, "%dA", ival);
    data = (DataNode *) malloc(sizeof(DataNode));
    strcpy(data->name, buf);
    //printf("insert %d\n", ival);
    enqueue(&pqueue, ival, data);

    sprintf(buf, "%dB", ival);
    data = (DataNode *) malloc(sizeof(DataNode));
    strcpy(data->name, buf);
    //printf("insert %d\n", ival);
    enqueue(&pqueue, ival, data);
    //printQueue(pqueue);
  }

  // should see |3 3A|3 3B|5 5A|5 5B|10 10A|10 10B|17 17A|17 17B|35 35A|35 35B|
  printQueue(&pqueue);
}

//----------------------------------------------------------------
/*
main(int argc, char *argv[]) {
  pqueue_test_3();
  pqueue_test_4();
}
*/
