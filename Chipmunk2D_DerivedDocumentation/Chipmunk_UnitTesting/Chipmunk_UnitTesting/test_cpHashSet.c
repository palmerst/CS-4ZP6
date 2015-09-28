
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpHashSet.h"

#include "chipmunk/cpHashSet_private.h"
#include "chipmunk\chipmunk.h"

#define diff 0.0001

cpHashSet *hashSet1;

void *ptrNew;
void *ptrDefault;
void* value;
static int
testHashSet(void *obj, void *node)
{
	return 0;
}

/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpHashSetSuite(void)
{

	ptrNew = 0;
	ptrDefault = 0;
	hashSet1 = cpHashSetNew(10, (cpHashSetEqlFunc)testHashSet);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpHashSetSuite(void)
{
	return 0;
}

/* Simple test of cpHashSetSetDefaultValue().
*/
void test_cpHashSetSetDefaultValue(void)
{
	void *ptr2 = 0;
	void *ptr3 = "hello";

	CU_ASSERT(cpHashSetFind(hashSet1, (cpHashValue)4, ptr2) == NULL);

	cpHashSetSetDefaultValue(hashSet1, ptr2);
	CU_ASSERT(cpHashSetFind(hashSet1, (cpHashValue)4, ptr2) == ptr2);

	cpHashSetSetDefaultValue(hashSet1, ptr3);
	CU_ASSERT(cpHashSetFind(hashSet1, (cpHashValue)4, ptr3) == ptr3);

	cpHashSetSetDefaultValue(hashSet1, ptrDefault);
	CU_ASSERT(cpHashSetFind(hashSet1, (cpHashValue)4, ptrDefault) == ptrDefault);

}


/* Simple test of cpHashSetCount().
*/
void test_cpHashSetCount(void)
{
	CU_ASSERT(cpHashSetCount(hashSet1) == 0);
	void *data = 0;
	cpHashSetInsert(hashSet1, (cpHashValue)4, ptrNew, (cpHashSetTransFunc)testHashSet, data);
	CU_ASSERT(cpHashSetCount(hashSet1) == 1);
	cpHashSetRemove(hashSet1, (cpHashValue)4, ptrNew);
	CU_ASSERT(cpHashSetCount(hashSet1) == 0);
}


/* Simple test of cpHashSetInsert().
*/
void test_cpHashSetInsert(void)
{
	void *data =0;

	value  = cpHashSetInsert(hashSet1, (cpHashValue)4, ptrNew, (cpHashSetTransFunc)testHashSet, data);
	CU_ASSERT(cpHashSetFind(hashSet1, (cpHashValue)4, ptrNew) == value);
}


/* Simple test of cpHashSetRemove().
*/
void test_cpHashSetRemove(void)
{
	void *data = 0;

	CU_ASSERT(cpHashSetRemove(hashSet1, (cpHashValue)4, ptrNew) == value);
	CU_ASSERT(cpHashSetRemove(hashSet1, (cpHashValue)4, ptrNew) == NULL);
}


/* Simple test of cpHashSetFind().
*/
void test_cpHashSetFind(void)
{
	void *data = 0;
	void *pointerNotInHash = "notInHash";
	value = cpHashSetInsert(hashSet1, (cpHashValue)4, ptrNew, (cpHashSetTransFunc)testHashSet, data);

	CU_ASSERT(cpHashSetFind(hashSet1, (cpHashValue)4, ptrNew) == value);
	CU_ASSERT(cpHashSetFind(hashSet1, (cpHashValue)25, pointerNotInHash) == ptrDefault);
}
