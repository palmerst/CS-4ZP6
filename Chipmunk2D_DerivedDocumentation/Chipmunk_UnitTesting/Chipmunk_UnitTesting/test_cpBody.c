
#include <stdio.h>
#include "CUnit/Console.h"
#include "test_cpBody.h"

#include "chipmunk\chipmunk.h"
#include "chipmunk\cpBody_private.h"

#define diff 0.0001

static cpBody *body1, *body2, *body3;
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_cpBodySuite(void)
{
	body1 = cpBodyNew(5, 7);
	body2 = cpBodyNew(3.12, 4.7);
	body3 = cpBodyNew(9.8, 1.11);

	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_cpBodySuite(void)
{
	return 0;
}

/* Simple test of cpBodyNewKinematic().
*/
void test_cpBodyNewKinematic(void)
{
	cpBody *tempBody = cpBodyNewKinematic();

	//Test if tempBody is a static body. Should be False
	CU_ASSERT_FALSE(cpBodyGetType(tempBody) == CP_BODY_TYPE_STATIC);
	//Test if tempBody is a Kinematic body. Should be True
	CU_ASSERT_TRUE(cpBodyGetType(tempBody) == CP_BODY_TYPE_KINEMATIC);
	//Test if tempBody is a DYNAMIC body. Should be False
	CU_ASSERT_FALSE(cpBodyGetType(tempBody) == CP_BODY_TYPE_DYNAMIC);
}

/* Simple test of cpBodyNewStatic().
*/
void test_cpBodyNewStatic(void)
{
	cpBody *tempBody = cpBodyNewStatic();

	//Test if tempBody is a static body. Should be True
	CU_ASSERT_TRUE(cpBodyGetType(tempBody) == CP_BODY_TYPE_STATIC);
	//Test if tempBody is a Kinematic body. Should be False
	CU_ASSERT_FALSE(cpBodyGetType(tempBody) == CP_BODY_TYPE_KINEMATIC);
	//Test if tempBody is a DYNAMIC body. Should be False
	CU_ASSERT_FALSE(cpBodyGetType(tempBody) == CP_BODY_TYPE_DYNAMIC);

}


/* Simple test of cpBodyIsSleeping().
*/
void test_cpBodyIsSleeping(void)
{
	body1->sleeping.root = NULL;
	//If the body is not sleeping, the root is NULL
	CU_ASSERT_FALSE(cpBodyIsSleeping(body1));

	body1->sleeping.root = body2;
	//If the body is sleeping, the root exists.
	CU_ASSERT_TRUE(cpBodyIsSleeping(body1));
}


/* Simple test of cpBodyGetType().
*/
void test_cpBodyGetType(void)
{
	cpBody *tempBody = cpBodyNewStatic();
	cpBody *tempBody2 = cpBodyNewKinematic();

	CU_ASSERT(cpBodyGetType(body1) == CP_BODY_TYPE_DYNAMIC);
	CU_ASSERT(cpBodyGetType(tempBody) == CP_BODY_TYPE_STATIC);
	CU_ASSERT(cpBodyGetType(tempBody2) == CP_BODY_TYPE_KINEMATIC);
}

void test_cpBodySetType(void)
{
	cpBody *tempBody = cpBodyNew(3, 8);
	cpBodySetType(tempBody, CP_BODY_TYPE_DYNAMIC);
	CU_ASSERT(cpBodyGetType(tempBody) == CP_BODY_TYPE_DYNAMIC);
	CU_ASSERT(cpBodyGetType(tempBody) != CP_BODY_TYPE_STATIC);
	CU_ASSERT(cpBodyGetType(tempBody) != CP_BODY_TYPE_KINEMATIC);


	cpBodySetType(tempBody, CP_BODY_TYPE_STATIC);
	CU_ASSERT(cpBodyGetType(tempBody) == CP_BODY_TYPE_STATIC);
	CU_ASSERT(cpBodyGetType(tempBody) != CP_BODY_TYPE_DYNAMIC);
	CU_ASSERT(cpBodyGetType(tempBody) != CP_BODY_TYPE_KINEMATIC);


	cpBodySetType(tempBody, CP_BODY_TYPE_KINEMATIC);
	CU_ASSERT(cpBodyGetType(tempBody) == CP_BODY_TYPE_KINEMATIC);
	CU_ASSERT(cpBodyGetType(tempBody) != CP_BODY_TYPE_DYNAMIC);
	CU_ASSERT(cpBodyGetType(tempBody) != CP_BODY_TYPE_STATIC);
}

void test_cpBodyGetSpace(void)
{
	CU_ASSERT(cpBodyGetSpace(body1) == NULL);

	cpSpace *space = cpSpaceNew();
	cpSpaceAddBody(space, body2);

	CU_ASSERT(cpBodyGetSpace(body2) == space);
}


void test_cpBodyGetMass(void)
{
	CU_ASSERT(cpBodyGetMass(body1) == 5);
	CU_ASSERT(cpBodyGetMass(body2) == 3.12);
	CU_ASSERT(cpBodyGetMass(body3) == 9.8);
}

void test_cpBodySetMass(void)
{
	cpBody *tempBody = cpBodyNew(1.1, 4.75);
	CU_ASSERT(tempBody->m == 1.1);

	//Integer Test
	cpBodySetMass(tempBody, 1);
	CU_ASSERT(tempBody->m == 1);

	//Boundary Test
	cpBodySetMass(tempBody, 0);
	CU_ASSERT(tempBody->m == 0);

	//Float Test
	cpBodySetMass(tempBody, 8.75);
	CU_ASSERT(tempBody->m == 8.75);

}

void test_cpBodyGetMoment(void)
{
	CU_ASSERT(cpBodyGetMoment(body1) == 7);
	CU_ASSERT(cpBodyGetMoment(body2) == 4.7);
	CU_ASSERT(cpBodyGetMoment(body3) == 1.11);
}

void test_cpBodySetMoment(void)
{
	cpBody *tempBody = cpBodyNew(1.1, 2.65);
	CU_ASSERT(tempBody->i == 2.65);

	//Integer Test
	cpBodySetMoment(tempBody, 9);
	CU_ASSERT(tempBody->i== 9);

	//Boundary Test
	cpBodySetMoment(tempBody, 0);
	CU_ASSERT(tempBody->i == 0);

	//Float Test
	cpBodySetMoment(tempBody, 3.333);
	CU_ASSERT(tempBody->i == 3.333);

}

void test_cpBodyGetRotation()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	cpTransform transform = cpTransformNew(3.2, 4.7, 1.1, 2.2, 5.5, 3);
	tempBody->transform = transform;
	cpVect vect = cpBodyGetRotation(tempBody);
	CU_ASSERT(vect.x == 3.2);
	CU_ASSERT(vect.y == 4.7);

	//Integer Test
	cpTransform transform2 = cpTransformNew(3, 7, 1.1, 2.2, 5.5, 3);
	tempBody->transform = transform2;
	cpVect vect2 = cpBodyGetRotation(tempBody);
	CU_ASSERT(vect2.x == 3);
	CU_ASSERT(vect2.y == 7);

	//Negative Test
	cpTransform transform3 = cpTransformNew(-87.5, -32.1, 1.1, 2.2, 5.5, 3);
	tempBody->transform = transform3;
	cpVect vect3 = cpBodyGetRotation(tempBody);
	CU_ASSERT(vect3.x == -87.5);
	CU_ASSERT(vect3.y == -32.1);
}

