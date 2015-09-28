
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpGrooveJoint.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1, *body2;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpGrooveJointSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpGrooveJointSuite(void)
{
	return 0;
}

/* Simple test of cpConstraintIsGrooveJoint().
*/
void test_cpConstraintIsGrooveJoint(void)
{
	cpConstraint *isGroove = cpGrooveJointNew(body1, body2, cpv(0, 0), cpv(0, 0), cpv(3, 3));
	cpConstraint *isNotGroove = cpGearJointNew(body1, body2, 1,1);

	CU_ASSERT(cpConstraintIsGrooveJoint(isGroove));
	CU_ASSERT_FALSE(cpConstraintIsGrooveJoint(isNotGroove));
}


/* Simple test of cpGrooveJointGetGrooveA().
*/
void test_cpGrooveJointGetGrooveA(void)
{
	cpConstraint *groove1 = cpGrooveJointNew(body1, body2, cpv(50, 100), cpv(0, 0), cpv(3, 3));
	cpConstraint *groove2 = cpGrooveJointNew(body1, body2, cpv(3.2, 15.7), cpv(0, 0), cpv(3, 3));
	cpConstraint *groove3 = cpGrooveJointNew(body1, body2, cpv(-2.5, -7.8), cpv(0, 0), cpv(3, 3));
	cpConstraint *groove4 = cpGrooveJointNew(body1, body2, cpv(0, 0), cpv(0, 0), cpv(3, 3));

	cpVect vect = cpGrooveJointGetGrooveA(groove1);
	CU_ASSERT(vect.x==50 && vect.y==100);

	vect = cpGrooveJointGetGrooveA(groove2);
	CU_ASSERT(vect.x == 3.2 && vect.y == 15.7);

	vect = cpGrooveJointGetGrooveA(groove3);
	CU_ASSERT(vect.x == -2.5 && vect.y == -7.8);

	vect = cpGrooveJointGetGrooveA(groove4);
	CU_ASSERT(vect.x == 0 && vect.y == 0);

}


/* Simple test of cpGrooveJointSetGrooveA().
*/
void test_cpGrooveJointSetGrooveA(void)
{
	cpConstraint *groove1 = cpGrooveJointNew(body1, body2, cpv(50, 100), cpv(0, 0), cpv(3, 3));

	cpGrooveJointSetGrooveA(groove1, cpv(7.6, 5.4));
	cpGrooveJoint *grooveCast = (cpGrooveJoint*)groove1;
	CU_ASSERT(grooveCast->grv_a.x == 7.6 && grooveCast->grv_a.y == 5.4);

	cpGrooveJointSetGrooveA(groove1, cpv(2, -4));
	grooveCast = (cpGrooveJoint*)groove1;
	CU_ASSERT(grooveCast->grv_a.x == 2 && grooveCast->grv_a.y == -4);

	cpGrooveJointSetGrooveA(groove1, cpv(-26.9, 65.7));
	grooveCast = (cpGrooveJoint*)groove1;
	CU_ASSERT(grooveCast->grv_a.x == -26.9 && grooveCast->grv_a.y == 65.7);
	 
}


/* Simple test of cpGrooveJointGetGrooveB().
*/
void test_cpGrooveJointGetGrooveB(void)
{
	cpConstraint *groove1 = cpGrooveJointNew(body1, body2, cpv(50, 100), cpv(-4.89, 1.78), cpv(3, 3));
	cpConstraint *groove2 = cpGrooveJointNew(body1, body2, cpv(3.2, 15.7), cpv(3, -5), cpv(3, 3));
	cpConstraint *groove3 = cpGrooveJointNew(body1, body2, cpv(-2.5, -7.8), cpv(0, 0), cpv(3, 3));
	cpConstraint *groove4 = cpGrooveJointNew(body1, body2, cpv(0, 0), cpv(9.86, -2.71), cpv(3, 3));

	cpVect vect = cpGrooveJointGetGrooveB(groove1);
	CU_ASSERT(vect.x == -4.89 && vect.y == 1.78);

	vect = cpGrooveJointGetGrooveB(groove2);
	CU_ASSERT(vect.x == 3 && vect.y == -5);

	vect = cpGrooveJointGetGrooveB(groove3);
	CU_ASSERT(vect.x == 0 && vect.y == 0);

	vect = cpGrooveJointGetGrooveB(groove4);
	CU_ASSERT(vect.x == 9.86 && vect.y == -2.71);
}

