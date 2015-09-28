#ifndef CPARRAY_PRIVATE_H
#define CPARRAY_PRIVATE_H


#include "chipmunk.h"
//MARK: cpArray

struct cpArray {
	int num, max;
	void **arr;
};

cpArray *cpArrayNew(int size);

void cpArrayFree(cpArray *arr);

void cpArrayPush(cpArray *arr, void *object);
void *cpArrayPop(cpArray *arr);
void cpArrayDeleteObj(cpArray *arr, void *obj);
cpBool cpArrayContains(cpArray *arr, void *ptr);

void cpArrayFreeEach(cpArray *arr, void (freeFunc)(void*));

#endif