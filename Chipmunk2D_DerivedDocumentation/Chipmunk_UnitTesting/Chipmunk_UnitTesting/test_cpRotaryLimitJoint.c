
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpRotaryLimitJoint.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1, *body2;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpRotaryLimitJointSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpRotaryLimitJointSuite(void)
{
	return 0;
}

/* Simple test of cpConstraintIsRotaryLimitJoint().
*/
void test_cpConstraintIsRotaryLimitJoint(void)
{
	cpConstraint *isRotaryLimit = cpRotaryLimitJointNew(body1, body2, 1, 1);
	cpConstraint *isNotRotaryLimit = cpGearJointNew(body1, body2, 1, 1);

	CU_ASSERT(cpConstraintIsRotaryLimitJoint(isRotaryLimit));
	CU_ASSERT_FALSE(cpConstraintIsRotaryLimitJoint(isNotRotaryLimit));
}


/* Simple test of cpRotaryLimitJointGetMin().
*/
void test_cpRotaryLimitJointGetMin(void)
{
	cpConstraint *rotary1 = cpRotaryLimitJointNew(body1, body2, 5, 1);
	cpConstraint *rotary2 = cpRotaryLimitJointNew(body1, body2, -6.14, 1);
	cpConstraint *rotary3 = cpRotaryLimitJointNew(body1, body2, 14.26, 1);
	cpConstraint *rotary4 = cpRotaryLimitJointNew(body1, body2, 0, 1);

	CU_ASSERT(cpRotaryLimitJointGetMin(rotary1) == 5);
	CU_ASSERT(cpRotaryLimitJointGetMin(rotary2) == -6.14);
	CU_ASSERT(cpRotaryLimitJointGetMin(rotary3) == 14.26);
	CU_ASSERT(cpRotaryLimitJointGetMin(rotary4) == 0);
}


/* Simple test of cpRotaryLimitJointSetMin().
*/
void test_cpRotaryLimitJointSetMin(void)
{
	cpConstraint *rotary1 = cpRotaryLimitJointNew(body1, body2, 5, 1);

	cpRotaryLimitJointSetMin(rotary1, 56.42);
	CU_ASSERT(((cpRotaryLimitJoint *)rotary1)->min == 56.42);

	cpRotaryLimitJointSetMin(rotary1, -58.7);
	CU_ASSERT(((cpRotaryLimitJoint *)rotary1)->min == -58.7);

	cpRotaryLimitJointSetMin(rotary1, 17);
	CU_ASSERT(((cpRotaryLimitJoint *)rotary1)->min == 17);

	cpRotaryLimitJointSetMin(rotary1, 0);
	CU_ASSERT(((cpRotaryLimitJoint *)rotary1)->min == 0);
}


/* Simple test of cpRotaryLimitJointGetMax().
*/
void test_cpRotaryLimitJointGetMax(void)
{
	cpConstraint *rotary1 = cpRotaryLimitJointNew(body1, body2, 5, 49);
	cpConstraint *rotary2 = cpRotaryLimitJointNew(body1, body2, -6.14, -101.6);
	cpConstraint *rotary3 = cpRotaryLimitJointNew(body1, body2, 14.26, 82.36);
	cpConstraint *rotary4 = cpRotaryLimitJointNew(body1, body2, 0, 0);

	CU_ASSERT(cpRotaryLimitJointGetMax(rotary1) == 49);
	CU_ASSERT(cpRotaryLimitJointGetMax(rotary2) == -101.6);
	CU_ASSERT(cpRotaryLimitJointGetMax(rotary3) == 82.36);
	CU_ASSERT(cpRotaryLimitJointGetMax(rotary4) == 0);
}

/* Simple test of cpRotaryLimitJointSetMax().
*/
void test_cpRotaryLimitJointSetMax(void)
{
	cpConstraint *rotary1 = cpRotaryLimitJointNew(body1, body2, 5, 1);

	cpRotaryLimitJointSetMax(rotary1, 119.20);
	CU_ASSERT(((cpRotaryLimitJoint *)rotary1)->max == 119.20);

	cpRotaryLimitJointSetMax(rotary1, -4.7);
	CU_ASSERT(((cpRotaryLimitJoint *)rotary1)->max == -4.7);

	cpRotaryLimitJointSetMax(rotary1, 45);
	CU_ASSERT(((cpRotaryLimitJoint *)rotary1)->max == 45);

	cpRotaryLimitJointSetMax(rotary1, 0);
	CU_ASSERT(((cpRotaryLimitJoint *)rotary1)->max == 0);
}

