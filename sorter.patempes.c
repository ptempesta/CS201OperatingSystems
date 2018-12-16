#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#define NUMVALS 1024

typedef struct {
	int start_index;
	int end_index;
} SortInfo;

// Generate a random integer r such that low <= r <= high.
int getRand(int low, int high) {
	double r1, r2;
	int rtnval;
	r1 = drand48();
	r2 = (1 + high - low) * r1;
	rtnval = low + floor(r2);
	return(rtnval);
}

// Global Arrays:
int initialArray[NUMVALS];
int mergeArray[NUMVALS];

void *sorter(void *sortInfoParam) {
	SortInfo *sortInfo;
	sortInfo = (SortInfo *) sortInfoParam;

	int temp;
	int iter;
	int swapped = 1;
	int lim = sortInfo->end_index;
	while (swapped == 1) {
		swapped = 0;
		for (iter = sortInfo->start_index; iter < lim; ++iter){
			if (initialArray[iter] >  initialArray[iter + 1]){
				temp = initialArray[iter];
				initialArray[iter] = initialArray[iter + 1];
				initialArray[iter + 1] = temp;
				swapped = 1;
			}
		}
	}

	pthread_exit(0);
}

void *merger(void *sortInfoParam) {
	int *indexPointer;
	indexPointer = (int *) sortInfoParam;

	int loopIter;
	int leftIter = 0;
	int rightIter = *indexPointer; //513

	int midIndex = NUMVALS / 2; //512
	int endIndex = NUMVALS; //1024
	int currentIndex = 0;

	for (loopIter = 0; loopIter < endIndex; ++loopIter) {
		if (leftIter < midIndex && rightIter < endIndex) {
			if (initialArray[leftIter] < initialArray[rightIter]) {
				mergeArray[loopIter] = initialArray[leftIter];
				++leftIter;
				++currentIndex;
			}
			else {
				mergeArray[loopIter] = initialArray[rightIter];
				++rightIter;
				++currentIndex;
			}
		}
	}

	// Cases in which one array has already finished iterating:
	if (leftIter < midIndex) {
		for (loopIter = leftIter; loopIter <= midIndex; ++loopIter) {
			mergeArray[currentIndex] = initialArray[loopIter];
			++currentIndex;
		}
	}

	if (rightIter < endIndex) {
		for (loopIter = rightIter; loopIter <= endIndex; ++loopIter) {
			mergeArray[currentIndex] = initialArray[rightIter];
			++currentIndex;
		}
	}

	pthread_exit(0);
}

int main() {

	// Initialization of thread values:
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_attr_t attr;

	int i; // Iterator
	int lowVal = 1; // Set for getRand function.
	int highVal = 1000; // Set for getRand function.
	int secondStart; // Starting middle index for merge function.

	// Populate the initial array.
	for (i = 0; i < NUMVALS; ++i) {
		initialArray[i] = getRand(lowVal, highVal);	
	}

	// SortInfo structure information:
	SortInfo sortInfo1, sortInfo2;
	sortInfo1.start_index = 0;
	sortInfo1.end_index = NUMVALS / 2;
	sortInfo2.start_index = sortInfo1.end_index + 1;
	sortInfo2.end_index = NUMVALS - 1;

	// Thread attribute initialization:
	pthread_attr_init(&attr);

	// Creation and joining of sorting threads:
	pthread_create(&tid1, &attr, sorter, &sortInfo1);
	pthread_create(&tid2, &attr, sorter, &sortInfo2);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	// Index initialization, creation and joining of merge thread:
	secondStart = sortInfo2.start_index;
	pthread_create(&tid3, &attr, merger, &secondStart);
	pthread_join(tid3, NULL);

	// Print the merged and sorted array:
	for (i = 0; i < NUMVALS; ++i) {
		printf("Element %d: %d\n", i+1,  mergeArray[i]);
	}
	return(0);
}