void test_cpBodyAddShape()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	CU_ASSERT(tempBody->shapeList == NULL);

	cpShape *shape = cpBoxShapeNew(tempBody, 2, 2, 2);
	cpBodyAddShape(tempBody, shape);
	CU_ASSERT(tempBody->shapeList == shape);

	cpShape *shape2 = cpCircleShapeNew(tempBody, 2, cpv(0, 0));
	cpBodyAddShape(tempBody, shape2);
	CU_ASSERT(tempBody->shapeList == shape2);
}

void test_cpBodyRemoveShape()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	cpShape *shape = cpBoxShapeNew(tempBody, 2, 2, 2);
	cpShape *shape2 = cpCircleShapeNew(tempBody, 2, cpv(0, 0));
	cpShape *shape3 = cpCircleShapeNew(tempBody, 2, cpv(0, 0));

	cpBodyAddShape(tempBody, shape);
	cpBodyAddShape(tempBody, shape2);
	cpBodyAddShape(tempBody, shape3);


	cpBodyRemoveShape(tempBody, shape);
	CU_ASSERT(tempBody->shapeList == shape3);

	cpBodyRemoveShape(tempBody, shape3);
	CU_ASSERT(tempBody->shapeList == shape2);

	cpBodyRemoveShape(tempBody, shape2);
	CU_ASSERT(tempBody->shapeList == NULL);
		
}


