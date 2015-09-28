#ifndef CPSPATIALINDEX_PRIVATE_H
#define CPSPATIALINDEX_PRIVATE_H


#include "chipmunk.h"


//MARK: Spatial Index Functions
cpSpatialIndex *cpSpatialIndexInit(cpSpatialIndex *index, cpSpatialIndexClass *klass, cpSpatialIndexBBFunc bbfunc, cpSpatialIndex *staticIndex);

#endif