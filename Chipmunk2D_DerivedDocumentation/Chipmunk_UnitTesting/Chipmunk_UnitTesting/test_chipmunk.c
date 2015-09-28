
#include "CUnit/Automated.h"
#include "chipmunk/chipmunk.h"

#include "test_chipmunk.h"
#define diff 0.0001


/* Simple test of cpMomentForCircle().
*/
void test_cpMomentForCircle(void)
{
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForCircle(1.31, 2.11, 4.2, cpv(1, 1)), 17.0903255, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForCircle(3, 1.49, 3.7, cpv(2.2, 5.71)), 136.19745, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForCircle(1.22, 0.11, 2.67, cpv(-1.6, 0.45)), 7.72626, diff);
	CU_ASSERT_EQUAL(cpMomentForCircle(0, 1.2, 7.4, cpv(3.9, -4.1)), 0);

	//Integer test
	CU_ASSERT_EQUAL(cpMomentForCircle(1, 5, 7, cpv(0, 0)), 37);
}

/* Simple test of cpAreaForCircle().
*/
void test_cpAreaForCircle(void)
{
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForCircle(3.2, 1.1), 28.36858166, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForCircle(1.1, 3.2), 28.36858166, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForCircle(1.45, 1.45), 0, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForCircle(-5.62, 4.87), 24.7164802, diff);

	//Integer test
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForCircle(2, 1), 9.424777961, diff);
}


/* Simple test of cpMomentForSegment().
*/
void test_cpMomentForSegment(void)
{
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForSegment(1.1, cpv(2.3, 2.1), cpv(3.41, 1.5), 2), 16.53471193, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForSegment(29.87, cpv(-12.4, 14.7), cpv(-16.98, -3.75), 9.9999), 12124.76751, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForSegment(6.4, cpv(0, 0), cpv(0, 0), 4.53), 87.55584, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForSegment(0, cpv(8.7, -10.6), cpv(13.7, 1.24), 4.5), 0, diff);

	//Zero test
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForSegment(6.4, cpv(0, 0), cpv(0, 0), 0), 0, diff);
	
}

/* Simple test of cpAreaForSegment().
*/
void test_cpAreaForSegment(void)
{
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForSegment(cpv(-3.5, -6.1), cpv(4.55, -2.15), 7.23), 293.8812943, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForSegment(cpv(0, 0), cpv(0, 0), 4.6), 66.47610055, diff);

	//Integer test
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForSegment(cpv(1, 7), cpv(3, 5), 8), 246.3167638, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForSegment(cpv(3.78, 4.46), cpv(1.12, 9.75), 0), 0, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForSegment(cpv(3.78, 4.46), cpv(1.12, 9.75), 0.00002), 0.0002368461848, diff);
}


/* Simple test of cpMomentForPoly().
*/
void test_cpMomentForPoly(void)
{
	cpVect verts2[3] = { cpv(1, 1), cpv(2, 2), cpv(3, 1) };
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForPoly(4, 3, verts2, cpv(1, 1), 2), 58.666666667, diff);

	cpVect verts[4] = { cpv(3.14, -1.21), cpv(4.5, -1.3), cpv(0, 0), cpv(7.89, 13.2) };
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForPoly(3.11, 2, verts, cpv(0, 0), 1), 50.76214567, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForPoly(5, 3, verts, cpv(4, 1), 1), 219.3055833, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForPoly(0, 3, verts, cpv(2.2, 3.6), 7.1), 0, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForPoly(2.34, 4, verts, cpv(-4.1, -2.6), 3.8), 36.06910486, diff);
}

/* Simple test of cpAreaForPoly().
*/
void test_cpAreaForPoly(void)
{
	cpVect verts2[3] = { cpv(3, 1), cpv(2, 4), cpv(1, 7) };
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForPoly(3, verts2, 2), 37.8645919, diff);

	cpVect verts[4] = { cpv(2.67, -3.1), cpv(5.2, 1.5), cpv(-1.4, -7.0), cpv(0, 0) };
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForPoly(1, verts, 1.9), 11.34114948, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForPoly(2, verts,  1.9), 31.29057042, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForPoly(3, verts,  0), 4.4275, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForPoly(3, verts,  4.2), 150.7679537, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpAreaForPoly(4, verts,  3.8), 141.7940398, diff);
}

/* Simple test of cpCentroidForPoly().
*/
void test_cpCentroidForPoly(void)
{
	cpVect verts2[3] = { cpv(2, 5), cpv(1, 3), cpv(4, 6) };
	cpVect testVect1 = cpCentroidForPoly(3, verts2);
	CU_ASSERT_DOUBLE_EQUAL(testVect1.x, 2.333333, diff);
	CU_ASSERT_DOUBLE_EQUAL(testVect1.y, 4.6666667, diff);

	cpVect verts[4] = { cpv(3.78, 1.44), cpv(-2.5, -0.34), cpv(0, 0), cpv(-5.9, 6.2)};

	cpVect testVect2 = cpCentroidForPoly(3, verts);
	CU_ASSERT_DOUBLE_EQUAL(testVect2.x, 0.426666, diff);
	CU_ASSERT_DOUBLE_EQUAL(testVect2.y, 0.36666, diff);

	cpVect testVect3 = cpCentroidForPoly(4, verts);
	CU_ASSERT_DOUBLE_EQUAL(testVect3.x, -0.795244925, diff);
	CU_ASSERT_DOUBLE_EQUAL(testVect3.y, 2.717049552, diff);
	
}

/* Simple test of cpMomentForBox().
*/
void test_cpMomentForBox(void)
{
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForBox(1,3,5), 2.8333333, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForBox(3.33, 1.76, 8.90), 22.840359, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForBox(0.78, 0, 3.55), 0.8191625, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForBox(2.45, 4.98, 0), 5.0634155, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForBox(0, 0.98, 1.67), 0, diff);
}

/* Simple test of cpMomentForBox2().
*/
void test_cpMomentForBox2(void)
{
	cpBB box1 = cpBBNew(0, 0, 1, 1);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForBox2(1, box1), 0.6666, diff);

	cpBB box2 = cpBBNew(-3.2, 1.6, 4.7, 5.9);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForBox2(3.6, box2), 76.92, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForBox2(0, box2), 0, diff);

	cpBB box3 = cpBBNew(2.1, 0.75, -1.45, -3.2);
	CU_ASSERT_DOUBLE_EQUAL(cpMomentForBox2(2.63, box3), 10.40603333, diff);

}
