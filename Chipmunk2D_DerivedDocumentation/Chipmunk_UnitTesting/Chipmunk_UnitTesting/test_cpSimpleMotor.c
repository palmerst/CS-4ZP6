
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpSimpleMotor.h"

#include "chipmunk\chipmunk_private.h"
#include "chipmunk\chipmunk.h"
#define diff 0.0001

static cpBody *body1, *body2;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpSimpleMotorSuite(void)
{
	body1 = cpBodyNew(1, 1);
	body2 = cpBodyNew(1, 1);
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpSimpleMotorSuite(void)
{
	return 0;
}

/* Simple test of cpConstraintIsSimpleMotor().
*/
void test_cpConstraintIsSimpleMotor(void)
{
	cpConstraint *isSimpleMotor = cpSimpleMotorNew(body1, body2, 1);
	cpConstraint *isNotSimpleMotor = cpGearJointNew(body1, body2, 1, 1);

	CU_ASSERT(cpConstraintIsSimpleMotor(isSimpleMotor));
	CU_ASSERT_FALSE(cpConstraintIsSimpleMotor(isNotSimpleMotor));
}


/* Simple test of cpSimpleMotorGetRate().
*/
void test_cpSimpleMotorGetRate(void)
{
	cpConstraint *motor1 = cpSimpleMotorNew(body1, body2, 57.8);
	cpConstraint *motor2 = cpSimpleMotorNew(body1, body2, -36.3);
	cpConstraint *motor3 = cpSimpleMotorNew(body1, body2, 0);
	cpConstraint *motor4 = cpSimpleMotorNew(body1, body2, 12);

	CU_ASSERT(cpSimpleMotorGetRate(motor1) == 57.8);
	CU_ASSERT(cpSimpleMotorGetRate(motor2) == -36.3);
	CU_ASSERT(cpSimpleMotorGetRate(motor3) == 0);
	CU_ASSERT(cpSimpleMotorGetRate(motor4) == 12);
}


/* Simple test of cpSimpleMotorSetRate().
*/
void test_cpSimpleMotorSetRate(void)
{
	cpConstraint *motor1 = cpSimpleMotorNew(body1, body2, 57.8);

	cpSimpleMotorSetRate(motor1, 117.9);
	CU_ASSERT(((cpSimpleMotor *)motor1)->rate == 117.9);

	cpSimpleMotorSetRate(motor1, -99.14);
	CU_ASSERT(((cpSimpleMotor *)motor1)->rate == -99.14);

	cpSimpleMotorSetRate(motor1, 0);
	CU_ASSERT(((cpSimpleMotor *)motor1)->rate == 0);

	cpSimpleMotorSetRate(motor1, 84);
	CU_ASSERT(((cpSimpleMotor *)motor1)->rate == 84);
}
