

#ifndef CPCONSTRAINT_PRIVATE_H
#define CPCONSTRAINT_PRIVATE_H

#include "chipmunk.h"

//MARK: Constraints
// TODO naming conventions here

typedef void(*cpConstraintPreStepImpl)(cpConstraint *constraint, cpFloat dt);
typedef void(*cpConstraintApplyCachedImpulseImpl)(cpConstraint *constraint, cpFloat dt_coef);
typedef void(*cpConstraintApplyImpulseImpl)(cpConstraint *constraint, cpFloat dt);
typedef cpFloat(*cpConstraintGetImpulseImpl)(cpConstraint *constraint);

typedef struct cpConstraintClass {
	cpConstraintPreStepImpl preStep;
	cpConstraintApplyCachedImpulseImpl applyCachedImpulse;
	cpConstraintApplyImpulseImpl applyImpulse;
	cpConstraintGetImpulseImpl getImpulse;
} cpConstraintClass;

struct cpConstraint {
	const cpConstraintClass *klass;

	cpSpace *space;

	cpBody *a, *b;
	cpConstraint *next_a, *next_b;

	cpFloat maxForce;
	cpFloat errorBias;
	cpFloat maxBias;

	cpBool collideBodies;

	cpConstraintPreSolveFunc preSolve;
	cpConstraintPostSolveFunc postSolve;

	cpDataPointer userData;
};

struct cpPinJoint {
	cpConstraint constraint;
	cpVect anchorA, anchorB;
	cpFloat dist;

	cpVect r1, r2;
	cpVect n;
	cpFloat nMass;

	cpFloat jnAcc;
	cpFloat bias;
};

struct cpSlideJoint {
	cpConstraint constraint;
	cpVect anchorA, anchorB;
	cpFloat min, max;

	cpVect r1, r2;
	cpVect n;
	cpFloat nMass;

	cpFloat jnAcc;
	cpFloat bias;
};

struct cpPivotJoint {
	cpConstraint constraint;
	cpVect anchorA, anchorB;

	cpVect r1, r2;
	cpMat2x2 k;

	cpVect jAcc;
	cpVect bias;
};

struct cpGrooveJoint {
	cpConstraint constraint;
	cpVect grv_n, grv_a, grv_b;
	cpVect  anchorB;

	cpVect grv_tn;
	cpFloat clamp;
	cpVect r1, r2;
	cpMat2x2 k;

	cpVect jAcc;
	cpVect bias;
};

struct cpDampedSpring {
	cpConstraint constraint;
	cpVect anchorA, anchorB;
	cpFloat restLength;
	cpFloat stiffness;
	cpFloat damping;
	cpDampedSpringForceFunc springForceFunc;

	cpFloat target_vrn;
	cpFloat v_coef;

	cpVect r1, r2;
	cpFloat nMass;
	cpVect n;

	cpFloat jAcc;
};

struct cpDampedRotarySpring {
	cpConstraint constraint;
	cpFloat restAngle;
	cpFloat stiffness;
	cpFloat damping;
	cpDampedRotarySpringTorqueFunc springTorqueFunc;

	cpFloat target_wrn;
	cpFloat w_coef;

	cpFloat iSum;
	cpFloat jAcc;
};

struct cpRotaryLimitJoint {
	cpConstraint constraint;
	cpFloat min, max;

	cpFloat iSum;

	cpFloat bias;
	cpFloat jAcc;
};

struct cpRatchetJoint {
	cpConstraint constraint;
	cpFloat angle, phase, ratchet;

	cpFloat iSum;

	cpFloat bias;
	cpFloat jAcc;
};

struct cpGearJoint {
	cpConstraint constraint;
	cpFloat phase, ratio;
	cpFloat ratio_inv;

	cpFloat iSum;

	cpFloat bias;
	cpFloat jAcc;
};

struct cpSimpleMotor {
	cpConstraint constraint;
	cpFloat rate;

	cpFloat iSum;

	cpFloat jAcc;
};

void cpConstraintInit(cpConstraint *constraint, const struct cpConstraintClass *klass, cpBody *a, cpBody *b);

static inline void
cpConstraintActivateBodies(cpConstraint *constraint)
{
	cpBody *a = constraint->a; cpBodyActivate(a);
	cpBody *b = constraint->b; cpBodyActivate(b);
}

