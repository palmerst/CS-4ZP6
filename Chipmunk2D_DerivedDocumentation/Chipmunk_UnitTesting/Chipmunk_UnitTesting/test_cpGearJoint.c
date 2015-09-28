
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpGearJoint.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001


static cpBody *body1, *body2;

/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpGearJointSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpGearJointSuite(void)
{
	return 0;
}


/* Simple test of cpConstraintIsGearJoint().
*/
void test_cpConstraintIsGearJoint(void)
{
	cpConstraint *isGear = cpGearJointNew(body1, body2, 1, 1); 
	cpConstraint *isNotGear = cpGrooveJointNew(body1, body2, cpv(0, 0), cpv(0, 0), cpv(3, 3));

	CU_ASSERT(cpConstraintIsGearJoint(isGear));
	CU_ASSERT_FALSE(cpConstraintIsGearJoint(isNotGear));
}

/* Simple test of cpGearJointGetPhase().
*/
void test_cpGearJointGetPhase(void)
{
	cpConstraint *gear1 = cpGearJointNew(body1, body2, 4, 7);
	CU_ASSERT(cpGearJointGetPhase(gear1)==4);

	cpConstraint *gear2 = cpGearJointNew(body1, body2, -12.7, 7);
	CU_ASSERT(cpGearJointGetPhase(gear2) == -12.7);

	cpConstraint *gear3 = cpGearJointNew(body1, body2, 0, 7);
	CU_ASSERT(cpGearJointGetPhase(gear3) == 0);

	cpConstraint *gear4 = cpGearJointNew(body1, body2, 98.5, 7);
	CU_ASSERT(cpGearJointGetPhase(gear4) == 98.5);
}

/* Simple test of cpGearJointSetPhase().
*/
void test_cpGearJointSetPhase(void)
{
	cpConstraint *gear1 = cpGearJointNew(body1, body2, 4, 7);
	
	cpGearJointSetPhase(gear1, 5.87);
	cpGearJoint *gearCast = (cpGearJoint*)gear1;
	CU_ASSERT(gearCast->phase == 5.87);

	cpGearJointSetPhase(gear1, -18.3);
	gearCast = (cpGearJoint*)gear1;
	CU_ASSERT(gearCast->phase == -18.3);

	cpGearJointSetPhase(gear1, 19);
	gearCast = (cpGearJoint*)gear1;
	CU_ASSERT(gearCast->phase == 19);
}

/* Simple test of cpGearJointGetRatio().
*/
void test_cpGearJointGetRatio(void)
{
	cpConstraint *gear1 = cpGearJointNew(body1, body2, 4, -2);
	CU_ASSERT(cpGearJointGetRatio(gear1) == -2);

	cpConstraint *gear2 = cpGearJointNew(body1, body2, -12.7, 17.59);
	CU_ASSERT(cpGearJointGetRatio(gear2) == 17.59);

	cpConstraint *gear3 = cpGearJointNew(body1, body2, 0, -36.8);
	CU_ASSERT(cpGearJointGetRatio(gear3) == -36.8);

	cpConstraint *gear4 = cpGearJointNew(body1, body2, 98.5, 0);
	CU_ASSERT(cpGearJointGetRatio(gear4) == 0);
}

/* Simple test of cpGearJointSetRatio().
*/
void test_cpGearJointSetRatio(void)
{
	cpConstraint *gear1 = cpGearJointNew(body1, body2, 4, 7);

	cpGearJointSetRatio(gear1, 63.25);
	cpGearJoint *gearCast = (cpGearJoint*)gear1;
	CU_ASSERT(gearCast->ratio == 63.25);

	cpGearJointSetRatio(gear1, -7.14);
	gearCast = (cpGearJoint*)gear1;
	CU_ASSERT(gearCast->ratio == -7.14);

	cpGearJointSetRatio(gear1, 92);
	gearCast = (cpGearJoint*)gear1;
	CU_ASSERT(gearCast->ratio == 92);
}