void test_cpBodyRemoveConstraint()
{
	cpConstraint *pin = cpPinJointNew(body1, body2, cpv(0, 0), cpv(0, 0));
	cpConstraint *groove = cpGrooveJointNew(body2, body3, cpv(0, 0), cpv(0, 0),cpv(0,0));
	cpConstraint *rotary = cpRotaryLimitJointNew(body3, body1, 0,100);

	cpSpace *space = cpSpaceNew();
	cpSpaceAddConstraint(space, pin);
	cpSpaceAddConstraint(space, groove);
	cpSpaceAddConstraint(space, rotary);

	CU_ASSERT(body1->constraintList == rotary && body2->constraintList == groove && body3->constraintList == rotary);

	cpBodyRemoveConstraint(body1, rotary);
	CU_ASSERT(body1->constraintList == pin && body2->constraintList == groove && body3->constraintList == rotary);

	cpBodyRemoveConstraint(body3, rotary);
	CU_ASSERT(body1->constraintList == pin && body2->constraintList == groove && body3->constraintList == groove);

	cpBodyRemoveConstraint(body2, pin);
	CU_ASSERT(body1->constraintList == pin && body2->constraintList == groove && body3->constraintList == groove);

	cpBodyRemoveConstraint(body3, groove);
	CU_ASSERT(body1->constraintList == pin && body2->constraintList == groove && body3->constraintList == NULL);
}

void test_cpBodyGetPosition()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	tempBody->transform = cpTransformNew(1, 2, 3, 4, 5, 6);
	cpVect pos = cpBodyGetPosition(tempBody);
	CU_ASSERT(pos.x == 5);
	CU_ASSERT(pos.y == 6);

	tempBody->transform = cpTransformNew(3.78, 1.54, 2.79, 10.8, 3.22, 16.97);
	cpVect pos2 = cpBodyGetPosition(tempBody);
	CU_ASSERT(pos2.x == 3.22);
	CU_ASSERT(pos2.y == 16.97);

	tempBody->transform = cpTransformNew(-4.12,6.78,-3.45,1.24,-7.4,-2.01);
	cpVect pos3 = cpBodyGetPosition(tempBody);
	CU_ASSERT(pos3.x == -7.4);
	CU_ASSERT(pos3.y == -2.01);
}

void test_cpBodySetPosition()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	cpBodySetPosition(tempBody, cpv(13, 2));
	cpVect pos = tempBody->p;
	CU_ASSERT(pos.x == 13);
	CU_ASSERT(pos.y == 2);
	
	cpBodySetPosition(tempBody, cpv(-7.34, 4.87));
	cpVect pos2 = tempBody->p;
	CU_ASSERT(pos2.x == -7.34);
	CU_ASSERT(pos2.y == 4.87);

	cpBodySetPosition(tempBody, cpv(0, -9.01));
	cpVect pos3 = tempBody->p;
	CU_ASSERT(pos3.x == 0);
	CU_ASSERT(pos3.y == -9.01);
}

void test_cpBodyGetCenterOfGravity()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	tempBody->cog = cpv(1.2, 3.4);
	cpVect vect = cpBodyGetCenterOfGravity(tempBody);
	CU_ASSERT(vect.x == 1.2);
	CU_ASSERT(vect.y == 3.4);

	tempBody->cog = cpv(-4.8, 0);
	cpVect vect2 = cpBodyGetCenterOfGravity(tempBody);
	CU_ASSERT(vect2.x == -4.8);
	CU_ASSERT(vect2.y == 0);

	tempBody->cog = cpv(2, -7);
	cpVect vect3 = cpBodyGetCenterOfGravity(tempBody);
	CU_ASSERT(vect3.x == 2);
	CU_ASSERT(vect3.y == -7);
}

