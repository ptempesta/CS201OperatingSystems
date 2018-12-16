#include "slist.patempes.h"

void printList(SListNode *theList)
{
	SListNode *cursor;
	cursor = theList;
	while(cursor!=NULL)
	{
		printf("%d ", cursor->data);
		cursor = cursor->next;
	}
	printf("\n");
}

int insertAtEnd(SListNode **theList, int data)
{
	SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
	SListNode* lastNode = *theList;

	newNode->data = data;
	newNode->next = NULL;

	if (lastNode == NULL)
	{
		*theList = newNode;
		return(0);
	}

	while(lastNode->next!=NULL)
		lastNode = lastNode->next;

	lastNode->next = newNode;

	return (0);
}

int insertSorted(SListNode **theList, int data) {

	SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
	SListNode* lastNode = *theList;
	SListNode* prevNode = NULL;

	newNode->data = data;
	newNode->next = NULL;

	if (lastNode==NULL) {
		*theList = newNode;
		return(0);
	}

	if (lastNode->data>data) {
		newNode->next = lastNode;
		*theList = newNode;
		return(0);
	}

	if (lastNode->next==NULL) {
		if(lastNode->data<=data) {
			lastNode->next = newNode;
			return(0);
		}
	}

	while(lastNode->next!=NULL) {
		if(lastNode->data<=data) {
			prevNode = lastNode;
		}
		else {
			newNode->next = lastNode;
			prevNode->next = newNode;
			return(0);
		}
		lastNode = lastNode->next;
		if(lastNode->next==NULL) {
			lastNode->next = newNode;
			return(0);
		}
	}

}

int isInList(SListNode *theList, int data)
{
	SListNode *cursor;
	cursor = theList;
	while(cursor!=NULL)
	{
		if(cursor->data == data)
			return(1);
		cursor = cursor->next;
	}
	return(0);
}

int deleteFromList(SListNode **theList, int data)
{
	SListNode* lastNode = *theList;
	SListNode* prevNode = NULL;
	int delBool = 0;

	if(lastNode==NULL)
	{
		return(1);
	}
	
	while(lastNode->next!=NULL)
	{
		if(data == lastNode->data)
		{
			if(lastNode->next!=NULL)
			{
				prevNode->next = lastNode->next;
				free(lastNode);
				delBool = 1;
			}
		}
		prevNode = lastNode;
		lastNode = lastNode->next;
	}
	if(lastNode->next==NULL)
	{
		if(data == lastNode->data)
		{
			free(lastNode);
			prevNode->next = NULL;
			delBool = 1;
		}
	}

	if(delBool == 0)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}
