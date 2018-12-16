#ifndef DLIST_PATEMPES_H_
#define DLIST_PATEMPES_H_

typedef struct dlistStruct {
	int data;
	struct dlistStruct *next;
	struct dlistStruct *prev;
} DListNode;

void printList(DListNode *theList);
/* print the list items from head to tail */

void printListReverse(DListNode *theList);
/* print the list items from tail to head */

int insertAtEnd(DListNode **theList, int data);
/* return zero if successful */

int insertSorted(DListNode **theList, int data);
/* return zero if successful */

int isInList(DListNode *theList, int data);
/* return non-zero value if the value is in the list; otherwise return zero */

int deleteFromList(DListNode **theList, int data);
/* if the value isn't in the list, then do nothing and return non-zero value; otherwise delete all listnodes matching the data from the list and return zero */

#endif