void test_cpBodySetCenterOfGravity()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	cpBodySetCenterOfGravity(tempBody, cpv(12.1, 6.02));
	CU_ASSERT(tempBody->cog.x == 12.1);
	CU_ASSERT(tempBody->cog.y == 6.02);

	cpBodySetCenterOfGravity(tempBody, cpv(0, -5.2));
	CU_ASSERT(tempBody->cog.x == 0);
	CU_ASSERT(tempBody->cog.y == -5.2);
	
	cpBodySetCenterOfGravity(tempBody, cpv(14, 3));
	CU_ASSERT(tempBody->cog.x == 14);
	CU_ASSERT(tempBody->cog.y == 3);
}

void test_cpBodyGetVelocity()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	tempBody->v = cpv(5.5, 9.7);
	cpVect vect = cpBodyGetVelocity(tempBody);
	CU_ASSERT(vect.x == 5.5);
	CU_ASSERT(vect.y == 9.7);

	tempBody->v = cpv(-19.6, -5.92);
	cpVect vect2 = cpBodyGetVelocity(tempBody);
	CU_ASSERT(vect2.x == -19.6);
	CU_ASSERT(vect2.y == -5.92);

	tempBody->v = cpv(5, 0);
	cpVect vect3 = cpBodyGetVelocity(tempBody);
	CU_ASSERT(vect3.x == 5);
	CU_ASSERT(vect3.y == 0);
}

void test_cpBodySetVelocity()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	cpBodySetVelocity(tempBody, cpv(9.1, 1.4));
	CU_ASSERT(tempBody->v.x == 9.1);
	CU_ASSERT(tempBody->v.y == 1.4);

	cpBodySetVelocity(tempBody, cpv(-0.3, -2.8));
	CU_ASSERT(tempBody->v.x == -0.3);
	CU_ASSERT(tempBody->v.y == -2.8);

	cpBodySetVelocity(tempBody, cpv(8, 13));
	CU_ASSERT(tempBody->v.x == 8);
	CU_ASSERT(tempBody->v.y == 13);
}

void test_cpBodyGetForce()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	tempBody->f = cpv(8.9, 3.4);
	cpVect vect = cpBodyGetForce(tempBody);
	CU_ASSERT(vect.x == 8.9);
	CU_ASSERT(vect.y == 3.4);

	tempBody->f = cpv(-7.08, -4.57);
	cpVect vect2 = cpBodyGetForce(tempBody);
	CU_ASSERT(vect2.x == -7.08);
	CU_ASSERT(vect2.y == -4.57);

	tempBody->f = cpv(2, 5);
	cpVect vect3 = cpBodyGetForce(tempBody);
	CU_ASSERT(vect3.x == 2);
	CU_ASSERT(vect3.y == 5);
}

void test_cpBodySetForce()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	cpBodySetForce(tempBody, cpv(38.74,79.02));
	CU_ASSERT(tempBody->f.x == 38.74);
	CU_ASSERT(tempBody->f.y == 79.02);

	cpBodySetForce(tempBody, cpv(-4.12, -18.28));
	CU_ASSERT(tempBody->f.x == -4.12);
	CU_ASSERT(tempBody->f.y == -18.28);

	cpBodySetForce(tempBody, cpv(25, 17));
	CU_ASSERT(tempBody->f.x == 25);
	CU_ASSERT(tempBody->f.y == 17);
}

void test_cpBodyGetAngle()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	tempBody->a = 0;
	CU_ASSERT(cpBodyGetAngle(tempBody) == 0);

	tempBody->a = M_PI_2;
	CU_ASSERT(cpBodyGetAngle(tempBody) == M_PI_2);

	tempBody->a = -M_PI_4;
	CU_ASSERT(cpBodyGetAngle(tempBody) == -M_PI_4);
}

void test_cpBodySetAngle()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	cpBodySetAngle(tempBody, M_PI);
	CU_ASSERT(tempBody->a == M_PI);

	cpBodySetAngle(tempBody, -M_PI_2);
	CU_ASSERT(tempBody->a == -M_PI_2);

	cpBodySetAngle(tempBody, 400);
	CU_ASSERT(tempBody->a == 400);
	
}

void test_cpBodyGetAngularVelocity()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	tempBody->w = 0;
	CU_ASSERT(cpBodyGetAngularVelocity(tempBody) == 0);

	tempBody->w = M_PI;
	CU_ASSERT(cpBodyGetAngularVelocity(tempBody) == M_PI);

	tempBody->w = -M_PI_2;
	CU_ASSERT(cpBodyGetAngularVelocity(tempBody) == -M_PI_2);
}

