
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpConstraint.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpConstraint *pinJoint, *grooveJoint, *simpleMotor;
static cpBody *body1, *body2, *body3;
static cpSpace *space, *space2;

/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpConstraintSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	body3 = cpBodyNew(1, 1);

	space = cpSpaceNew();
	space2 = cpSpaceNew();

	pinJoint = cpPinJointNew(body1, body2, cpv(3.1, -1.4), cpv(2, 7));
	grooveJoint = cpGrooveJointNew(body2, body3, cpv(0,0), cpv(11.7,-1.4), cpv(15, 2));
	simpleMotor = cpSimpleMotorNew(body3, body1,2.1);

	cpSpaceAddConstraint(space, pinJoint);
	cpSpaceAddConstraint(space, grooveJoint);
	cpSpaceAddConstraint(space2, simpleMotor);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpConstraintSuite(void)
{
	return 0;
}

/* Simple test of cpConstraintGetSpace().
*/
void test_cpConstraintGetSpace(void)
{
	CU_ASSERT(cpConstraintGetSpace(pinJoint) == space);
	CU_ASSERT(cpConstraintGetSpace(grooveJoint) == space);
	CU_ASSERT(cpConstraintGetSpace(simpleMotor) == space2);
}

/* Simple test of cpConstraintGetBodyA().
*/
void test_cpConstraintGetBodyA(void)
{
	CU_ASSERT(cpConstraintGetBodyA(pinJoint) == body1);
	CU_ASSERT(cpConstraintGetBodyA(grooveJoint) == body2);
	CU_ASSERT(cpConstraintGetBodyA(simpleMotor) == body3);
}

/* Simple test of cpConstraintGetBodyB().
*/
void test_cpConstraintGetBodyB(void)
{
	CU_ASSERT(cpConstraintGetBodyB(pinJoint) == body2);
	CU_ASSERT(cpConstraintGetBodyB(grooveJoint) == body3);
	CU_ASSERT(cpConstraintGetBodyB(simpleMotor) == body1);
}

/* Simple test of cpConstraintGetMaxForce().
*/
void test_cpConstraintGetMaxForce(void)
{
	pinJoint->maxForce = 11.7;
	grooveJoint->maxForce = 3;
	simpleMotor->maxForce = 2.7;

	CU_ASSERT(cpConstraintGetMaxForce(pinJoint) == 11.7);
	CU_ASSERT(cpConstraintGetMaxForce(grooveJoint) == 3);
	CU_ASSERT(cpConstraintGetMaxForce(simpleMotor) == 2.7);
}

/* Simple test of cpConstraintSetMaxForce().
*/
void test_cpConstraintSetMaxForce(void)
{
	cpConstraintSetMaxForce(pinJoint, 5.68);
	cpConstraintSetMaxForce(grooveJoint, 6.7);
	cpConstraintSetMaxForce(simpleMotor, 4);

	CU_ASSERT(pinJoint->maxForce == 5.68);
	CU_ASSERT(grooveJoint->maxForce == 6.7);
	CU_ASSERT(simpleMotor->maxForce == 4);
}

/* Simple test of cpConstraintGetErrorBias().
*/
void test_cpConstraintGetErrorBias(void)
{
	pinJoint->errorBias = 1.05;
	grooveJoint->errorBias = 7.8;
	simpleMotor->errorBias = 16;

	CU_ASSERT(cpConstraintGetErrorBias(pinJoint) == 1.05);
	CU_ASSERT(cpConstraintGetErrorBias(grooveJoint) == 7.8);
	CU_ASSERT(cpConstraintGetErrorBias(simpleMotor) == 16);
}

/* Simple test of cpConstraintSetErrorBias().
*/
void test_cpConstraintSetErrorBias(void)
{
	cpConstraintSetErrorBias(pinJoint, 3.45);
	cpConstraintSetErrorBias(grooveJoint, 9);
	cpConstraintSetErrorBias(simpleMotor, 5.17);

	CU_ASSERT(pinJoint->errorBias == 3.45);
	CU_ASSERT(grooveJoint->errorBias == 9);
	CU_ASSERT(simpleMotor->errorBias == 5.17);
}

/* Simple test of cpConstraintGetMaxBias().
*/
void test_cpConstraintGetMaxBias(void)
{
	pinJoint->maxBias = 9.51;
	grooveJoint->maxBias = 12;
	simpleMotor->maxBias = 8.04;

	CU_ASSERT(cpConstraintGetMaxBias(pinJoint) == 9.51);
	CU_ASSERT(cpConstraintGetMaxBias(grooveJoint) == 12);
	CU_ASSERT(cpConstraintGetMaxBias(simpleMotor) == 8.04);
}

