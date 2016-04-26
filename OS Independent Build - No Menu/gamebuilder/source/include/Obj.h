#ifndef OBJ_H_INCLUDED
#define OBJ_H_INCLUDED

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "ObjGPUDataStore.h"
#include "ShaderStore.h"
#include "SoundStore.h"

#include <vector>
#include <string>

#define OBJ_SURFACE 0x0001
#define OBJ_BOULDER 0x0002
#define OBJ_HERO 0x0004
#define OBJ_MOVINGPLAT 0x0008
#define OBJ_FATAL_HAZARD 0x0016
#define OBJ_GOAL 0x0032

/*! The Obj class acts as a base class for static, dynamic, and kinematic objects.  It holds the physics data (Chipmunk 2D) and gpu data of an object.
 */
class Obj
{

public:

    static glm::mat4 matProjection;  //!< The projection matrix.
    static glm::mat4 matView;  //!< The view matrix.


    static glm::vec4 primaryLightPos;  //!< The primary light position.
    static glm::vec3 primaryLightLa;  //!< The primary ambient light vector.
    static glm::vec3 primaryLightLd;  //!< The primary diffuse light vector.
    static glm::vec3 primaryLightLs;  //!< The primary spectral light vector.


    static ObjGPUDataStore gpuStore;  //!< Collection of loaded meshes.
    static ShaderStore shaderStore;  //!< Collection of loaded shaders.
    static SoundStore soundStore;  //!< Collection of loaded sounds.

    static Shader* currentShader;  //!< The shader currently being used.

    std::vector<ObjGPUData*> gpuDataList;  //!< Vector of meshes associated with this object.
    std::vector<Shader*> shaderList;  //!< Vector of shaders associated with this object.

    bool transformOverrides = false;  //!< Flag to activate override transformations.
    std::vector<glm::vec3> translationOverrideList;  //!< List of translation overrides (one for each mesh).
    std::vector<float> rotationOverrideList;  //!< List of rotation overrides (one for each mesh).
    std::vector<glm::mat4> shearOverrideList; //!< List of shear overrides (one for each mesh).

    float height;           //!< Height of the object.
    float width;            //!< Width of the object.

    glm::vec3 modelScale;  //!< Initial scaling matrix to be applied the model.

    bool draw = true;              //!< Flag for whether the object should be drawn or not.


    //! Renders an object
    /*!
      \param pos Object position
      \param angle Rotation about z axis
    */
    void render(glm::vec3 pos, float angle);
};






#endif // STATIC_OBJ_H_INCLUDED
