
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpPolyShape.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk_unsafe.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1;
static cpShape *shape1;

static cpVect verts1[4]; 
static cpVect verts2[4];

static cpTransform transform1;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpPolyShapeSuite(void)
{
	verts1[0] = cpv(2.67, -3.1);
	verts1[1] = cpv(5.2, 1.5);
	verts1[2] = cpv(-1.4, -7.0);
	verts1[3] = cpv(0, 0);

	verts2[0] = cpv(-3.45, -4.2);
	verts2[1] = cpv(-3.1, 2.7);
	verts2[2] = cpv(4.6, 5.9);
	verts2[3] = cpv(6.1, -5.2);
	
	body1 = cpBodyNew(1, 1);
	transform1 = cpTransformNew(3.2, 1.5, 6.7, 2.1, 4.4, 8.6);
	shape1 = cpPolyShapeNew(body1, 4, verts1, transform1, 10);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpPolyShapeSuite(void)
{
	return 0;
}


/* Simple test of cpPolyShapeGetCount().
*/
void test_cpPolyShapeGetCount(void)
{
	CU_ASSERT(cpPolyShapeGetCount(shape1) == 4);
}


/* Simple test of cpPolyShapeGetVert().
*/
void test_cpPolyShapeGetVert(void)
{
	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 0).x, -46.98, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 0).y, -8.2,diff);
	
	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 1).x, 4.4, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 1).y, 8.6, diff);

	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 2).x, 31.09, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 2).y, 19.55, diff);

	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 3).x, -7.826, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 3).y, 6.095, diff);

	

}

/* Simple test of cpPolyShapeGetRadius().
*/
void test_cpPolyShapeGetRadius(void)
{
	CU_ASSERT(cpPolyShapeGetRadius(shape1) == 10);

	((cpPolyShape*)shape1)->r = 3.46;
	CU_ASSERT(cpPolyShapeGetRadius(shape1) == 3.46);

	((cpPolyShape*)shape1)->r = 0;
	CU_ASSERT(cpPolyShapeGetRadius(shape1) == 0);

	((cpPolyShape*)shape1)->r = -7.14;
	CU_ASSERT(cpPolyShapeGetRadius(shape1) == -7.14);
}


/* Simple test of cpPolyShapeSetVerts().
*/
void test_cpPolyShapeSetVerts(void)
{
	cpPolyShapeSetVerts(shape1, 4, verts2, transform1);

	
	CU_ASSERT(((cpPolyShape*)shape1)->count == 4);
	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 0).x, -34.78, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 0).y, -5.395, diff);

	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 3).x, -10.92, diff);
	CU_ASSERT_DOUBLE_EQUAL(cpPolyShapeGetVert(shape1, 3).y, 6.83, diff);


}



/* Simple test of cpPolyShapeSetRadius().
*/
void test_cpPolyShapeSetRadius(void)
{

	cpPolyShapeSetRadius(shape1, 0);
	CU_ASSERT(((cpPolyShape*)shape1)->r == 0);

	cpPolyShapeSetRadius(shape1, 11.4);
	CU_ASSERT(((cpPolyShape*)shape1)->r == 11.4);

	cpPolyShapeSetRadius(shape1, -1.5);
	CU_ASSERT(((cpPolyShape*)shape1)->r == -1.5);
}