/* Simple test of cpGrooveJointSetGrooveB().
*/
void test_cpGrooveJointSetGrooveB(void)
{
	cpConstraint *groove1 = cpGrooveJointNew(body1, body2, cpv(50, 100), cpv(0, 0), cpv(3, 3));

	cpGrooveJointSetGrooveB(groove1, cpv(6.35, 12.46));
	cpGrooveJoint *grooveCast = (cpGrooveJoint*)groove1;
	CU_ASSERT(grooveCast->grv_b.x == 6.35 && grooveCast->grv_b.y == 12.46);

	cpGrooveJointSetGrooveB(groove1, cpv(-8, 11));
	grooveCast = (cpGrooveJoint*)groove1;
	CU_ASSERT(grooveCast->grv_b.x == -8 && grooveCast->grv_b.y == 11);

	cpGrooveJointSetGrooveB(groove1, cpv(-5.43, -14.26));
	grooveCast = (cpGrooveJoint*)groove1;
	CU_ASSERT(grooveCast->grv_b.x == -5.43 && grooveCast->grv_b.y == -14.26);
}


/* Simple test of cpGrooveJointGetAnchorB().
*/
void test_cpGrooveJointGetAnchorB(void)
{
	cpConstraint *groove1 = cpGrooveJointNew(body1, body2, cpv(50, 100), cpv(-4.89, 1.78), cpv(37.71, 25.86));
	cpConstraint *groove2 = cpGrooveJointNew(body1, body2, cpv(3.2, 15.7), cpv(3, -5), cpv(0, 0));
	cpConstraint *groove3 = cpGrooveJointNew(body1, body2, cpv(-2.5, -7.8), cpv(0, 0), cpv(5, -2));
	cpConstraint *groove4 = cpGrooveJointNew(body1, body2, cpv(0, 0), cpv(9.86, -2.71), cpv(-8.65, 4.91));

	cpVect vect = cpGrooveJointGetAnchorB(groove1);
	CU_ASSERT(vect.x == 37.71 && vect.y == 25.86);

	vect = cpGrooveJointGetAnchorB(groove2);
	CU_ASSERT(vect.x == 0 && vect.y == 0);

	vect = cpGrooveJointGetAnchorB(groove3);
	CU_ASSERT(vect.x == 5 && vect.y == -2);

	vect = cpGrooveJointGetAnchorB(groove4);
	CU_ASSERT(vect.x == -8.65 && vect.y == 4.91);
}

/* Simple test of cpGrooveJointSetAnchorB().
*/
void test_cpGrooveJointSetAnchorB(void)
{
	cpConstraint *groove1 = cpGrooveJointNew(body1, body2, cpv(50, 100), cpv(0, 0), cpv(3, 3));

	cpGrooveJointSetAnchorB(groove1, cpv(16.59, 13.45));
	cpGrooveJoint *grooveCast = (cpGrooveJoint*)groove1;
	CU_ASSERT(grooveCast->anchorB.x == 16.59 && grooveCast->anchorB.y == 13.45);

	cpGrooveJointSetAnchorB(groove1, cpv(19, -23));
	grooveCast = (cpGrooveJoint*)groove1;
	CU_ASSERT(grooveCast->anchorB.x == 19 && grooveCast->anchorB.y == -23);

	cpGrooveJointSetAnchorB(groove1, cpv(-6.81, -0.27));
	grooveCast = (cpGrooveJoint*)groove1;
	CU_ASSERT(grooveCast->anchorB.x == -6.81 && grooveCast->anchorB.y == -0.27);
}