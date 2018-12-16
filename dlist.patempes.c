#include "dlist.patempes.h"

void printList(DListNode *theList) {
	DListNode *listNode;

	listNode = theList;
	while (listNode) {
		printf("%d ", listNode->data);
		listNode = listNode->next;
	}
	printf("\n");

}
	
/*	DListNode *cursor;
	cursor = theList;
	while(cursor!=NULL) {
		printf("%d ", cursor->data);
		cursor = cursor->next;
	}
	printf("\n");
*/


void printListReverse(DListNode *theList) {
	DListNode *listNode;

	listNode = theList;
	while(listNode->next != NULL) {
		listNode = listNode->next;
	}
	while(listNode->prev != NULL) {
		printf("%d ", listNode->data);
		listNode = listNode->prev;
	}
	printf("%d\n", listNode->data);

}

/*	DListNode *cursor;
	cursor = theList;
	while(cursor->next!=NULL) {
		cursor = cursor->next;
	}
	while(cursor->prev!=NULL) {
		printf("%d ", cursor->data);
		cursor = cursor->prev;
	}
	printf("%d\n", cursor->data);
*/


int insertAtEnd(DListNode **theList, int value) {
	DListNode *curNode, *newNode;

	newNode = (DListNode *) malloc(sizeof(DListNode));
	newNode->data = value;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (*theList == NULL) {
		*theList = newNode;
		return(0);
	} else {
		curNode = *theList;
		while (curNode->next != NULL) {
			curNode = curNode->next;
		}
		curNode->next = newNode;
		newNode->prev = curNode;
		return(0);
	}
}

/*	DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
	DListNode* lastNode = *theList;

	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;

	if(lastNode==NULL) {
		*theList = newNode;
		return(0);
	}

	while(lastNode->next!=NULL) {
		lastNode = lastNode->next;
	}

	lastNode->next = newNode;
	newNode->prev = lastNode;

	return(0);
*/


int insertSorted(DListNode **theList, int value) {
	DListNode *listNode, *newNode, *prevNode;
	int found;

	newNode = (DListNode *) malloc(sizeof(DListNode));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->data = value;

	if (*theList == NULL) {
		*theList = newNode;
		return(0);
	} else {
		if (value <= (*theList)->data) {
			newNode->next = *theList;
			listNode = *theList;
			listNode->prev = newNode;
			*theList = newNode;
			return(0);
		} else {
			listNode = *theList;
			// while (listNode != NULL && listNode->data < value)
			found = 0;
			while ( ! found ) {
				if (listNode == NULL)
					found = 1;
				else if (listNode->data >= value)
					found = 1;
				else {
					prevNode = listNode;
					listNode = listNode->next;
				}
			}

			if (listNode == NULL) {
				prevNode->next = newNode;
				newNode->prev = prevNode;
				return(0);
			} else {
				prevNode->next = newNode;
				newNode->next = listNode;
				newNode->prev = prevNode;
				listNode->prev = newNode;
				return(0);
			}
		}
	}
}


/*	DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
	DListNode* lastNode = *theList;

	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (lastNode==NULL) {
		*theList = newNode;
		return(0);
	}

	if (lastNode->data>data) {
		newNode->next = lastNode;
		lastNode->prev = newNode;
		*theList = newNode;
		return(0);
	}

	if (lastNode->next==NULL) {
		if(lastNode->data<=data) {
			lastNode->next = newNode;
			newNode->prev = lastNode;
			return(0);
		}
	}

	while(lastNode->next!=NULL) {
		if(lastNode->data>data) {
			newNode->prev = lastNode->prev;
			newNode->next = lastNode;
			lastNode->prev->next = newNode;
			lastNode->prev = newNode;
			return(0);
		}
		lastNode = lastNode->next;
		if(lastNode->next==NULL) {
			lastNode->next = newNode;
			newNode->prev = lastNode;
			return(0);
		}
	}
*/


int isInList(DListNode *theList, int value) {
	DListNode *listNode;
	int found;

	found = 0;
	listNode = theList;
	while ( ! found && listNode != NULL) {
		if (listNode->data == value)
			found = 1;
		else
			listNode = listNode->next;
	}

	return(found);

}

/*	DListNode *cursor;
	cursor = theList;
	while(cursor!=NULL) {
		if(cursor->data==data) {
			return(1);
		}
		cursor = cursor->next;
	}
	return(0);
*/


int deleteFromList(DListNode **theList, int value) {
	DListNode *listNode, *prevNode, *nextNode;
	int found;

	found = 0;
	listNode = *theList;
	prevNode = NULL;
	while (listNode != NULL) {
		nextNode = listNode->next;
		if (listNode->data == value) {
			found = 1;
			// Special case: node to delete at end of list:
			if (listNode->next == NULL) {
				prevNode->next = NULL;
				free(listNode);
				return(0);
			}
			if (prevNode != NULL) {
				prevNode->next = nextNode;
				nextNode->prev = prevNode;
				free(listNode);
			} else {
				nextNode->prev = NULL;
				*theList = nextNode;
				free(listNode);
			}
		} else {
			prevNode = listNode;
		}
		listNode = nextNode;
	}
	if (found)
		return(0);
	else
		return(1);
}

/*	DListNode* lastNode = *theList;
	DListNode* prevNode = NULL;
	int delBool = 0;

	if(lastNode==NULL) {
		return(1);
	}

	while(lastNode->next!=NULL) {
		if(data==lastNode->data) {
			if(lastNode->next!=NULL) {
				prevNode->next = lastNode->next;
				lastNode->next->prev = prevNode;
				free(lastNode);
				delBool = 1;
			}
		}
		prevNode = lastNode;
		lastNode = lastNode->next;
	}

	if(lastNode->next==NULL) {
		if(data==lastNode->data) {
			free(lastNode);
			prevNode->next = NULL;
			delBool = 1;
		}
	}

	if(delBool==0) {
		return(1);
	}
	else {
		return(0);
	}
*/