/* Simple test of cpConstraintSetMaxBias().
*/
void test_cpConstraintSetMaxBias(void)
{
	cpConstraintSetMaxBias(pinJoint, 11.02);
	cpConstraintSetMaxBias(grooveJoint, 0.7);
	cpConstraintSetMaxBias(simpleMotor, 19);

	CU_ASSERT(pinJoint->maxBias == 11.02);
	CU_ASSERT(grooveJoint->maxBias == 0.7);
	CU_ASSERT(simpleMotor->maxBias == 19);
}

/* Simple test of cpConstraintGetCollideBodies().
*/
void test_cpConstraintGetCollideBodies(void)
{
	pinJoint->collideBodies = 0;
	grooveJoint->collideBodies = 1;
	simpleMotor->collideBodies = 0;

	CU_ASSERT(cpConstraintGetCollideBodies(pinJoint) == 0);
	CU_ASSERT(cpConstraintGetCollideBodies(grooveJoint) == 1);
	CU_ASSERT(cpConstraintGetCollideBodies(simpleMotor) == 0);
}

/* Simple test of cpConstraintSetCollideBodies().
*/
void test_cpConstraintSetCollideBodies(void)
{
	cpConstraintSetCollideBodies(pinJoint, 0);
	cpConstraintSetCollideBodies(grooveJoint, 0);
	cpConstraintSetCollideBodies(simpleMotor, 1);

	CU_ASSERT(pinJoint->collideBodies == 0);
	CU_ASSERT(grooveJoint->collideBodies == 0);
	CU_ASSERT(simpleMotor->collideBodies == 1);
}


static cpFloat
testPreSolve(cpConstraint *constraint, cpSpace *space){
	return 0;
}

/* Simple test of cpConstraintGetPreSolveFunc().
*/
void test_cpConstraintGetPreSolveFunc(void)
{
	pinJoint->preSolve = (cpConstraintPreSolveFunc)testPreSolve;
	CU_ASSERT(cpConstraintGetPreSolveFunc(pinJoint) == (cpConstraintPreSolveFunc)testPreSolve);
}

/* Simple test of cpConstraintSetPreSolveFunc().
*/
void test_cpConstraintSetPreSolveFunc(void)
{
	cpConstraintSetPreSolveFunc(pinJoint, (cpConstraintPreSolveFunc)testPreSolve);
	CU_ASSERT(pinJoint->preSolve == (cpConstraintPreSolveFunc)testPreSolve);
}

static cpFloat
testPostSolve(cpConstraint *constraint, cpSpace *space){
	return 0;
}

/* Simple test of cpConstraintGetPostSolveFunc().
*/
void test_cpConstraintGetPostSolveFunc(void)
{
	grooveJoint->postSolve = (cpConstraintPostSolveFunc)testPostSolve;
	CU_ASSERT(cpConstraintGetPostSolveFunc(grooveJoint) == (cpConstraintPostSolveFunc)testPostSolve);
}

/* Simple test of cpConstraintSetPreSolveFunc().
*/
void test_cpConstraintSetPostSolveFunc(void)
{
	cpConstraintSetPreSolveFunc(grooveJoint, (cpConstraintPostSolveFunc)testPostSolve);
	CU_ASSERT(grooveJoint->postSolve == (cpConstraintPostSolveFunc)testPostSolve);
}

/* Simple test of cpConstraintGetUserData().
*/
void test_cpConstraintGetUserData(void)
{
	cpDataPointer p = cpConstraintGetUserData(simpleMotor);
	CU_ASSERT(p == NULL);

	cpBody *pointer = cpBodyNew(1, 1);
	pinJoint->userData = (cpDataPointer)pointer;
	CU_ASSERT(cpConstraintGetUserData(pinJoint) == pointer);
}

/* Simple test of cpConstraintSetUserData().
*/
void test_cpConstraintSetUserData(void)
{
	cpBody *pointer = cpBodyNew(1, 1);
	cpConstraintSetUserData(grooveJoint, (cpDataPointer)pointer);
	CU_ASSERT(grooveJoint->userData == pointer);

	cpConstraintSetUserData(pinJoint, NULL);
	CU_ASSERT(pinJoint->userData == NULL);
}

/* Simple test of cpConstraintGetImpulse().
*/
void test_cpConstraintGetImpulse(void)
{
	((cpPinJoint*)pinJoint)->jnAcc = -12.4;
	((cpGrooveJoint*)grooveJoint)->jAcc = cpv(1,4);
	((cpSimpleMotor*)simpleMotor)->jAcc = 25.36;

	CU_ASSERT(cpConstraintGetImpulse(pinJoint) == 12.4);
	CU_ASSERT_DOUBLE_EQUAL(cpConstraintGetImpulse(grooveJoint),  4.123105626, diff);
	CU_ASSERT(cpConstraintGetImpulse(simpleMotor) == 25.36);
}