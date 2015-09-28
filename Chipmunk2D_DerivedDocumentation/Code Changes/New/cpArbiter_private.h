#ifndef CPARBITER_PRIVATE_H
#define CPARBITER_PRIVATE_H


//MARK: Arbiters
#include "chipmunk.h"
enum cpArbiterState {
	// Arbiter is active and its the first collision.
	CP_ARBITER_STATE_FIRST_COLLISION,
	// Arbiter is active and its not the first collision.
	CP_ARBITER_STATE_NORMAL,
	// Collision has been explicitly ignored.
	// Either by returning false from a begin collision handler or calling cpArbiterIgnore().
	CP_ARBITER_STATE_IGNORE,
	// Collison is no longer active. A space will cache an arbiter for up to cpSpace.collisionPersistence more steps.
	CP_ARBITER_STATE_CACHED,
	// Collison arbiter is invalid because one of the shapes was removed.
	CP_ARBITER_STATE_INVALIDATED,
};

struct cpArbiterThread {
	struct cpArbiter *next, *prev;
};

struct cpContact {
	cpVect r1, r2;

	cpFloat nMass, tMass;
	cpFloat bounce; // TODO: look for an alternate bounce solution.

	cpFloat jnAcc, jtAcc, jBias;
	cpFloat bias;

	cpHashValue hash;
};

struct cpCollisionInfo {
	const cpShape *a, *b;
	cpCollisionID id;

	cpVect n;

	int count;
	// TODO Should this be a unique struct type?
	struct cpContact *arr;
};

struct cpArbiter {
	cpFloat e;
	cpFloat u;
	cpVect surface_vr;

	cpDataPointer data;

	const cpShape *a, *b;
	cpBody *body_a, *body_b;
	struct cpArbiterThread thread_a, thread_b;

	int count;
	struct cpContact *contacts;
	cpVect n;

	// Regular, wildcard A and wildcard B collision handlers.
	cpCollisionHandler *handler, *handlerA, *handlerB;
	cpBool swapped;

	cpTimestamp stamp;
	enum cpArbiterState state;
};

cpArbiter* cpArbiterInit(cpArbiter *arb, cpShape *a, cpShape *b);

static inline struct cpArbiterThread *
cpArbiterThreadForBody(cpArbiter *arb, cpBody *body)
{
	return (arb->body_a == body ? &arb->thread_a : &arb->thread_b);
}

void cpArbiterUnthread(cpArbiter *arb);

void cpArbiterUpdate(cpArbiter *arb, struct cpCollisionInfo *info, cpSpace *space);
void cpArbiterPreStep(cpArbiter *arb, cpFloat dt, cpFloat bias, cpFloat slop);
void cpArbiterApplyCachedImpulse(cpArbiter *arb, cpFloat dt_coef);
void cpArbiterApplyImpulse(cpArbiter *arb);



static inline cpArbiter *
cpArbiterNext(cpArbiter *node, cpBody *body)
{
	return (node->body_a == body ? node->thread_a.next : node->thread_b.next);
}

#define CP_BODY_FOREACH_ARBITER(bdy, var)\
for (cpArbiter *var = bdy->arbiterList; var; var = cpArbiterNext(var, bdy))

#endif