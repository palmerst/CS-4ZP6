#ifndef CPSHAPE_PRIVATE_H
#define CPSHAPE_PRIVATE_H

#include "chipmunk.h"

// TODO: Eww. Magic numbers.
#define MAGIC_EPSILON 1e-5


//MARK: Shapes/Collisions

struct cpShapeMassInfo {
	cpFloat m;
	cpFloat i;
	cpVect cog;
	cpFloat area;
};

typedef enum cpShapeType{
	CP_CIRCLE_SHAPE,
	CP_SEGMENT_SHAPE,
	CP_POLY_SHAPE,
	CP_NUM_SHAPES
} cpShapeType;

typedef cpBB(*cpShapeCacheDataImpl)(cpShape *shape, cpTransform transform);
typedef void(*cpShapeDestroyImpl)(cpShape *shape);
typedef void(*cpShapePointQueryImpl)(const cpShape *shape, cpVect p, cpPointQueryInfo *info);
typedef void(*cpShapeSegmentQueryImpl)(const cpShape *shape, cpVect a, cpVect b, cpFloat radius, cpSegmentQueryInfo *info);

typedef struct cpShapeClass cpShapeClass;

struct cpShapeClass {
	cpShapeType type;

	cpShapeCacheDataImpl cacheData;
	cpShapeDestroyImpl destroy;
	cpShapePointQueryImpl pointQuery;
	cpShapeSegmentQueryImpl segmentQuery;
};

struct cpShape {
	const cpShapeClass *klass;

	cpSpace *space;
	cpBody *body;
	struct cpShapeMassInfo massInfo;
	cpBB bb;

	cpBool sensor;

	cpFloat e;
	cpFloat u;
	cpVect surfaceV;

	cpDataPointer userData;

	cpCollisionType type;
	cpShapeFilter filter;

	cpShape *next;
	cpShape *prev;

	cpHashValue hashid;
};

struct cpCircleShape {
	cpShape shape;

	cpVect c, tc;
	cpFloat r;
};

struct cpSegmentShape {
	cpShape shape;

	cpVect a, b, n;
	cpVect ta, tb, tn;
	cpFloat r;

	cpVect a_tangent, b_tangent;
};

struct cpSplittingPlane {
	cpVect v0, n;
};

#define CP_POLY_SHAPE_INLINE_ALLOC 6

struct cpPolyShape {
	cpShape shape;

	cpFloat r;

	int count;
	// The untransformed planes are appended at the end of the transformed planes.
	struct cpSplittingPlane *planes;

	// Allocate a small number of splitting planes internally for simple poly.
	struct cpSplittingPlane _planes[2 * CP_POLY_SHAPE_INLINE_ALLOC];
};

cpShape *cpShapeInit(cpShape *shape, const cpShapeClass *klass, cpBody *body, struct cpShapeMassInfo massInfo);

static inline cpBool
cpShapeActive(cpShape *shape)
{
	// checks if the shape is added to a shape list.
	// TODO could this just check the space now?
	return (shape->prev || (shape->body && shape->body->shapeList == shape));
}

// Note: This function returns contact points with r1/r2 in absolute coordinates, not body relative.
struct cpCollisionInfo cpCollide(const cpShape *a, const cpShape *b, cpCollisionID id, struct cpContact *contacts);

static inline void
CircleSegmentQuery(cpShape *shape, cpVect center, cpFloat r1, cpVect a, cpVect b, cpFloat r2, cpSegmentQueryInfo *info)
{
	cpVect da = cpvsub(a, center);
	cpVect db = cpvsub(b, center);
	cpFloat rsum = r1 + r2;

	cpFloat qa = cpvdot(da, da) - 2.0f*cpvdot(da, db) + cpvdot(db, db);
	cpFloat qb = cpvdot(da, db) - cpvdot(da, da);
	cpFloat det = qb*qb - qa*(cpvdot(da, da) - rsum*rsum);

	if (det >= 0.0f){
		cpFloat t = (-qb - cpfsqrt(det)) / (qa);
		if (0.0f <= t && t <= 1.0f){
			cpVect n = cpvnormalize(cpvlerp(da, db, t));

			info->shape = shape;
			info->point = cpvsub(cpvlerp(a, b, t), cpvmult(n, r2));
			info->normal = n;
			info->alpha = t;
		}
	}
}

static inline cpBool
cpShapeFilterReject(cpShapeFilter a, cpShapeFilter b)
{
	// Reject the collision if:
	return (
		// They are in the same non-zero group.
		(a.group != 0 && a.group == b.group) ||
		// One of the category/mask combinations fails.
		(a.categories & b.mask) == 0 ||
		(b.categories & a.mask) == 0
		);
}

void cpLoopIndexes(const cpVect *verts, int count, int *start, int *end);


#define CP_BODY_FOREACH_SHAPE(body, var)\
	for(cpShape *var = body->shapeList; var; var = var->next)

#endif