void test_cpBodySetAngularVelocity()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	cpBodySetAngularVelocity(tempBody, M_PI_4);
	CU_ASSERT(tempBody->w == M_PI_4);

	cpBodySetAngularVelocity(tempBody, -2*M_PI);
	CU_ASSERT(tempBody->w == -2*M_PI);

	cpBodySetAngularVelocity(tempBody, -1);
	CU_ASSERT(tempBody->w == -1);
}


void test_cpBodyGetTorque()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	tempBody->t = 4;
	CU_ASSERT(cpBodyGetTorque(tempBody) == 4);

	tempBody->t = 12.87;
	CU_ASSERT(cpBodyGetTorque(tempBody) == 12.87);

	tempBody->t = -1.20;
	CU_ASSERT(cpBodyGetTorque(tempBody) == -1.20);
}

void test_cpBodySetTorque()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	cpBodySetTorque(tempBody, -18);
	CU_ASSERT(tempBody->t == -18);

	cpBodySetTorque(tempBody, 29.07);
	CU_ASSERT(tempBody->t == 29.07);

	cpBodySetTorque(tempBody, -4.56);
	CU_ASSERT(tempBody->t == -4.56);
}

void test_cpBodyGetUserData()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	cpDataPointer p = cpBodyGetUserData(tempBody);
	CU_ASSERT(p == NULL);

	cpBody *pointer = cpBodyNew(1, 1);
	tempBody->userData = (cpDataPointer)pointer;
	CU_ASSERT(cpBodyGetUserData(tempBody) == pointer);
}

void test_cpBodySetUserData()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	cpBody *pointer = cpBodyNew(1, 1);
	cpBodySetUserData(tempBody, (cpDataPointer)pointer);
	CU_ASSERT(tempBody->userData == pointer);

	cpBodySetUserData(tempBody, NULL);
	CU_ASSERT(tempBody->userData == NULL);
}

void test_cpBodyUpdateVelocity()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	tempBody->v = cpv(10, 20);
	tempBody->w = M_PI;
	
	// No damping
	cpBodyUpdateVelocity(tempBody, cpv(0, 9.81), 1, 0.1);
	CU_ASSERT(tempBody->v.x == 10);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->v.y, 20.981, diff);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->w ,M_PI, diff);

	tempBody->v = cpv(10.5, 20.2);
	tempBody->w = M_PI;

	// With damping
	cpBodyUpdateVelocity(tempBody, cpv(0, 9.81), 0.75, 0.1);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->v.x, 7.875, diff);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->v.y, 16.131, diff);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->w, M_PI*0.75, diff);

	tempBody->v = cpv(10.5, 20.2);
	tempBody->w = M_PI;
	tempBody->f = cpv(-2.5, -3.4);
	tempBody->t = -5.6; 

	// With damping and initial force/torque
	cpBodyUpdateVelocity(tempBody, cpv(0, 9.81), 0.75, 0.1);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->v.x , 7.625, diff);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->v.y, 15.791, diff);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->w, M_PI*0.75 - 0.56, diff);

	cpBodySetType(tempBody, CP_BODY_TYPE_KINEMATIC);

	tempBody->v = cpv(10, 20);
	tempBody->w = M_PI;
	//Kinematic bodies are skipped
	cpBodyUpdateVelocity(tempBody, cpv(0, 9.81), 0, 0.1);
	CU_ASSERT(tempBody->v.x == 10);
	CU_ASSERT(tempBody->v.y == 20);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->w, M_PI, diff);
}

void test_cpBodyUpdatePosition()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	tempBody->p = cpv(50, 100);
	tempBody->a = 0;
	tempBody->v = cpv(5, 8);
	tempBody->w = 10;

	//Integer Test
	cpBodyUpdatePosition(tempBody, 0.1);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->p.x, 50.5, diff);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->p.y, 100.8, diff);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->a,1, diff);
	
	tempBody->p = cpv(-22.6, 2.1);
	tempBody->a = M_PI_2;
	tempBody->v = cpv(13.4, -25.8);
	tempBody->w = M_PI;

	//Float Test
	cpBodyUpdatePosition(tempBody, 0.1);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->p.x, -21.26, diff);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->p.y, -0.48, diff);
	CU_ASSERT_DOUBLE_EQUAL(tempBody->a, M_PI_2 + M_PI*0.1, diff);
}

