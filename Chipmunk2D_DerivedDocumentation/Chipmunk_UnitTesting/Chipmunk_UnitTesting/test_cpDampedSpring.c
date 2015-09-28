
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpDampedSpring.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1, *body2;

/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpDampedSpringSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpDampedSpringSuite(void)
{
	return 0;
}


/* Simple test of cpConstraintIsDampedSpring().
*/
void test_cpConstraintIsDampedSpring(void)
{
	cpConstraint *isDampedSpring = cpDampedSpringNew(body1, body2, cpv(0,0), cpv(0,0), 1, 1, 1);
	cpConstraint *isNotDampedSpring = cpGrooveJointNew(body1, body2, cpv(0, 0), cpv(0, 0), cpv(3, 3));

	CU_ASSERT(cpConstraintIsDampedSpring(isDampedSpring));
	CU_ASSERT_FALSE(cpConstraintIsDampedSpring(isNotDampedSpring));
}


/* Simple test of cpDampedSpringGetAnchorA().
*/
void test_cpDampedSpringGetAnchorA(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 1, 1, 1);
	cpConstraint *spring2 = cpDampedSpringNew(body1, body2, cpv(2, 1), cpv(0, 0), 1, 1, 1);
	cpConstraint *spring3 = cpDampedSpringNew(body1, body2, cpv(-29.12, -72.65), cpv(0, 0), 1, 1, 1);
	cpConstraint *spring4 = cpDampedSpringNew(body1, body2, cpv(0, 0), cpv(0, 0), 1, 1, 1);

	cpVect vect = cpDampedSpringGetAnchorA(spring1);
	CU_ASSERT(vect.x == 13.2 && vect.y == 6.54);

	vect = cpDampedSpringGetAnchorA(spring2);
	CU_ASSERT(vect.x == 2 && vect.y == 1);

	vect = cpDampedSpringGetAnchorA(spring3);
	CU_ASSERT(vect.x == -29.12 && vect.y == -72.65);

	vect = cpDampedSpringGetAnchorA(spring4);
	CU_ASSERT(vect.x == 0 && vect.y == 0);
}

/* Simple test of cpDampedSpringSetAnchorA().
*/
void test_cpDampedSpringSetAnchorA(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 1, 1, 1);

	cpDampedSpringSetAnchorA(spring1, cpv(3.52, 11.5));
	cpDampedSpring *springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->anchorA.x == 3.52 && springCast->anchorA.y == 11.5);

	cpDampedSpringSetAnchorA(spring1, cpv(-6.1, -0.69));
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->anchorA.x == -6.1 && springCast->anchorA.y == -0.69);

	cpDampedSpringSetAnchorA(spring1, cpv(41, 22));
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->anchorA.x == 41 && springCast->anchorA.y == 22);
}


/* Simple test of cpDampedSpringGetAnchorB().
*/
void test_cpDampedSpringGetAnchorB(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(12.54, -6.55), 1, 1, 1);
	cpConstraint *spring2 = cpDampedSpringNew(body1, body2, cpv(2, 1), cpv(-4.46, 9.05), 1, 1, 1);
	cpConstraint *spring3 = cpDampedSpringNew(body1, body2, cpv(-29.12, -72.65), cpv(0, 0), 1, 1, 1);
	cpConstraint *spring4 = cpDampedSpringNew(body1, body2, cpv(0, 0), cpv(6, 1), 1, 1, 1);

	cpVect vect = cpDampedSpringGetAnchorB(spring1);
	CU_ASSERT(vect.x == 12.54 && vect.y == -6.55);

	vect = cpDampedSpringGetAnchorB(spring2);
	CU_ASSERT(vect.x == -4.46 && vect.y == 9.05);

	vect = cpDampedSpringGetAnchorB(spring3);
	CU_ASSERT(vect.x == 0 && vect.y == 0);

	vect = cpDampedSpringGetAnchorB(spring4);
	CU_ASSERT(vect.x == 6 && vect.y == 1);
}

/* Simple test of cpDampedSpringSetAnchorB().
*/
void test_cpDampedSpringSetAnchorB(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 1, 1, 1);

	cpDampedSpringSetAnchorB(spring1, cpv(2.11, 19.5));
	cpDampedSpring *springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->anchorB.x == 2.11 && springCast->anchorB.y == 19.5);

	cpDampedSpringSetAnchorB(spring1, cpv(-8.7, -3.65));
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->anchorB.x == -8.7 && springCast->anchorB.y == -3.65);

	cpDampedSpringSetAnchorB(spring1, cpv(-15, 3));
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->anchorB.x == -15 && springCast->anchorB.y == 3);
}


