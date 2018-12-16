#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5
#define RUNTIME 10
#define EAT_TIME 2
#define THINK_TIME 1
#define SEMAPHORE_COUNT 2

pthread_mutex_t forks[NUM_PHILOSOPHERS];
sem_t diningSemaphore;

void *philosopher(void *param) {

	int *myID;
	myID = (int *) param;

	int leftIdx = *myID;
	int rightIdx = (*myID + 1) % NUM_PHILOSOPHERS;
	printf("Philosopher %d starting:\n", *myID);

	while ( 1 ) {
		pthread_mutex_lock(&(forks[leftIdx]));
		usleep(1000);
		pthread_mutex_lock(&(forks[rightIdx]));
		printf("Philosopher %d status: eating for %d seconds.\n", *myID, EAT_TIME);
		sleep(EAT_TIME);
		pthread_mutex_unlock(&(forks[leftIdx]));
		pthread_mutex_unlock(&(forks[rightIdx]));
		printf("Philosopher %d status: thinking for %d seconds.\n", *myID, THINK_TIME);
	}

	pthread_exit(0);
}

void *philosopher_good(void *param) {

	int *myID;
	myID = (int *) param;

	int leftIdx = *myID;
	int rightIdx = (*myID + 1) % NUM_PHILOSOPHERS;
	printf("Philosopher %d starting:\n", *myID);

	while ( 1 ) {

		sem_wait(&diningSemaphore);

		pthread_mutex_lock(&(forks[leftIdx]));
		usleep(1000);
		pthread_mutex_lock(&(forks[rightIdx]));
		printf("Philosopher %d status: eating for %d seconds.\n", *myID, EAT_TIME);
		sleep(EAT_TIME);
		pthread_mutex_unlock(&(forks[leftIdx]));
		pthread_mutex_unlock(&(forks[rightIdx]));
		printf("Philosopher %d status: thinking for %d seconds.\n", *myID, THINK_TIME);

		sem_post(&diningSemaphore);
		usleep(1000);

	}

	pthread_exit(0);
}

int main() {

	int placeholder = 0;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	int id[NUM_PHILOSOPHERS];
	pthread_t tid[NUM_PHILOSOPHERS];

	sem_init(&diningSemaphore, 0, SEMAPHORE_COUNT);

	int i;

	// Part I: Create threads for incorrect function:
/*	for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
		id[i] = i;
		pthread_create(&(tid[i]), &attr, philosopher, &(id[i]));
	}
*/
	// Part II: Create threads for correct function:
	for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
		id[i] = i;
		pthread_create(&(tid[i]), &attr, philosopher_good, &(id[i]));
	}

	// Sleep for 10 seconds and kill processes afterward:
	sleep(RUNTIME);
	for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
		pthread_kill(tid[i], NULL);
	}

	sem_destroy(&diningSemaphore);

	return(0);
}
