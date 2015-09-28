
#include <stdio.h>
#include "CUnit/Console.h"
#include "chipmunk\chipmunk.h"

#include "chipmunk\cpArbiter_private.h"
#include "test_cpArbiter.h"

#define diff 0.0001

cpArbiter *arbiter1, *arbiter2;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpArbiterSuite(void)
{
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpArbiterSuite(void)
{
	return 0;
}

/* Simple test of cpMomentForCircle().
*/
void test_cpArbiterIsFirstContact(void)
{
	
}

