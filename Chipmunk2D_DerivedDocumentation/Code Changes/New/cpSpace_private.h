//MARK: Spaces
#ifndef CPSPACE_PRIVATE_H
#define CPSPACE_PRIVATE_H

#include "cpHashSet_private.h"
#include "cpArray_private.h"
#include "cpArbiter_private.h"
#include "chipmunk.h"



typedef struct cpContactBufferHeader cpContactBufferHeader;
typedef void(*cpSpaceArbiterApplyImpulseFunc)(cpArbiter *arb);

struct cpSpace {
	int iterations;

	cpVect gravity;
	cpFloat damping;

	cpFloat idleSpeedThreshold;
	cpFloat sleepTimeThreshold;

	cpFloat collisionSlop;
	cpFloat collisionBias;
	cpTimestamp collisionPersistence;

	cpDataPointer userData;

	cpTimestamp stamp;
	cpFloat curr_dt;

	cpArray *dynamicBodies;
	cpArray *staticBodies;
	cpArray *rousedBodies;
	cpArray *sleepingComponents;

	cpHashValue shapeIDCounter;
	cpSpatialIndex *staticShapes;
	cpSpatialIndex *dynamicShapes;

	cpArray *constraints;

	cpArray *arbiters;
	cpContactBufferHeader *contactBuffersHead;
	cpHashSet *cachedArbiters;
	cpArray *pooledArbiters;

	cpArray *allocatedBuffers;
	unsigned int locked;

	cpBool usesWildcards;
	cpHashSet *collisionHandlers;
	cpCollisionHandler defaultHandler;

	cpBool skipPostStep;
	cpArray *postStepCallbacks;

	cpBody *staticBody;
	cpBody _staticBody;
};

#define cpAssertSpaceUnlocked(space) \
	cpAssertHard(!space->locked, \
	"This operation cannot be done safely during a call to cpSpaceStep() or during a query. " \
	"Put these calls into a post-step callback." \
	);

void cpSpaceSetStaticBody(cpSpace *space, cpBody *body);

extern cpCollisionHandler cpCollisionHandlerDoNothing;

void cpSpaceProcessComponents(cpSpace *space, cpFloat dt);

void cpSpacePushFreshContactBuffer(cpSpace *space);
struct cpContact *cpContactBufferGetArray(cpSpace *space);
void cpSpacePushContacts(cpSpace *space, int count);

typedef struct cpPostStepCallback {
	cpPostStepFunc func;
	void *key;
	void *data;
} cpPostStepCallback;

cpPostStepCallback *cpSpaceGetPostStepCallback(cpSpace *space, void *key);

cpBool cpSpaceArbiterSetFilter(cpArbiter *arb, cpSpace *space);
void cpSpaceFilterArbiters(cpSpace *space, cpBody *body, cpShape *filter);

void cpSpaceActivateBody(cpSpace *space, cpBody *body);
void cpSpaceLock(cpSpace *space);
void cpSpaceUnlock(cpSpace *space, cpBool runPostStep);

static inline void
cpSpaceUncacheArbiter(cpSpace *space, cpArbiter *arb)
{
	const cpShape *a = arb->a, *b = arb->b;
	const cpShape *shape_pair[] = { a, b };
	cpHashValue arbHashID = CP_HASH_PAIR((cpHashValue)a, (cpHashValue)b);
	cpHashSetRemove(space->cachedArbiters, arbHashID, shape_pair);
	cpArrayDeleteObj(space->arbiters, arb);
}

static inline cpArray *
cpSpaceArrayForBodyType(cpSpace *space, cpBodyType type)
{
	return (type == CP_BODY_TYPE_STATIC ? space->staticBodies : space->dynamicBodies);
}

void cpShapeUpdateFunc(cpShape *shape, void *unused);
cpCollisionID cpSpaceCollideShapes(cpShape *a, cpShape *b, cpCollisionID id, cpSpace *space);

#endif