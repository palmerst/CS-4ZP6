#ifndef OBJ_H_INCLUDED
#define OBJ_H_INCLUDED

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "ObjGPUDataStore.h"
#include "ShaderStore.h"

#include <vector>
#include <string>

#define OBJ_BOUNDARY 0x0001
#define OBJ_ENEMY 0x0002
#define OBJ_HERO 0x0004
#define OBJ_HERO_BULLET 0x0008


/*! The Obj class acts as a base class for static, dynamic, and kinematic objects.  It holds the physics data (Chipmunk 2D) and gpu data of an object.
 */
class Obj {

    public:

        static glm::mat4 matProjection;
        static glm::mat4 matView;

        static ObjGPUDataStore gpuStore;
        static ShaderStore shaderStore;

        static Shader* currentShader;

        int gpuDataCount;
        std::vector<ObjGPUData*> gpuDataList;
        std::vector<Shader*> shaderList;
    //    ObjGPUData* gpuData;    //!< Pointer to the gpu data associated with the object.

        float height;           //!< Height of the object.
        float width;            //!< Width of the object.

        glm::vec3 modelScale;

        bool draw;              //!< Flag for whether the object should be drawn or not.

        void render(glm::vec3 pos, float angle, bool isBoundary);
};






#endif // STATIC_OBJ_H_INCLUDED
