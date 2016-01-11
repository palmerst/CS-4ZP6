#ifndef OBJ_H_INCLUDED
#define OBJ_H_INCLUDED

#include "include/chipmunk/chipmunk.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "ObjGPUData.h"

#include <vector>

#define OBJ_BOUNDARY 0x0001
#define OBJ_ENEMY 0x0002
#define OBJ_HERO 0x0004
#define OBJ_HERO_BULLET 0x0008


void setCollisionHandlers(cpSpace*);

int begin_single_deletion_collision(cpArbiter*, cpSpace*, cpDataPointer);
int begin_enemy_bullet_collision(cpArbiter*, cpSpace*, cpDataPointer);
int begin_knockback(cpArbiter*, cpSpace*, void*);


void deleteObject(cpSpace *space, void *obj, void *data);


/*! The Obj class acts as a base class for static, dynamic, and kinematic objects.  It holds the physics data (Chipmunk 2D) and gpu data of an object.
 */
class Obj {

    public:

        cpBody* body;           //!< Pointer to Chipmunk 2D body associated with the object.
        cpShape* shape;         //!< Pointer to Chipmunk 2D shape associated with the object.
        ObjGPUData* gpuData;    //!< Pointer to the gpu data associated with the object.

        float height;           //!< Height of the object.
        float width;            //!< Width of the object.

        bool draw;              //!< Flag for whether the object should be drawn or not.
};

/*! The StaticObject class is derived from the Obj class.  Physics calculations are generally ignored for static objects.  Used primarily for boundaries and stationary platforms.
 */
class StaticObject : public Obj {

    public:
        //! StaticObject constructor
        /*!
          \param space Chipmunk 2D space to attach object to
          \param p1 Bottom left coordinate of bounding box
          \param p2 Upper right coordinate of bounding box
          \param gpuData Pointer to the gpu data associated with the object
        */
        StaticObject(cpSpace* space, cpVect p1, cpVect p2, ObjGPUData* gpuData);


};

/*! The DynamicObject class is derived from the Obj class.  This type of object is subject to all physics calculations.
 */
class DynamicObject : public Obj {

    public:
        //! DynamicObject constructor
        DynamicObject();
        //! DynamicObject constructor
        /*!
          \param space Chipmunk 2D space to attach object to
          \param pos Coordinates of the initial center of the object
          \param mass Mass of the object
          \param scale Scalar factor by which to scale the object during GPU rendering
          \param elast Elasticity of the object
          \param fric Friction factor of the object
          \param gpuData Pointer to the gpu data associated with the object
          \param type Type of object (different values affect collision routines)
          \param noRotation Flag to ignore angular momentum in the physics calculations (default = false)
        */
        DynamicObject(cpSpace* space, glm::vec2 pos, float mass, float scale, float elast, float fric, ObjGPUData* gpuData, int type, bool noRotation = false);

};

/*! The KinematicObject class is derived from the Obj class.  This type of object has features of both static objects and dynamic objects and is generally used for moving platforms.
 */
class KinematicObject : public Obj {

    public:
        //! DynamicObject constructor
        /*!
          \param space Chipmunk 2D space to attach object to
          \param p1 Bottom left coordinate of bounding box
          \param p2 Upper right coordinate of bounding box
          \param gpuData Pointer to the gpu data associated with the object
          \param type Type of object (different values affect collision routines)
        */
        KinematicObject(cpSpace* space, cpVect p1, cpVect p2, ObjGPUData* gpuData, int type);

};


#endif // STATIC_OBJ_H_INCLUDED