void test_cpBodyLocalToWorld()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	
	//Integer test
	tempBody->transform = cpTransformNew(4, 8, 2, 9, 1, 3);
	cpVect vect = cpBodyLocalToWorld(tempBody, cpv(5, 10));

	CU_ASSERT(vect.x == 41);
	CU_ASSERT(vect.y == 133);

	//Float test
	tempBody->transform = cpTransformNew(1.2,7.6,4.3,8.9,6.2,12.09);
	cpVect vect2 = cpBodyLocalToWorld(tempBody, cpv(-3.6, -11.7));

	CU_ASSERT_DOUBLE_EQUAL(vect2.x, -48.43, diff);
	CU_ASSERT_DOUBLE_EQUAL(vect2.y , -119.4,diff);
}


void test_cpBodyWorldToLocal()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	//Integer test
	tempBody->transform = cpTransformNew(4, 8, 2, 9, 1, 3);
	cpVect vect = cpBodyWorldToLocal(tempBody, cpv(41, 133));

	CU_ASSERT(vect.x == 100);
	CU_ASSERT(vect.y == 200);
}

void test_cpBodyGetVelocityAtLocalPoint()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	//Integer Test
	tempBody->transform = cpTransformNew(3, 1, 5, 7, 8, 2);
	tempBody->v = cpv(7, 3);
	tempBody->w = 0.5;
	tempBody->cog = cpv(0, 0);

	cpVect vect = cpBodyGetVelocityAtLocalPoint(tempBody, cpv(4, 9));
	CU_ASSERT_DOUBLE_EQUAL(vect.x,-26.5 , diff);
	CU_ASSERT_DOUBLE_EQUAL(vect.y, 31.5, diff);


	//Float Test
	tempBody->transform = cpTransformNew(1.67, 3.7, 9.8, 2.4, 5.3, 1.6);
	tempBody->v = cpv(-4.56, 3.25);
	tempBody->w = -4.36;
	tempBody->cog = cpv(0.56, 1.32);

	cpVect vect2 = cpBodyGetVelocityAtLocalPoint(tempBody, cpv(5.7, 1.9));

	CU_ASSERT_DOUBLE_EQUAL(vect2.x, 84.4276, diff);
	CU_ASSERT_DOUBLE_EQUAL(vect2.y, -58.957608, diff);
}

void test_cpBodyGetVelocityAtWorldPoint()
{
	cpBody *tempBody = cpBodyNew(1, 1);

	//Integer Test
	tempBody->transform = cpTransformNew(5, 2, 3, 6, 12, 1);
	tempBody->v = cpv(15, 6);
	tempBody->w = 2;
	tempBody->cog = cpv(1, 3);

	cpVect vect = cpBodyGetVelocityAtWorldPoint(tempBody, cpv(2, 3));
	CU_ASSERT_EQUAL(vect.x, 51);
	CU_ASSERT_EQUAL(vect.y, -42);


	//Float Test
	tempBody->transform = cpTransformNew(3.22,4.76,1.1,9.5,3.4,7.6);
	tempBody->v = cpv(14.3, -22.6);
	tempBody->w = 5.57;
	tempBody->cog = cpv(2.45, -0.67);

	cpVect vect2 = cpBodyGetVelocityAtWorldPoint(tempBody, cpv(-4.3, 2.8));

	CU_ASSERT_DOUBLE_EQUAL(vect2.x, 70.54029, diff);
	CU_ASSERT_DOUBLE_EQUAL(vect2.y, -105.32564, diff);
}


void test_cpBodyKineticEnergy()
{
	cpBody *tempBody = cpBodyNew(1, 1);
	tempBody->v = cpv(2, 5);
	tempBody->w = 3;
	// integer test
	CU_ASSERT(cpBodyKineticEnergy(tempBody) == 38 );


	cpBody *tempBody2 = cpBodyNew(4.31, 7.85);
	tempBody2->v = cpv(-4.8, 2.7);
	tempBody2->w = -M_PI;
	// float test
	CU_ASSERT_DOUBLE_EQUAL(cpBodyKineticEnergy(tempBody2), 208.1986945, diff);
}