/* Simple test of cpDampedSpringGetRestLength().
*/
void test_cpDampedSpringGetRestLength(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 13, 1, 1);
	CU_ASSERT(cpDampedSpringGetRestLength(spring1) == 13);

	cpConstraint *spring2 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), -0.45, 1, 1);
	CU_ASSERT(cpDampedSpringGetRestLength(spring2) == -0.45);

	cpConstraint *spring3 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 0, 1, 1);
	CU_ASSERT(cpDampedSpringGetRestLength(spring3) == 0);

	cpConstraint *spring4 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 91.65, 1, 1);
	CU_ASSERT(cpDampedSpringGetRestLength(spring4) == 91.65);
}

/* Simple test of cpDampedSpringSetRestLength().
*/
void test_cpDampedSpringSetRestLength(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 13, 1, 1);

	cpDampedSpringSetRestLength(spring1, 60.5);
	cpDampedSpring *springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->restLength == 60.5);

	cpDampedSpringSetRestLength(spring1, -13.2);
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->restLength == -13.2);

	cpDampedSpringSetRestLength(spring1, 9);
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->restLength == 9);
}

/* Simple test of cpDampedSpringGetStiffness().
*/
void test_cpDampedSpringGetStiffness(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 13, 50.48, 1);
	CU_ASSERT(cpDampedSpringGetStiffness(spring1) == 50.48);

	cpConstraint *spring2 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), -0.45, 0, 1);
	CU_ASSERT(cpDampedSpringGetStiffness(spring2) == 0);

	cpConstraint *spring3 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 0, -16.57, 1);
	CU_ASSERT(cpDampedSpringGetStiffness(spring3) == -16.57);

	cpConstraint *spring4 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 91.65, 19, 1);
	CU_ASSERT(cpDampedSpringGetStiffness(spring4) == 19);
}

/* Simple test of cpDampedSpringSetStiffness().
*/
void test_cpDampedSpringSetStiffness(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 13, 50.48, 1);

	cpDampedSpringSetStiffness(spring1, 1.38);
	cpDampedSpring *springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->stiffness == 1.38);

	cpDampedSpringSetStiffness(spring1, -2.74);
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->stiffness == -2.74);

	cpDampedSpringSetStiffness(spring1, 11);
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->stiffness == 11);
}

/* Simple test of cpDampedSpringGetDamping().
*/
void test_cpDampedSpringGetDamping(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 13, 50.48, -15.4);
	CU_ASSERT(cpDampedSpringGetDamping(spring1) == -15.4);

	cpConstraint *spring2 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), -0.45, 0, 63.2);
	CU_ASSERT(cpDampedSpringGetDamping(spring2) == 63.2);

	cpConstraint *spring3 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 0, -16.57, 74);
	CU_ASSERT(cpDampedSpringGetDamping(spring3) == 74);

	cpConstraint *spring4 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 91.65, 19, 0);
	CU_ASSERT(cpDampedSpringGetDamping(spring4) == 0);
}

/* Simple test of cpDampedSpringSetDamping().
*/
void test_cpDampedSpringSetDamping(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 13, 50.48, 1);

	cpDampedSpringSetDamping(spring1, 5.12);
	cpDampedSpring *springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->damping == 5.12);

	cpDampedSpringSetDamping(spring1, -9.4);
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->damping == -9.4);

	cpDampedSpringSetDamping(spring1, -55);
	springCast = (cpDampedSpring*)spring1;
	CU_ASSERT(springCast->damping == -55);
}

static cpFloat
testSpringForce(cpDampedSpring *spring, cpFloat relativeAngle){
	return 0;
}

/* Simple test of cpDampedSpringGetSpringForceFunc().
*/
void test_cpDampedSpringGetSpringForceFunc(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 13, 50.48, 1);
	((cpDampedSpring*)spring1)->springForceFunc = (cpDampedSpringForceFunc)testSpringForce;

	CU_ASSERT(cpDampedSpringGetSpringForceFunc(spring1) == (cpDampedSpringForceFunc)testSpringForce);
}

/* Simple test of cpDampedSpringSetSpringForceFunc().
*/
void test_cpDampedSpringSetSpringForceFunc(void)
{
	cpConstraint *spring1 = cpDampedSpringNew(body1, body2, cpv(13.2, 6.54), cpv(0, 0), 13, 50.48, 1);
	cpDampedSpringSetSpringForceFunc(spring1, (cpDampedSpringForceFunc)testSpringForce);

	CU_ASSERT(((cpDampedSpring*)spring1)->springForceFunc == (cpDampedSpringForceFunc)testSpringForce);

}