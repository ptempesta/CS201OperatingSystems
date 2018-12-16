# CS201OperatingSystems
This is a collection of C code and programs I developed and compiled remotely on a Linux server as part of a course on operating systems.

In order:

CPUScheduler.patempes.c is the first stage of a CPU scheduler simulation which submits several pre-set processes and operates on them on a first-come-first-serve basis as well as on a shortest-job-first basis. Updates are given on process status of completion. CPUScheduler.patempes.wprofcode.c is the third stage of the simulator. For this, I added random process creation and round-robin scheduling on top of my professor's base code.

DP.patempes.c is a solution to the dining philosophers problem with mutexes and semaphores.

dlist.patempes.c and dlist.patempes.h are an implementation of doubly-linked lists. At the time, I did not understand that pointers in C must be explicitly initialized as NULL before being used, so this implementation results in segmentation faults.

pqueue.main.c, pqueue.patempes.c, pqueue.patempes.h, pqueue_more_tests.c, pqueue_test_1.c and pqueue_test_2.c are an implementation of priority queues as well as several test files and a main file.

slist.patempes.c and slist.patempes.h are an implementation of singly-linked lists. This implementation suffers from the same pointer issue which dlist.patempes.c and dlist.patempes.h suffer from.

Finally, sorter.patempes.c is a simulation of multithreaded sorting of values.
