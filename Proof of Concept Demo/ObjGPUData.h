#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

typedef unsigned int GLuint;



/*! The ObjGPUData class loads and stores data used by the GPU to render objects.
 *  Each object is defined by three files which are loaded by this class:  an object file (.obj) which contains information about vertices, faces, normals, and texture coordinates;
 *  a material file (.mtl) which contains texture and lighting information;
 *  and an image file(s) (.dds) which contain the texture images.
 *
 *
 */
class ObjGPUData
{
    private:
        //! Defines the different datatypes found in the .obj file;  used in parsing.
        enum dataType : short;
        //! Defines the different datatypes found in the .mtl file;  used in parsing.
        enum mtlDataType : short;
        struct FullVertex;

        //! Parses .obj and .mtl files and stores the data.
        /*!
          \param fileName Name (without extension) of the .obj and .mtl files
        */
        void loadObject(const char* fileName);

        //! Converts string to .obj file datatype (dataType).
        /*!
          \param dataTypeString The string to be converted.
          \return Equivalent dataType value.
        */
        dataType getDataType(std::string dataTypeString);
        //! Converts string to .mtl file datatype (mtlDataType).
        /*!
          \param dataTypeString The string to be converted.
          \return Equivalent mtlDataType value.
        */
        mtlDataType getMtlDataType(std::string dataTypeString);


    public:

        //! ObjGPUData constructor
        /*!
          \param objFile Object and material file path (these should have the same name) without extension
          \param angle Initial y-axis rotation in radians (optional:  default 0.0)
        */
        ObjGPUData(const char* objFile, float angle = 0.0f, bool scalingMode = true);

        class Material{
        public:

            std::string materialName;
            GLfloat shine;
            glm::vec3 Ka, Kd, Ks;
            GLuint texture;
            std::string textureName;
            bool textureSet;

            Material(std::string materialName){
                this->materialName = materialName;
                textureSet = false;
            }
        };  //!< Class for storing material information loaded from .mtl file

        std::vector<glm::vec3> vList;           //!< Stores vertex coordinates loaded from .obj file
        std::vector<glm::vec2> vTextureList;    //!< Stores texture coordinates loaded from .obj file
        std::vector<glm::vec3> vNormalList;     //!< Stores vertex normals loaded from .obj file
        std::vector<GLuint> fList;              //!< Stores faces loaded from .obj file
        std::vector<int> materialIndices;       //!< Marks divisions of different materials given in the .obj file (and defined in .mtl file)
        std::vector<Material> materials;        //!< Stores material information loaded from .mtl file

        GLuint vertexArrayObj;      //!< Name to bind the vertex array object
        GLuint elementBuffer;       //!< Name to bind the element buffer object
        GLuint vertexBuffer;        //!< Name to bind the vertex buffer object
        GLuint textureBuffer;       //!< Name to bind the texture coordinate buffer object
        GLuint normalBuffer;        //!< Name to bind the vertex normal buffer object
//        GLuint shaderProgram;
//        GLuint texture_ID;
//        GLuint MVP_ID, MV_ID, P_ID, N_ID;
//        GLuint MTL_KA_ID, MTL_KD_ID, MTL_KS_ID, MTL_SHINE_ID;
//        GLuint LPOS_ID, LA_ID, LD_ID, LS_ID;

        glm::mat4 unitScale;        //!< Scaling factor to adjust object to size 1.0 in y-axis (height)
//        glm::mat4 scaling;
        glm::mat4 rotation;         //!< Rotation about y-axis to adjust objects initial rotational centering (if required:  this is what the optional constructor argument sets)

        float whRatio;              //!< Ratio of maximum x-axis vertex separation (width) to maximum y-axis vertex separation (height)
};

#endif // OBJECT_H
