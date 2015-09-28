
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpPinJoint.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1, *body2;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpPinJointSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpPinJointSuite(void)
{
	return 0;
}

/* Simple test of cpConstraintIsPinJoint().
*/
void test_cpConstraintIsPinJoint(void)
{
	cpConstraint *isPin= cpPinJointNew(body1, body2, cpv(0, 0), cpv(0, 0));
	cpConstraint *isNotPin = cpGearJointNew(body1, body2, 1, 1);

	CU_ASSERT(cpConstraintIsPinJoint(isPin));
	CU_ASSERT_FALSE(cpConstraintIsPinJoint(isNotPin));
}


/* Simple test of cpPinJointGetAnchorA().
*/
void test_cpPinJointGetAnchorA(void)
{
	cpConstraint *pin1 = cpPinJointNew(body1, body2, cpv(12.45, 33.9), cpv(0, 0));
	cpConstraint *pin2 = cpPinJointNew(body1, body2, cpv(-1.44, -6.32), cpv(0, 0));
	cpConstraint *pin3 = cpPinJointNew(body1, body2, cpv(0, 0), cpv(0, 0));
	cpConstraint *pin4 = cpPinJointNew(body1, body2, cpv(4, 1), cpv(0, 0));

	cpVect vect = cpPinJointGetAnchorA(pin1);
	CU_ASSERT(vect.x == 12.45 && vect.y == 33.9);

	vect = cpPinJointGetAnchorA(pin2);
	CU_ASSERT(vect.x == -1.44 && vect.y == -6.32);

	vect = cpPinJointGetAnchorA(pin3);
	CU_ASSERT(vect.x == 0 && vect.y == 0);

	vect = cpPinJointGetAnchorA(pin4);
	CU_ASSERT(vect.x == 4 && vect.y == 1);
}


/* Simple test of cpPinJointSetAnchorA().
*/
void test_cpPinJointSetAnchorA(void)
{
	cpConstraint *pin1 = cpPinJointNew(body1, body2, cpv(12.45, 33.9), cpv(0, 0));

	cpPinJointSetAnchorA(pin1, cpv(13.6, 1.14));
	cpPinJoint *pinCast = (cpPinJoint*)pin1;
	CU_ASSERT(pinCast->anchorA.x == 13.6 && pinCast->anchorA.y == 1.14);

	cpPinJointSetAnchorA(pin1, cpv(-85.6, -94.2));
	pinCast = (cpPinJoint*)pin1;
	CU_ASSERT(pinCast->anchorA.x == -85.6 && pinCast->anchorA.y == -94.2);
	
	cpPinJointSetAnchorA(pin1, cpv(17, 44));
	pinCast = (cpPinJoint*)pin1;
	CU_ASSERT(pinCast->anchorA.x == 17 && pinCast->anchorA.y == 44);


}


/* Simple test of cpPinJointGetAnchorB().
*/
void test_cpPinJointGetAnchorB(void)
{
	cpConstraint *pin1 = cpPinJointNew(body1, body2, cpv(12.45, 33.9), cpv(-32.55, -8.4));
	cpConstraint *pin2 = cpPinJointNew(body1, body2, cpv(-1.44, -6.32), cpv(0, 0));
	cpConstraint *pin3 = cpPinJointNew(body1, body2, cpv(0, 0), cpv(2.68, 0.77));
	cpConstraint *pin4 = cpPinJointNew(body1, body2, cpv(4, 1), cpv(2, 5));

	cpVect vect = cpPinJointGetAnchorB(pin1);
	CU_ASSERT(vect.x == -32.55 && vect.y == -8.4);

	vect = cpPinJointGetAnchorB(pin2);
	CU_ASSERT(vect.x == 0 && vect.y == 0);

	vect = cpPinJointGetAnchorB(pin3);
	CU_ASSERT(vect.x == 2.68 && vect.y == 0.77);

	vect = cpPinJointGetAnchorB(pin4);
	CU_ASSERT(vect.x == 2 && vect.y == 5);
}

/* Simple test of cpPinJointSetAnchorB().
*/
void test_cpPinJointSetAnchorB(void)
{
	cpConstraint *pin1 = cpPinJointNew(body1, body2, cpv(12.45, 33.9), cpv(0, 0));

	cpPinJointSetAnchorB(pin1, cpv(84.21, 65.65));
	cpPinJoint *pinCast = (cpPinJoint*)pin1;
	CU_ASSERT(pinCast->anchorB.x == 84.21 && pinCast->anchorB.y == 65.65);

	cpPinJointSetAnchorB(pin1, cpv(-13.3, -71.2));
	pinCast = (cpPinJoint*)pin1;
	CU_ASSERT(pinCast->anchorB.x == -13.3 && pinCast->anchorB.y == -71.2);

	cpPinJointSetAnchorB(pin1, cpv(6, 29));
	pinCast = (cpPinJoint*)pin1;
	CU_ASSERT(pinCast->anchorB.x == 6 && pinCast->anchorB.y == 29);
}


/* Simple test of cpPinJointGetDist().
*/
void test_cpPinJointGetDist(void)
{
	cpConstraint *pin1 = cpPinJointNew(body1, body2, cpv(12.45, 33.9), cpv(-32.55, -8.4));
	
	((cpPinJoint*)pin1)->dist = 18;
	CU_ASSERT(cpPinJointGetDist(pin1) == 18);

	((cpPinJoint*)pin1)->dist = 103.4;
	CU_ASSERT(cpPinJointGetDist(pin1) == 103.4);

	((cpPinJoint*)pin1)->dist = -97.62;
	CU_ASSERT(cpPinJointGetDist(pin1) == -97.62);

	((cpPinJoint*)pin1)->dist = 0;
	CU_ASSERT(cpPinJointGetDist(pin1) == 0);
}

/* Simple test of cpPinJointSetDist().
*/
void test_cpPinJointSetDist(void)
{
	cpConstraint *pin1 = cpPinJointNew(body1, body2, cpv(12.45, 33.9), cpv(-32.55, -8.4));
	
	cpPinJointSetDist(pin1, 3.89);
	CU_ASSERT(((cpPinJoint*)pin1)->dist == 3.89);

	cpPinJointSetDist(pin1, 0);
	CU_ASSERT(((cpPinJoint*)pin1)->dist == 0);

	cpPinJointSetDist(pin1, -4.98);
	CU_ASSERT(((cpPinJoint*)pin1)->dist == -4.98);

	cpPinJointSetDist(pin1, 14);
	CU_ASSERT(((cpPinJoint*)pin1)->dist == 14);
}