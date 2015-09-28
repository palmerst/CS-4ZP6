
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpRatchetJoint.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1, *body2;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpRatchetJointSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpRatchetJointSuite(void)
{
	return 0;
}

/* Simple test of cpConstraintIsRatchetJoint().
*/
void test_cpConstraintIsRatchetJoint(void)
{
	cpConstraint *isRatchet = cpRatchetJointNew(body1, body2, 1,1);
	cpConstraint *isNotRatchet = cpGearJointNew(body1, body2, 1, 1);

	CU_ASSERT(cpConstraintIsRatchetJoint(isRatchet));
	CU_ASSERT_FALSE(cpConstraintIsRatchetJoint(isNotRatchet));
}


/* Simple test of cpRatchetJointGetAngle().
*/
void test_cpRatchetJointGetAngle(void)
{
	cpConstraint *ratchet1 = cpRatchetJointNew(body1, body2, 1, 1);
	
	((cpRatchetJoint *)ratchet1)->angle = 25;
	CU_ASSERT(cpRatchetJointGetAngle(ratchet1) == 25);

	((cpRatchetJoint *)ratchet1)->angle = -45.23;
	CU_ASSERT(cpRatchetJointGetAngle(ratchet1) == -45.23);

	((cpRatchetJoint *)ratchet1)->angle = 262.3;
	CU_ASSERT(cpRatchetJointGetAngle(ratchet1) == 262.3);

	((cpRatchetJoint *)ratchet1)->angle = 0;
	CU_ASSERT(cpRatchetJointGetAngle(ratchet1) == 0);
}


/* Simple test of cpRatchetJointSetAngle().
*/
void test_cpRatchetJointSetAngle(void)
{
	cpConstraint *ratchet1 = cpRatchetJointNew(body1, body2, 1, 1);

	cpRatchetJointSetAngle(ratchet1, 105.7);
	CU_ASSERT(((cpRatchetJoint *)ratchet1)->angle == 105.7);

	cpRatchetJointSetAngle(ratchet1, -36.1);
	CU_ASSERT(((cpRatchetJoint *)ratchet1)->angle == -36.1);

	cpRatchetJointSetAngle(ratchet1, 12);
	CU_ASSERT(((cpRatchetJoint *)ratchet1)->angle == 12);

	cpRatchetJointSetAngle(ratchet1, 0);
	CU_ASSERT(((cpRatchetJoint *)ratchet1)->angle == 0);
}


/* Simple test of cpRatchetJointGetPhase().
*/
void test_cpRatchetJointGetPhase(void)
{
	cpConstraint *ratchet1 = cpRatchetJointNew(body1, body2, 42, 1);
	cpConstraint *ratchet2 = cpRatchetJointNew(body1, body2, -7.41, 1);
	cpConstraint *ratchet3 = cpRatchetJointNew(body1, body2, 51.23, 1);
	cpConstraint *ratchet4 = cpRatchetJointNew(body1, body2, 0, 1);

	CU_ASSERT(cpRatchetJointGetPhase(ratchet1) == 42 );
	CU_ASSERT(cpRatchetJointGetPhase(ratchet2) == -7.41);
	CU_ASSERT(cpRatchetJointGetPhase(ratchet3) == 51.23);
	CU_ASSERT(cpRatchetJointGetPhase(ratchet4) == 0);
}

/* Simple test of cpRatchetJointSetPhase().
*/
void test_cpRatchetJointSetPhase(void)
{
	cpConstraint *ratchet1 = cpRatchetJointNew(body1, body2, 42, 1);

	cpRatchetJointSetPhase(ratchet1, 112.1);
	cpRatchetJoint *ratchetCast = (cpRatchetJoint*)ratchet1;
	CU_ASSERT(ratchetCast->phase == 112.1);
	
	cpRatchetJointSetPhase(ratchet1, -65.32);
	ratchetCast = (cpRatchetJoint*)ratchet1;
	CU_ASSERT(ratchetCast->phase == -65.32);

	cpRatchetJointSetPhase(ratchet1, 28);
	 ratchetCast = (cpRatchetJoint*)ratchet1;
	CU_ASSERT(ratchetCast->phase == 28);
}


/* Simple test of cpRatchetJointGetRatchet().
*/
void test_cpRatchetJointGetRatchet(void)
{
	cpConstraint *ratchet1 = cpRatchetJointNew(body1, body2, 42, 16);
	cpConstraint *ratchet2 = cpRatchetJointNew(body1, body2, -7.41, -0.89);
	cpConstraint *ratchet3 = cpRatchetJointNew(body1, body2, 51.23, 11.95);
	cpConstraint *ratchet4 = cpRatchetJointNew(body1, body2, 0, 0);

	CU_ASSERT(cpRatchetJointGetRatchet(ratchet1) == 16);
	CU_ASSERT(cpRatchetJointGetRatchet(ratchet2) == -0.89);
	CU_ASSERT(cpRatchetJointGetRatchet(ratchet3) == 11.95);
	CU_ASSERT(cpRatchetJointGetRatchet(ratchet4) == 0);
}

/* Simple test of cpRatchetJointSetRatchet().
*/
void test_cpRatchetJointSetRatchet(void)
{
	cpConstraint *ratchet1 = cpRatchetJointNew(body1, body2, 42, 1);

	cpRatchetJointSetRatchet(ratchet1, 58.12);
	cpRatchetJoint *ratchetCast = (cpRatchetJoint*)ratchet1;
	CU_ASSERT(ratchetCast->ratchet == 58.12);

	cpRatchetJointSetRatchet(ratchet1, -364.1);
	ratchetCast = (cpRatchetJoint*)ratchet1;
	CU_ASSERT(ratchetCast->ratchet == -364.1);

	cpRatchetJointSetRatchet(ratchet1, 74);
	ratchetCast = (cpRatchetJoint*)ratchet1;
	CU_ASSERT(ratchetCast->ratchet == 74);
}

