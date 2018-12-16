#ifndef SLIST_PATEMPES_H_
#define SLIST_PATEMPES_H_

typedef struct slistStruct {
	int data;
	struct slistStruct *next;
} SListNode;

void printList(SListNode *theList);
/* print the list items from head to tail */

int insertAtEnd(SListNode **theList, int data);
/* return zero if successful */

int insertSorted(SListNode **theList, int data);
/* return zero if successfun */

int isInList(SListNode *theList, int data);
/* return non-zero value if the value is in the list; otherwise return zero */

int deleteFromList(SListNode **theList, int data);
/* if the value isn't in the list, then do nothing and return non-zero value;
 * otherwise delete all listnodes matching the data from the list and return
 * zero */

#endif
