
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpPivotJoint.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1, *body2;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpPivotJointSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpPivotJointSuite(void)
{
	return 0;
}

/* Simple test of cpConstraintIsPivotJoint().
*/
void test_cpConstraintIsPivotJoint(void)
{
	cpConstraint *isPivot = cpPivotJointNew(body1, body2, cpv(0, 0));
	cpConstraint *isNotPivot = cpGearJointNew(body1, body2, 1, 1);

	CU_ASSERT(cpConstraintIsPivotJoint(isPivot));
	CU_ASSERT_FALSE(cpConstraintIsPivotJoint(isNotPivot));
}


/* Simple test of cpPivotJointGetAnchorA().
*/
void test_cpPivotJointGetAnchorA(void)
{
	cpConstraint *pivot1 = cpPivotJointNew2(body1, body2, cpv(36.5, 41.7),cpv(0,0));
	cpConstraint *pivot2 = cpPivotJointNew2(body1, body2, cpv(-95.6, -113.2), cpv(0, 0));
	cpConstraint *pivot3 = cpPivotJointNew2(body1, body2, cpv(0, 0), cpv(0, 0));
	cpConstraint *pivot4 = cpPivotJointNew2(body1, body2, cpv(5, 4), cpv(0, 0));

	cpVect vect = cpPivotJointGetAnchorA(pivot1);
	CU_ASSERT(vect.x == 36.5 && vect.y == 41.7);

	vect = cpPivotJointGetAnchorA(pivot2);
	CU_ASSERT(vect.x == -95.6 && vect.y == -113.2);

	vect = cpPivotJointGetAnchorA(pivot3);
	CU_ASSERT(vect.x == 0 && vect.y == 0);

	vect = cpPivotJointGetAnchorA(pivot4);
	CU_ASSERT(vect.x == 5 && vect.y == 4);
}


/* Simple test of cpPivotJointSetAnchorA().
*/
void test_cpPivotJointSetAnchorA(void)
{
	cpConstraint *pivot1 = cpPivotJointNew2(body1, body2, cpv(36.5, 41.7), cpv(0, 0));

	cpPivotJointSetAnchorA(pivot1, cpv(55.9, 40.6));
	cpPivotJoint *pivotCast = (cpPivotJoint*)pivot1;
	CU_ASSERT(pivotCast->anchorA.x == 55.9 && pivotCast->anchorA.y == 40.6);

	cpPivotJointSetAnchorA(pivot1, cpv(-36.8, -12.5));
	pivotCast = (cpPivotJoint*)pivot1;
	CU_ASSERT(pivotCast->anchorA.x == -36.8 && pivotCast->anchorA.y == -12.5);

	cpPivotJointSetAnchorA(pivot1, cpv(15, 25));
	pivotCast = (cpPivotJoint*)pivot1;
	CU_ASSERT(pivotCast->anchorA.x == 15 && pivotCast->anchorA.y == 25);

}


/* Simple test of cpPivotJointGetAnchorB().
*/
void test_cpPivotJointGetAnchorB(void)
{
	cpConstraint *pivot1 = cpPivotJointNew2(body1, body2, cpv(36.5, 41.7), cpv(0, 0));
	cpConstraint *pivot2 = cpPivotJointNew2(body1, body2, cpv(-95.6, -113.2), cpv(13, 77));
	cpConstraint *pivot3 = cpPivotJointNew2(body1, body2, cpv(0, 0), cpv(-62.7, -3.08));
	cpConstraint *pivot4 = cpPivotJointNew2(body1, body2, cpv(5, 4), cpv(18.12, 66.4));

	cpVect vect = cpPivotJointGetAnchorB(pivot1);
	CU_ASSERT(vect.x == 0 && vect.y == 0);

	vect = cpPivotJointGetAnchorB(pivot2);
	CU_ASSERT(vect.x == 13 && vect.y == 77);

	vect = cpPivotJointGetAnchorB(pivot3);
	CU_ASSERT(vect.x == -62.7 && vect.y == -3.08);

	vect = cpPivotJointGetAnchorB(pivot4);
	CU_ASSERT(vect.x == 18.12 && vect.y == 66.4);
}

/* Simple test of cpPivotJointSetAnchorB().
*/
void test_cpPivotJointSetAnchorB(void)
{
	cpConstraint *pivot1 = cpPivotJointNew2(body1, body2, cpv(36.5, 41.7), cpv(0, 0));

	cpPivotJointSetAnchorB(pivot1, cpv(13.58, 27.5));
	cpPivotJoint *pivotCast = (cpPivotJoint*)pivot1;
	CU_ASSERT(pivotCast->anchorB.x == 13.58 && pivotCast->anchorB.y == 27.5);

	cpPivotJointSetAnchorB(pivot1, cpv(-48.25, -2.8));
	pivotCast = (cpPivotJoint*)pivot1;
	CU_ASSERT(pivotCast->anchorB.x == -48.25 && pivotCast->anchorB.y == -2.8);

	cpPivotJointSetAnchorB(pivot1, cpv(71, 94));
	pivotCast = (cpPivotJoint*)pivot1;
	CU_ASSERT(pivotCast->anchorB.x == 71 && pivotCast->anchorB.y == 94);
}

