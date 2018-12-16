#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.patempes.h"
#include "pqueue_test_1.c"
#include "pqueue_test_2.c"
#include "pqueue_more_tests.c"

int main() {
	pqueue_test_1();
	pqueue_test_2();
	pqueue_test_3();
	pqueue_test_4();
	return(0);
}
