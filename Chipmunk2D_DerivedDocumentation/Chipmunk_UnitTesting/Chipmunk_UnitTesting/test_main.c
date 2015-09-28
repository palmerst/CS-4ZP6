
#include "CUnit\Automated.h"
#include "test_main.h"
/* The main() function for setting up and running the tests.
* Returns a CUE_SUCCESS on successful running, another
* CUnit error code on failure.
*/
/* The suite initialization function.
* Returns zero on success, non-zero otherwise.
*/
int init_default(void)
{
	return 0;
}

/* The suite cleanup function.
* Returns zero on success, non-zero otherwise.
*/
int clean_default(void)
{
	return 0;
}


int main()
{

	CU_pSuite chipmunkSuite= NULL;
	CU_pSuite cpArbiterSuite = NULL;
	CU_pSuite cpArraySuite = NULL;
	CU_pSuite cpBodySuite = NULL;
	CU_pSuite cpConstriantSuite = NULL;
	CU_pSuite cpDampedRotarySpringSuite = NULL;
	CU_pSuite cpDampedSpringSuite = NULL;
	CU_pSuite cpGearJointSuite = NULL;
	CU_pSuite cpGrooveJointSuite = NULL;
	CU_pSuite cpHashSetSuite = NULL;
	CU_pSuite cpPinJointSuite = NULL;
	CU_pSuite cpPivotJointSuite = NULL;
	CU_pSuite cpPolyShapeSuite = NULL;
	CU_pSuite cpRatchetJointSuite = NULL;
	CU_pSuite cpRotaryLimitJointSuite = NULL;
	CU_pSuite cpSimpleMotorSuite = NULL;
	CU_pSuite cpSlideJointSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	chipmunkSuite = CU_add_suite("Suite_Chipmunk", init_default, clean_default);
	if (NULL == chipmunkSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpArbiterSuite = CU_add_suite("Suite_cpArbiter", init_cpArbiterSuite, clean_cpArbiterSuite);
	if (NULL == cpArbiterSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpArraySuite = CU_add_suite("Suite_cpArray", init_cpArraySuite, clean_cpArraySuite);
	if (NULL == cpArraySuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpBodySuite = CU_add_suite("Suite_cpBody", init_cpBodySuite, clean_cpBodySuite);
	if (NULL == cpBodySuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpConstriantSuite = CU_add_suite("Suite_cpConstraint", init_cpConstraintSuite, clean_cpConstraintSuite);
	if (NULL == cpConstriantSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpDampedRotarySpringSuite = CU_add_suite("Suite_cpDampedRotarySpring", init_cpDampedRotarySpringSuite, clean_cpDampedRotarySpringSuite);
	if (NULL == cpDampedRotarySpringSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpDampedSpringSuite = CU_add_suite("Suite_cpDampedySpring", init_cpDampedSpringSuite, clean_cpDampedSpringSuite);
	if (NULL == cpDampedSpringSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpGearJointSuite = CU_add_suite("Suite_cpGearJoint", init_cpGearJointSuite, clean_cpGearJointSuite);
	if (NULL == cpGearJointSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpGrooveJointSuite = CU_add_suite("Suite_cpGrooveJoint", init_cpGrooveJointSuite, clean_cpGrooveJointSuite);
	if (NULL == cpGrooveJointSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpHashSetSuite = CU_add_suite("Suite_cpHashSet", init_cpHashSetSuite, clean_cpHashSetSuite);
	if (NULL == cpHashSetSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	} 

	/* add a suite to the registry */
	cpPinJointSuite = CU_add_suite("Suite_cpPinJoint", init_cpPinJointSuite, clean_cpPinJointSuite);
	if (NULL == cpPinJointSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add a suite to the registry */
	cpPivotJointSuite = CU_add_suite("Suite_cpPivotJoint", init_cpPivotJointSuite, clean_cpPivotJointSuite);
	if (NULL == cpPivotJointSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpPolyShapeSuite = CU_add_suite("Suite_cpPolyShape", init_cpPolyShapeSuite, clean_cpPolyShapeSuite);
	if (NULL == cpPolyShapeSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpRatchetJointSuite = CU_add_suite("Suite_cpRatchetJoint", init_cpRatchetJointSuite, clean_cpRatchetJointSuite);
	if (NULL == cpRatchetJointSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpRotaryLimitJointSuite = CU_add_suite("Suite_cpRotaryLimitJoint", init_cpRotaryLimitJointSuite, clean_cpRotaryLimitJointSuite);
	if (NULL == cpRotaryLimitJointSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpSimpleMotorSuite = CU_add_suite("Suite_cpSimpleMotor", init_cpSimpleMotorSuite, clean_cpSimpleMotorSuite);
	if (NULL == cpSimpleMotorSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add a suite to the registry */
	cpSlideJointSuite = CU_add_suite("Suite_cpSlideJoint", init_cpSlideJointSuite, clean_cpSlideJointSuite);
	if (NULL == cpSlideJointSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(chipmunkSuite, "test_cpMomentForCircle", test_cpMomentForCircle)) ||
		(NULL == CU_add_test(chipmunkSuite, "test_cpAreaForCircle", test_cpAreaForCircle)) ||
		(NULL == CU_add_test(chipmunkSuite, "test_cpMomentForSegment", test_cpMomentForSegment)) ||
		(NULL == CU_add_test(chipmunkSuite, "test_cpAreaForSegment", test_cpAreaForSegment)) ||
		(NULL == CU_add_test(chipmunkSuite, "test_cpMomentForPoly", test_cpMomentForPoly)) ||
		(NULL == CU_add_test(chipmunkSuite, "test_cpAreaForPoly", test_cpAreaForPoly)) ||
		(NULL == CU_add_test(chipmunkSuite, "test_cpCentroidForPoly", test_cpCentroidForPoly)) ||
		(NULL == CU_add_test(chipmunkSuite, "test_cpMomentForBox", test_cpMomentForBox)) ||
		(NULL == CU_add_test(chipmunkSuite, "test_cpMomentForBox2", test_cpMomentForBox2)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpArraySuite, "test_cpArrayPush", test_cpArrayPush))||
	   (NULL == CU_add_test(cpArraySuite, "test_cpArrayPop", test_cpArrayPop))|| 
	   (NULL == CU_add_test(cpArraySuite, "test_cpArrayContains", test_cpArrayContains)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpBodySuite, "test_cpBodyNewKinematic", test_cpBodyNewKinematic)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyNewStatic", test_cpBodyNewStatic)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyIsSleeping", test_cpBodyIsSleeping)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetType", test_cpBodyGetType)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetType", test_cpBodySetType)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetSpace", test_cpBodyGetSpace)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetMass", test_cpBodyGetMass)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetMass", test_cpBodySetMass)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetMoment", test_cpBodyGetMoment)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetMoment", test_cpBodySetMoment)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetRotation", test_cpBodyGetRotation)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyAddShape", test_cpBodyAddShape)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyRemoveShape", test_cpBodyRemoveShape)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyRemoveConstraint", test_cpBodyRemoveConstraint)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetPosition", test_cpBodyGetPosition)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetPosition", test_cpBodySetPosition)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetCenterOfGravity", test_cpBodyGetCenterOfGravity)) ||
		(NULL == CU_add_test(cpBodySuite, "Test of cpBodySetCenterOfGravity()", test_cpBodySetCenterOfGravity)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetCenterOfGravity", test_cpBodyGetVelocity)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetVelocity", test_cpBodySetVelocity)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetForce", test_cpBodyGetForce)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetForce", test_cpBodySetForce)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetAngle", test_cpBodyGetAngle)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetAngle", test_cpBodySetAngle)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetAngularVelocity", test_cpBodyGetAngularVelocity)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetAngularVelocity", test_cpBodySetAngularVelocity)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetTorque", test_cpBodyGetTorque)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetTorque", test_cpBodySetTorque)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetUserData", test_cpBodyGetUserData)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodySetUserData", test_cpBodySetUserData)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyUpdateVelocity", test_cpBodyUpdateVelocity)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyUpdatePosition", test_cpBodyUpdatePosition)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyLocalToWorld", test_cpBodyLocalToWorld)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyWorldToLocal)", test_cpBodyWorldToLocal)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetVelocityAtLocalPoint", test_cpBodyGetVelocityAtLocalPoint)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyGetVelocityAtWorldPoint", test_cpBodyGetVelocityAtWorldPoint)) ||
		(NULL == CU_add_test(cpBodySuite, "test_cpBodyKineticEnergy", test_cpBodyKineticEnergy)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetSpace", test_cpConstraintGetSpace)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetBodyA", test_cpConstraintGetBodyA)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetBodyB", test_cpConstraintGetBodyB)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetMaxForce", test_cpConstraintGetMaxForce)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintSetMaxForce", test_cpConstraintSetMaxForce)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetErrorBias", test_cpConstraintGetErrorBias)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintSetErrorBias", test_cpConstraintSetErrorBias)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetMaxBias", test_cpConstraintGetMaxBias)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintSetMaxBias", test_cpConstraintSetMaxBias)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetCollideBodies", test_cpConstraintGetCollideBodies)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintSetCollideBodies", test_cpConstraintSetCollideBodies)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetPreSolveFunc", test_cpConstraintGetPreSolveFunc)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintSetPreSolveFunc", test_cpConstraintSetPreSolveFunc)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetPostSolveFunc", test_cpConstraintGetPostSolveFunc)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintSetPostSolveFunc", test_cpConstraintSetPostSolveFunc)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetUserData", test_cpConstraintGetUserData)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintSetUserData", test_cpConstraintSetUserData)) ||
		(NULL == CU_add_test(cpConstriantSuite, "test_cpConstraintGetImpulse", test_cpConstraintGetImpulse)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpDampedRotarySpringSuite, "test_cpConstraintIsDampedRotarySpring", test_cpConstraintIsDampedRotarySpring)) ||
		(NULL == CU_add_test(cpDampedRotarySpringSuite, "test_cpDampedRotarySpringGetRestAngle", test_cpDampedRotarySpringGetRestAngle)) ||
		(NULL == CU_add_test(cpDampedRotarySpringSuite, "test_cpDampedRotarySpringSetRestAngle", test_cpDampedRotarySpringSetRestAngle)) ||
		(NULL == CU_add_test(cpDampedRotarySpringSuite, "test_cpDampedRotarySpringGetStiffness", test_cpDampedRotarySpringGetStiffness)) ||
		(NULL == CU_add_test(cpDampedRotarySpringSuite, "test_cpDampedRotarySpringSetStiffness", test_cpDampedRotarySpringSetStiffness)) ||
		(NULL == CU_add_test(cpDampedRotarySpringSuite, "test_cpDampedRotarySpringGetDamping", test_cpDampedRotarySpringGetDamping)) ||
		(NULL == CU_add_test(cpDampedRotarySpringSuite, "test_cpDampedRotarySpringSetDamping", test_cpDampedRotarySpringSetDamping)) ||
		(NULL == CU_add_test(cpDampedRotarySpringSuite, "test_cpDampedRotarySpringGetSpringTorqueFunc", test_cpDampedRotarySpringGetSpringTorqueFunc)) ||
		(NULL == CU_add_test(cpDampedRotarySpringSuite, "test_cpDampedRotarySpringSetSpringTorqueFunc", test_cpDampedRotarySpringSetSpringTorqueFunc)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpDampedSpringSuite, "test_cpConstraintIsDampedSpring", test_cpConstraintIsDampedSpring)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringGetAnchorA", test_cpDampedSpringGetAnchorA)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringSetAnchorA", test_cpDampedSpringSetAnchorA)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringGetAnchorB", test_cpDampedSpringGetAnchorB)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringSetAnchorB", test_cpDampedSpringSetAnchorB)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringGetRestLength", test_cpDampedSpringGetRestLength)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringSetRestLength", test_cpDampedSpringSetRestLength)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringGetStiffness", test_cpDampedSpringGetStiffness)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringSetStiffness", test_cpDampedSpringSetStiffness)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringGetDamping", test_cpDampedSpringGetDamping)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringSetDamping", test_cpDampedSpringSetDamping)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringGetSpringForceFunc", test_cpDampedSpringGetSpringForceFunc)) ||
		(NULL == CU_add_test(cpDampedSpringSuite, "test_cpDampedSpringSetSpringForceFunc", test_cpDampedSpringSetSpringForceFunc)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpGearJointSuite, "test_cpConstraintIsGearJoint", test_cpConstraintIsGearJoint)) ||
		(NULL == CU_add_test(cpGearJointSuite, "test_cpGearJointGetPhase", test_cpGearJointGetPhase)) ||
		(NULL == CU_add_test(cpGearJointSuite, "test_cpGearJointSetPhase", test_cpGearJointSetPhase)) ||
		(NULL == CU_add_test(cpGearJointSuite, "test_cpGearJointGetRatio", test_cpGearJointGetRatio)) ||
		(NULL == CU_add_test(cpGearJointSuite, "test_cpGearJointSetRatio", test_cpGearJointSetRatio)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpGrooveJointSuite, "test_cpConstraintIsGrooveJoint", test_cpConstraintIsGrooveJoint))||
		(NULL == CU_add_test(cpGrooveJointSuite, "test_cpGrooveJointGetGrooveA", test_cpGrooveJointGetGrooveA)) ||
		(NULL == CU_add_test(cpGrooveJointSuite, "test_cpGrooveJointSetGrooveA", test_cpGrooveJointSetGrooveA)) ||
		(NULL == CU_add_test(cpGrooveJointSuite, "test_cpGrooveJointGetGrooveB", test_cpGrooveJointGetGrooveB)) ||
		(NULL == CU_add_test(cpGrooveJointSuite, "test_cpGrooveJointSetGrooveB", test_cpGrooveJointSetGrooveB)) ||
		(NULL == CU_add_test(cpGrooveJointSuite, "test_cpGrooveJointGetAnchorB", test_cpGrooveJointGetAnchorB)) ||
		(NULL == CU_add_test(cpGrooveJointSuite, "test_cpGrooveJointSetAnchorB", test_cpGrooveJointSetAnchorB)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpHashSetSuite, "test_cpHashSetSetDefaultValue", test_cpHashSetSetDefaultValue)) ||
		(NULL == CU_add_test(cpHashSetSuite, "test_cpHashSetCount", test_cpHashSetCount)) ||
		(NULL == CU_add_test(cpHashSetSuite, "test_cpHashSetInsert", test_cpHashSetInsert)) ||
		(NULL == CU_add_test(cpHashSetSuite, "test_cpHashSetRemove", test_cpHashSetRemove)) ||
		(NULL == CU_add_test(cpHashSetSuite, "test_cpHashSetFind", test_cpHashSetFind)) )
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpPinJointSuite, "test_cpConstraintIsPinJoint", test_cpConstraintIsPinJoint)) ||
		(NULL == CU_add_test(cpPinJointSuite, "test_cpPinJointGetAnchorA", test_cpPinJointGetAnchorA)) ||
		(NULL == CU_add_test(cpPinJointSuite, "test_cpPinJointSetAnchorA", test_cpPinJointSetAnchorA)) ||
		(NULL == CU_add_test(cpPinJointSuite, "test_cpPinJointGetAnchorB", test_cpPinJointGetAnchorB)) ||
		(NULL == CU_add_test(cpPinJointSuite, "test_cpPinJointSetAnchorB", test_cpPinJointSetAnchorB)) ||
		(NULL == CU_add_test(cpPinJointSuite, "test_cpPinJointGetDist", test_cpPinJointGetDist)) ||
		(NULL == CU_add_test(cpPinJointSuite, "test_cpPinJointSetDist", test_cpPinJointSetDist)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpPivotJointSuite, "test_cpConstraintIsPivotJoint", test_cpConstraintIsPivotJoint)) ||
		(NULL == CU_add_test(cpPivotJointSuite, "test_cpPivotJointGetAnchorA", test_cpPivotJointGetAnchorA)) ||
		(NULL == CU_add_test(cpPivotJointSuite, "test_cpPivotJointSetAnchorA", test_cpPivotJointSetAnchorA)) ||
		(NULL == CU_add_test(cpPivotJointSuite, "test_cpPivotJointGetAnchorB", test_cpPivotJointGetAnchorB)) ||
		(NULL == CU_add_test(cpPivotJointSuite, "test_cpPivotJointSetAnchorB", test_cpPivotJointSetAnchorB)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpPolyShapeSuite, "test_cpPolyShapeGetCount", test_cpPolyShapeGetCount)) ||
		(NULL == CU_add_test(cpPolyShapeSuite, "test_cpPolyShapeGetVert", test_cpPolyShapeGetVert)) ||
		(NULL == CU_add_test(cpPolyShapeSuite, "test_cpPolyShapeGetRadius", test_cpPolyShapeGetRadius)) ||
		(NULL == CU_add_test(cpPolyShapeSuite, "test_cpPolyShapeSetVerts", test_cpPolyShapeSetVerts)) ||
		(NULL == CU_add_test(cpPolyShapeSuite, "test_cpPolyShapeSetRadius", test_cpPolyShapeSetRadius)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpRatchetJointSuite, "test_cpConstraintIsRatchetJoint", test_cpConstraintIsRatchetJoint)) ||
		(NULL == CU_add_test(cpRatchetJointSuite, "test_cpRatchetJointGetAngle", test_cpRatchetJointGetAngle)) ||
		(NULL == CU_add_test(cpRatchetJointSuite, "test_cpRatchetJointSetAngle", test_cpRatchetJointSetAngle)) ||
		(NULL == CU_add_test(cpRatchetJointSuite, "test_cpRatchetJointGetPhase", test_cpRatchetJointGetPhase)) ||
		(NULL == CU_add_test(cpRatchetJointSuite, "test_cpRatchetJointSetPhase", test_cpRatchetJointSetPhase)) ||
		(NULL == CU_add_test(cpRatchetJointSuite, "test_cpRatchetJointGetRatchet", test_cpRatchetJointGetRatchet)) ||
		(NULL == CU_add_test(cpRatchetJointSuite, "test_cpRatchetJointSetRatchet", test_cpRatchetJointSetRatchet)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpRotaryLimitJointSuite, "test_cpConstraintIsRotaryLimitJoint", test_cpConstraintIsRotaryLimitJoint)) ||
		(NULL == CU_add_test(cpRotaryLimitJointSuite, "test_cpRotaryLimitJointGetMin", test_cpRotaryLimitJointGetMin)) ||
		(NULL == CU_add_test(cpRotaryLimitJointSuite, "test_cpRotaryLimitJointSetMin", test_cpRotaryLimitJointSetMin)) ||
		(NULL == CU_add_test(cpRotaryLimitJointSuite, "test_cpRotaryLimitJointGetMax", test_cpRotaryLimitJointGetMax)) ||
		(NULL == CU_add_test(cpRotaryLimitJointSuite, "test_cpRotaryLimitJointSetMax", test_cpRotaryLimitJointSetMax)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpSimpleMotorSuite, "test_cpConstraintIsSimpleMotor", test_cpConstraintIsSimpleMotor)) ||
		(NULL == CU_add_test(cpSimpleMotorSuite, "test_cpSimpleMotorGetRate", test_cpSimpleMotorGetRate)) ||
		(NULL == CU_add_test(cpSimpleMotorSuite, "test_cpSimpleMotorSetRate", test_cpSimpleMotorSetRate)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	/* add the tests to the suite */
	if ((NULL == CU_add_test(cpSlideJointSuite, "test_cpConstraintIsSlideJoint", test_cpConstraintIsSlideJoint)) ||
		(NULL == CU_add_test(cpSlideJointSuite, "test_cpSlideJointGetAnchorA", test_cpSlideJointGetAnchorA)) ||
		(NULL == CU_add_test(cpSlideJointSuite, "test_cpSlideJointSetAnchorA", test_cpSlideJointSetAnchorA)) ||
		(NULL == CU_add_test(cpSlideJointSuite, "test_cpSlideJointGetAnchorB", test_cpSlideJointGetAnchorB)) ||
		(NULL == CU_add_test(cpSlideJointSuite, "test_cpSlideJointSetAnchorB", test_cpSlideJointSetAnchorB)) ||
		(NULL == CU_add_test(cpSlideJointSuite, "test_cpSlideJointGetMin", test_cpSlideJointGetMin)) ||
		(NULL == CU_add_test(cpSlideJointSuite, "test_cpSlideJointSetMin", test_cpSlideJointSetMin)) ||
		(NULL == CU_add_test(cpSlideJointSuite, "test_cpSlideJointGetMax", test_cpSlideJointGetMax)) ||
		(NULL == CU_add_test(cpSlideJointSuite, "test_cpSlideJointSetMax", test_cpSlideJointSetMax)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit console interface */
	CU_automated_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
