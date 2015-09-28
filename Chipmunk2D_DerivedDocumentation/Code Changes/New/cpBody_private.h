#ifndef CPBODY_PRIVATE_H
#define CPBODY_PRIVATE_H

#include "chipmunk.h"
//MARK: Bodies
struct cpBody {
	// Integration functions
	cpBodyVelocityFunc velocity_func;
	cpBodyPositionFunc position_func;

	// mass and it's inverse
	cpFloat m;
	cpFloat m_inv;

	// moment of inertia and it's inverse
	cpFloat i;
	cpFloat i_inv;

	// center of gravity
	cpVect cog;

	// position, velocity, force
	cpVect p;
	cpVect v;
	cpVect f;

	// Angle, angular velocity, torque (radians)
	cpFloat a;
	cpFloat w;
	cpFloat t;

	cpTransform transform;

	cpDataPointer userData;

	// "pseudo-velocities" used for eliminating overlap.
	// Erin Catto has some papers that talk about what these are.
	cpVect v_bias;
	cpFloat w_bias;

	cpSpace *space;

	cpShape *shapeList;
	cpArbiter *arbiterList;
	cpConstraint *constraintList;

	struct {
		cpBody *root;
		cpBody *next;
		cpFloat idleTime;
	} sleeping;
};

void cpBodyAddShape(cpBody *body, cpShape *shape);
void cpBodyRemoveShape(cpBody *body, cpShape *shape);

//void cpBodyAccumulateMassForShape(cpBody *body, cpShape *shape);
void cpBodyAccumulateMassFromShapes(cpBody *body);

void cpBodyRemoveConstraint(cpBody *body, cpConstraint *constraint);


#define CP_BODY_FOREACH_COMPONENT(root, var)\
for (cpBody *var = root; var; var = var->sleeping.next)

#endif