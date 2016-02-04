#ifndef OBJ_H_INCLUDED
#define OBJ_H_INCLUDED

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtx/transform2.hpp"
#include "ObjGPUDataStore.h"
#include "ShaderStore.h"
#include "SoundStore.h"

#include <vector>
#include <string>

#define OBJ_SURFACE 0x0001
#define OBJ_BOULDER 0x0002
#define OBJ_HERO 0x0004
#define OBJ_HERO_BULLET 0x0008
#define OBJ_FATAL_HAZARD 0x0016


/*! The Obj class acts as a base class for static, dynamic, and kinematic objects.  It holds the physics data (Chipmunk 2D) and gpu data of an object.
 */
class Obj {

    public:

        static glm::mat4 matProjection;
        static glm::mat4 matView;

        static ObjGPUDataStore gpuStore;
        static ShaderStore shaderStore;
        static SoundStore soundStore;

        static Shader* currentShader;

        std::vector<ObjGPUData*> gpuDataList;
        std::vector<Shader*> shaderList;

        bool transformOverrides = false;
        std::vector<glm::vec3> translationOverrideList;
        std::vector<float> rotationOverrideList;
        std::vector<glm::mat4> shearOverrideList;
    //    ObjGPUData* gpuData;    //!< Pointer to the gpu data associated with the object.

        float height;           //!< Height of the object.
        float width;            //!< Width of the object.

        glm::vec3 modelScale;

        bool draw = true;              //!< Flag for whether the object should be drawn or not.

        void render(glm::vec3 pos, float angle);
};






#endif // STATIC_OBJ_H_INCLUDED
