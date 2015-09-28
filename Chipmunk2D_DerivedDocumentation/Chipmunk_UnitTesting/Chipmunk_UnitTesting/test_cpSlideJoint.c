
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpSlideJoint.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1, *body2;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpSlideJointSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpSlideJointSuite(void)
{
	return 0;
}

/* Simple test of cpConstraintIsSlideJoint().
*/
void test_cpConstraintIsSlideJoint(void)
{
	cpConstraint *isSlide = cpSlideJointNew(body1, body2, cpv(0, 0), cpv(0, 0),1 ,1);
	cpConstraint *isNotSlide= cpGearJointNew(body1, body2, 1, 1);

	CU_ASSERT(cpConstraintIsSlideJoint(isSlide));
	CU_ASSERT_FALSE(cpConstraintIsSlideJoint(isNotSlide));
}


/* Simple test of cpSlideJointGetAnchorA().
*/
void test_cpSlideJointGetAnchorA(void)
{
	cpConstraint *slide1 = cpSlideJointNew(body1, body2, cpv(14.59 ,12.14), cpv(0, 0), 1, 1);
	cpConstraint *slide2 = cpSlideJointNew(body1, body2, cpv(-55.61, -18.3), cpv(0, 0), 1, 1);
	cpConstraint *slide3 = cpSlideJointNew(body1, body2, cpv(5, 9), cpv(0, 0), 1, 1);
	cpConstraint *slide4 = cpSlideJointNew(body1, body2, cpv(0, 0), cpv(0, 0), 1, 1);

	cpVect vect = cpSlideJointGetAnchorA(slide1);
	CU_ASSERT(vect.x == 14.59 && vect.y == 12.14);

	vect = cpSlideJointGetAnchorA(slide2);
	CU_ASSERT(vect.x == -55.61 && vect.y == -18.3);

	vect = cpSlideJointGetAnchorA(slide3);
	CU_ASSERT(vect.x == 5 && vect.y == 9);

	vect = cpSlideJointGetAnchorA(slide4);
	CU_ASSERT(vect.x == 0 && vect.y == 0);
}


/* Simple test of cpSlideJointSetAnchorA().
*/
void test_cpSlideJointSetAnchorA(void)
{
	cpConstraint *slide1 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 1, 1);

	cpSlideJointSetAnchorA(slide1, cpv(16.14, 85.32));
	cpSlideJoint *slideCast = (cpSlideJoint*)slide1;
	CU_ASSERT(slideCast->anchorA.x == 16.14 && slideCast->anchorA.y == 85.32);

	cpSlideJointSetAnchorA(slide1, cpv(-19.2, -47.1));
	slideCast = (cpSlideJoint*)slide1;
	CU_ASSERT(slideCast->anchorA.x == -19.2 && slideCast->anchorA.y == -47.1);

	cpSlideJointSetAnchorA(slide1, cpv(12, 68));
	slideCast = (cpSlideJoint*)slide1;
	CU_ASSERT(slideCast->anchorA.x == 12 && slideCast->anchorA.y == 68);


}


/* Simple test of cpSlideJointGetAnchorB().
*/
void test_cpSlideJointGetAnchorB(void)
{

	cpConstraint *slide1 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(16.78, 21.3), 1, 1);
	cpConstraint *slide2 = cpSlideJointNew(body1, body2, cpv(-55.61, -18.3), cpv(-4.5, -7.9), 1, 1);
	cpConstraint *slide3 = cpSlideJointNew(body1, body2, cpv(5, 9), cpv(7, 2), 1, 1);
	cpConstraint *slide4 = cpSlideJointNew(body1, body2, cpv(0, 0), cpv(0, 0), 1, 1);

	cpVect vect = cpSlideJointGetAnchorB(slide1);
	CU_ASSERT(vect.x == 16.78 && vect.y == 21.3);

	vect = cpSlideJointGetAnchorB(slide2);
	CU_ASSERT(vect.x == -4.5 && vect.y == -7.9);

	vect = cpSlideJointGetAnchorB(slide3);
	CU_ASSERT(vect.x == 7 && vect.y == 2);

	vect = cpSlideJointGetAnchorB(slide4);
	CU_ASSERT(vect.x == 0 && vect.y == 0);
}