static inline cpVect
relative_velocity(cpBody *a, cpBody *b, cpVect r1, cpVect r2){
	cpVect v1_sum = cpvadd(a->CP_PRIVATE(v), cpvmult(cpvperp(r1), a->CP_PRIVATE(w)));
	cpVect v2_sum = cpvadd(b->CP_PRIVATE(v), cpvmult(cpvperp(r2), b->CP_PRIVATE(w)));

	return cpvsub(v2_sum, v1_sum);
}

static inline cpFloat
normal_relative_velocity(cpBody *a, cpBody *b, cpVect r1, cpVect r2, cpVect n){
	return cpvdot(relative_velocity(a, b, r1, r2), n);
}

static inline void
apply_impulse(cpBody *body, cpVect j, cpVect r){
	body->CP_PRIVATE(v) = cpvadd(body->CP_PRIVATE(v), cpvmult(j, body->CP_PRIVATE(m_inv)));
	body->CP_PRIVATE(w) += body->CP_PRIVATE(i_inv)*cpvcross(r, j);
}

static inline void
apply_impulses(cpBody *a, cpBody *b, cpVect r1, cpVect r2, cpVect j)
{
	apply_impulse(a, cpvneg(j), r1);
	apply_impulse(b, j, r2);
}

static inline void
apply_bias_impulse(cpBody *body, cpVect j, cpVect r)
{
	body->CP_PRIVATE(v_bias) = cpvadd(body->CP_PRIVATE(v_bias), cpvmult(j, body->CP_PRIVATE(m_inv)));
	body->CP_PRIVATE(w_bias) += body->CP_PRIVATE(i_inv)*cpvcross(r, j);
}

static inline void
apply_bias_impulses(cpBody *a, cpBody *b, cpVect r1, cpVect r2, cpVect j)
{
	apply_bias_impulse(a, cpvneg(j), r1);
	apply_bias_impulse(b, j, r2);
}

static inline cpFloat
k_scalar_body(cpBody *body, cpVect r, cpVect n)
{
	cpFloat rcn = cpvcross(r, n);
	return body->CP_PRIVATE(m_inv) + body->CP_PRIVATE(i_inv)*rcn*rcn;
}

static inline cpFloat
k_scalar(cpBody *a, cpBody *b, cpVect r1, cpVect r2, cpVect n)
{
	cpFloat value = k_scalar_body(a, r1, n) + k_scalar_body(b, r2, n);
	cpAssertSoft(value != 0.0, "Unsolvable collision or constraint.");

	return value;
}

static inline cpMat2x2
k_tensor(cpBody *a, cpBody *b, cpVect r1, cpVect r2)
{
	cpFloat m_sum = a->CP_PRIVATE(m_inv) + b->CP_PRIVATE(m_inv);

	// start with Identity*m_sum
	cpFloat k11 = m_sum, k12 = 0.0f;
	cpFloat k21 = 0.0f, k22 = m_sum;

	// add the influence from r1
	cpFloat a_i_inv = a->CP_PRIVATE(i_inv);
	cpFloat r1xsq = r1.x * r1.x * a_i_inv;
	cpFloat r1ysq = r1.y * r1.y * a_i_inv;
	cpFloat r1nxy = -r1.x * r1.y * a_i_inv;
	k11 += r1ysq; k12 += r1nxy;
	k21 += r1nxy; k22 += r1xsq;

	// add the influnce from r2
	cpFloat b_i_inv = b->CP_PRIVATE(i_inv);
	cpFloat r2xsq = r2.x * r2.x * b_i_inv;
	cpFloat r2ysq = r2.y * r2.y * b_i_inv;
	cpFloat r2nxy = -r2.x * r2.y * b_i_inv;
	k11 += r2ysq; k12 += r2nxy;
	k21 += r2nxy; k22 += r2xsq;

	// invert
	cpFloat det = k11*k22 - k12*k21;
	cpAssertSoft(det != 0.0, "Unsolvable constraint.");

	cpFloat det_inv = 1.0f / det;
	return cpMat2x2New(
		k22*det_inv, -k12*det_inv,
		-k21*det_inv, k11*det_inv
		);
}

static inline cpFloat
bias_coef(cpFloat errorBias, cpFloat dt)
{
	return 1.0f - cpfpow(errorBias, dt);
}


static inline cpConstraint *
cpConstraintNext(cpConstraint *node, cpBody *body)
{
	return (node->a == body ? node->next_a : node->next_b);
}

#define CP_BODY_FOREACH_CONSTRAINT(bdy, var)\
for (cpConstraint *var = bdy->constraintList; var; var = cpConstraintNext(var, bdy))

#endif