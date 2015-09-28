
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpDampedRotarySpring.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1, *body2;

/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpDampedRotarySpringSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpDampedRotarySpringSuite(void)
{
	return 0;
}

/* Simple test of cpConstraintIsDampedRotarySpring().
*/
void test_cpConstraintIsDampedRotarySpring(void)
{
	cpConstraint *isDampedRotarySpring = cpDampedRotarySpringNew(body1, body2, 1, 1,1);
	cpConstraint *isNotDampedRotarySpring = cpGrooveJointNew(body1, body2, cpv(0, 0), cpv(0, 0), cpv(3, 3));

	CU_ASSERT(cpConstraintIsDampedRotarySpring(isDampedRotarySpring));
	CU_ASSERT_FALSE(cpConstraintIsDampedRotarySpring(isNotDampedRotarySpring));
}


/* Simple test of cpDampedRotarySpringGetRestAngle().
*/
void test_cpDampedRotarySpringGetRestAngle(void)
{
	cpConstraint *spring1 = cpDampedRotarySpringNew(body1, body2, 7, 1, 1);
	CU_ASSERT(cpDampedRotarySpringGetRestAngle(spring1) == 7);

	cpConstraint *spring2 = cpDampedRotarySpringNew(body1, body2, -11.7, 1, 1);
	CU_ASSERT(cpDampedRotarySpringGetRestAngle(spring2) == -11.7);

	cpConstraint *spring3 = cpDampedRotarySpringNew(body1, body2, 0, 1, 1);
	CU_ASSERT(cpDampedRotarySpringGetRestAngle(spring3) == 0);

	cpConstraint *spring4 = cpDampedRotarySpringNew(body1, body2, 16.38, 1, 1);
	CU_ASSERT(cpDampedRotarySpringGetRestAngle(spring4) ==16.38);
}

/* Simple test of cpDampedRotarySpringSetRestAngle().
*/
void test_cpDampedRotarySpringSetRestAngle(void)
{
	cpConstraint *spring1 = cpDampedRotarySpringNew(body1, body2, 7, 1, 1);
	
	cpDampedRotarySpringSetRestAngle(spring1, M_PI_2);
	cpDampedRotarySpring *springCast = (cpDampedRotarySpring*)spring1;
	CU_ASSERT(springCast->restAngle == M_PI_2);

	cpDampedRotarySpringSetRestAngle(spring1, -M_PI);
	springCast = (cpDampedRotarySpring*)spring1;
	CU_ASSERT(springCast->restAngle == -M_PI);

	cpDampedRotarySpringSetRestAngle(spring1, 8);
	springCast = (cpDampedRotarySpring*)spring1;
	CU_ASSERT(springCast->restAngle == 8);
}

/* Simple test of cpDampedRotarySpringGetStiffness().
*/
void test_cpDampedRotarySpringGetStiffness(void)
{
	cpConstraint *spring1 = cpDampedRotarySpringNew(body1, body2, 7, 13.7, 1);
	CU_ASSERT(cpDampedRotarySpringGetStiffness(spring1) == 13.7);

	cpConstraint *spring2 = cpDampedRotarySpringNew(body1, body2, -11.7, 8, 1);
	CU_ASSERT(cpDampedRotarySpringGetStiffness(spring2) == 8);

	cpConstraint *spring3 = cpDampedRotarySpringNew(body1, body2, 0, -1.21, 1);
	CU_ASSERT(cpDampedRotarySpringGetStiffness(spring3) == -1.21);

	cpConstraint *spring4 = cpDampedRotarySpringNew(body1, body2, 16.38, 0, 1);
	CU_ASSERT(cpDampedRotarySpringGetStiffness(spring4) == 0);
}

/* Simple test of cpDampedRotarySpringSetStiffness().
*/
void test_cpDampedRotarySpringSetStiffness(void)
{
	cpConstraint *spring1 = cpDampedRotarySpringNew(body1, body2, 7, 1, 1);

	cpDampedRotarySpringSetStiffness(spring1, 0.778);
	cpDampedRotarySpring *springCast = (cpDampedRotarySpring*)spring1;
	CU_ASSERT(springCast->stiffness == 0.778);

	cpDampedRotarySpringSetStiffness(spring1, -14.28);
	springCast = (cpDampedRotarySpring*)spring1;
	CU_ASSERT(springCast->stiffness == -14.28);

	cpDampedRotarySpringSetStiffness(spring1, 31);
	springCast = (cpDampedRotarySpring*)spring1;
	CU_ASSERT(springCast->stiffness == 31);
}

/* Simple test of cpDampedRotarySpringGetDamping().
*/
void test_cpDampedRotarySpringGetDamping(void)
{
	cpConstraint *spring1 = cpDampedRotarySpringNew(body1, body2, 7, 13.7, -2.36);
	CU_ASSERT(cpDampedRotarySpringGetDamping(spring1) == -2.36);

	cpConstraint *spring2 = cpDampedRotarySpringNew(body1, body2, -11.7, 8, 0);
	CU_ASSERT(cpDampedRotarySpringGetDamping(spring2) == 0);

	cpConstraint *spring3 = cpDampedRotarySpringNew(body1, body2, 0, -1.21, 15);
	CU_ASSERT(cpDampedRotarySpringGetDamping(spring3) == 15);

	cpConstraint *spring4 = cpDampedRotarySpringNew(body1, body2, 16.38, 0, 6.95);
	CU_ASSERT(cpDampedRotarySpringGetDamping(spring4) == 6.95);
}

/* Simple test of cpDampedRotarySpringSetDamping().
*/
void test_cpDampedRotarySpringSetDamping(void)
{
	cpConstraint *spring1 = cpDampedRotarySpringNew(body1, body2, 7, 1, 1);

	cpDampedRotarySpringSetDamping(spring1, 54.36);
	cpDampedRotarySpring *springCast = (cpDampedRotarySpring*)spring1;
	CU_ASSERT(springCast->damping == 54.36);

	cpDampedRotarySpringSetDamping(spring1, -89.11);
	springCast = (cpDampedRotarySpring*)spring1;
	CU_ASSERT(springCast->damping == -89.11);

	cpDampedRotarySpringSetDamping(spring1, 12);
	springCast = (cpDampedRotarySpring*)spring1;
	CU_ASSERT(springCast->damping == 12);
}

static cpFloat
testSpringTorque(cpDampedRotarySpring *spring, cpFloat relativeAngle){
	return 0;
}

/* Simple test of cpDampedRotarySpringGetSpringTorqueFunc().
*/
void test_cpDampedRotarySpringGetSpringTorqueFunc(void)
{
	cpConstraint *spring1 = cpDampedRotarySpringNew(body1, body2, 7, 13.7, -2.36);
	((cpDampedRotarySpring*)spring1)->springTorqueFunc = (cpDampedRotarySpringTorqueFunc)testSpringTorque;

	CU_ASSERT(cpDampedRotarySpringGetSpringTorqueFunc(spring1) == (cpDampedRotarySpringTorqueFunc)testSpringTorque);
}

/* Simple test of cpDampedRotarySpringSetSpringTorqueFunc().
*/
void test_cpDampedRotarySpringSetSpringTorqueFunc(void)
{
	cpConstraint *spring1 = cpDampedRotarySpringNew(body1, body2, 7, 1, 1);
	cpDampedRotarySpringSetSpringTorqueFunc(spring1, (cpDampedRotarySpringTorqueFunc)testSpringTorque);

	CU_ASSERT(((cpDampedRotarySpring*)spring1)->springTorqueFunc == (cpDampedRotarySpringTorqueFunc)testSpringTorque);

}