/* Simple test of cpSlideJointSetAnchorB()
*/
void test_cpSlideJointSetAnchorB(void)
{
	cpConstraint *slide1 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 1, 1);

	cpSlideJointSetAnchorB(slide1, cpv(51.62, 125.7));
	cpSlideJoint *slideCast = (cpSlideJoint*)slide1;
	CU_ASSERT(slideCast->anchorB.x == 51.62 && slideCast->anchorB.y == 125.7);

	cpSlideJointSetAnchorB(slide1, cpv(-36.3, -92.4));
	slideCast = (cpSlideJoint*)slide1;
	CU_ASSERT(slideCast->anchorB.x == -36.3 && slideCast->anchorB.y == -92.4);

	cpSlideJointSetAnchorB(slide1, cpv(15, 87));
	slideCast = (cpSlideJoint*)slide1;
	CU_ASSERT(slideCast->anchorB.x == 15 && slideCast->anchorB.y == 87);
}


/* Simple test of cpSlideJointGetMin().
*/
void test_cpSlideJointGetMin(void)
{
	cpConstraint *slide1 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 5, 1);
	cpConstraint *slide2 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 16.8, 1);
	cpConstraint *slide3 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), -25.6, 1);
	cpConstraint *slide4 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 0, 1);

	CU_ASSERT(cpSlideJointGetMin(slide1) == 5);
	CU_ASSERT(cpSlideJointGetMin(slide2) == 16.8);
	CU_ASSERT(cpSlideJointGetMin(slide3) == -25.6);
	CU_ASSERT(cpSlideJointGetMin(slide4) == 0);
}

/* Simple test of cpSlideJointSetMin().
*/
void test_cpSlideJointSetMin(void)
{
	cpConstraint *slide1 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 5, 1);

	cpSlideJointSetMin(slide1, 5.97);
	CU_ASSERT(((cpSlideJoint*)slide1)->min == 5.97);

	cpSlideJointSetMin(slide1, -34.6);
	CU_ASSERT(((cpSlideJoint*)slide1)->min == -34.6);

	cpSlideJointSetMin(slide1, 16);
	CU_ASSERT(((cpSlideJoint*)slide1)->min == 16);

	cpSlideJointSetMin(slide1, 0);
	CU_ASSERT(((cpSlideJoint*)slide1)->min == 0);
}

/* Simple test of cpSlideJointGetMax().
*/
void test_cpSlideJointGetMax(void)
{
	cpConstraint *slide1 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 5, 13);
	cpConstraint *slide2 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 16.8, 37.1);
	cpConstraint *slide3 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), -25.6, -1.7);
	cpConstraint *slide4 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 0, 0);

	CU_ASSERT(cpSlideJointGetMax(slide1) == 13);
	CU_ASSERT(cpSlideJointGetMax(slide2) == 37.1);
	CU_ASSERT(cpSlideJointGetMax(slide3) == -1.7);
	CU_ASSERT(cpSlideJointGetMax(slide4) == 0);
}

/* Simple test of cpSlideJointSetMax().
*/
void test_cpSlideJointSetMax(void)
{
	cpConstraint *slide1 = cpSlideJointNew(body1, body2, cpv(14.59, 12.14), cpv(0, 0), 5, 1);

	cpSlideJointSetMax(slide1, 19.1);
	CU_ASSERT(((cpSlideJoint*)slide1)->max == 19.1);

	cpSlideJointSetMax(slide1, -52.94);
	CU_ASSERT(((cpSlideJoint*)slide1)->max == -52.94);

	cpSlideJointSetMax(slide1, 3);
	CU_ASSERT(((cpSlideJoint*)slide1)->max == 3);

	cpSlideJointSetMax(slide1, 0);
	CU_ASSERT(((cpSlideJoint*)slide1)->max == 0);
}