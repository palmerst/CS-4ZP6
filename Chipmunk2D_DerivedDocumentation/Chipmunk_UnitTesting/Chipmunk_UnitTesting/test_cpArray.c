
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpArray.h"

#include "chipmunk/cpArray_private.h"

#define diff 0.0001

cpArray *arr1, *arr2, *arr3;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpArraySuite(void)
{
	arr1 = cpArrayNew(2);
	arr2 = cpArrayNew(2);
	arr3 = cpArrayNew(2);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpArraySuite(void)
{
	return 0;
}

/* Simple test of cpArrayPush().
*/
void test_cpArrayPush(void)
{
	CU_ASSERT(arr1->num == 0);
	cpBody *body1 = cpBodyNew(1, 1);

	cpArrayPush(arr1, body1);
	CU_ASSERT(arr1->num == 1);

	cpArrayPush(arr1, body1);
	CU_ASSERT(arr1->num == 2);

	cpArrayPush(arr1, body1);
	CU_ASSERT(arr1->num == 3);

	cpArrayPush(arr1, body1);
	CU_ASSERT(arr1->num == 4);
}

/* Simple test of cpArrayPop().
*/
void test_cpArrayPop(void)
{
	cpBody *body1 = cpBodyNew(1, 1);
	arr2->arr[0] = body1;
	arr2->arr[1] = body1;
	arr2->arr[2] = body1;
	arr2->num = 3;

	cpArrayPop(arr2);
	CU_ASSERT(arr2->num == 2);

	cpArrayPop(arr2);
	CU_ASSERT(arr2->num == 1);

	cpArrayPop(arr2);
	CU_ASSERT(arr2->num == 0);

}


/* Simple test of cpArrayContains().
*/
void test_cpArrayContains(void)
{
	cpBody *body1 = cpBodyNew(1, 1);
	cpBody *body2 = cpBodyNew(1, 1);
	cpBody *body3 = cpBodyNew(1, 1);
	cpBody *body4 = cpBodyNew(1, 1);

	arr3->arr[0] = body1;
	arr3->arr[1] = body2;
	arr3->arr[2] = body3;
	arr3->num = 3; 

	CU_ASSERT_TRUE(cpArrayContains(arr3, body1));
	CU_ASSERT_TRUE(cpArrayContains(arr3, body2));
	CU_ASSERT_TRUE(cpArrayContains(arr3, body3));
	CU_ASSERT_FALSE(cpArrayContains(arr3, body4));

}