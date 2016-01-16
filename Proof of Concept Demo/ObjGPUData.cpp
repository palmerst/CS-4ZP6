#include "ObjGPUData.h"
#include "ImgLoader.h"

#include <vector>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <sstream>
#include <map>



enum ObjGPUData::dataType : short {
    dataV,
    dataVN,
    dataVT,
    dataF,
    dataUSEMTL,
    dataUNKNOWN
};

enum ObjGPUData::mtlDataType : short {
    mtlDataNS,
    mtlDataKA,
    mtlDataKD,
    mtlDataKS,
    mtlDataMAP,
    mtlDataNEWMTL,
    mtlDataUNKNOWN
};

struct ObjGPUData::FullVertex{

    glm::vec3 vertex;
    glm::vec2 uv;
    glm::vec3 normal;

    bool operator <(const FullVertex& that) const{
        return memcmp((void*)this, (void*)&that, sizeof(FullVertex))>0;
    }

};


ObjGPUData::ObjGPUData(const char* objFile, float angle)
{
    loadObject(objFile);

    glGenVertexArrays(1, &vertexArrayObj);
    glBindVertexArray(vertexArrayObj);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vList.size() * sizeof(glm::vec3), &vList[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );


    glGenBuffers(1, &textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, vTextureList.size() * sizeof(glm::vec2), &vTextureList[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, vNormalList.size() * sizeof(glm::vec3), &vNormalList[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, fList.size() * sizeof(GLuint), &fList[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    float minX = 0, maxX = 0;
    float minY = 0, maxY = 0;

    for(int i = 0; i < vList.size(); i++){

        if(vList[i][0] < minX)
            minX = vList[i][0];
        else if(vList[i][0] > maxX)
            maxX = vList[i][0];

        if(vList[i][1] < minY)
            minY = vList[i][1];
        else if(vList[i][1] > maxY)
            maxY = vList[i][1];

    }

    whRatio = (maxX - minX)/(maxY - minY);

    float scaleFactor = 1.0f/(maxY - minY);

    unitScale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
    rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
}


void ObjGPUData::loadObject(const char* fileName) {
    std::string folderName = fileName;

    for(int i = folderName.size() - 1; i >= 0; i--){
        if(folderName[i] == '/' || folderName[i] == '\\'){
            folderName = folderName.substr(0, i+1);
            break;
        }
        if(i == 0)
            folderName = "";
    }

    std::string objFileName = fileName;
    std::string mtlFileName = fileName;
    objFileName += ".obj";
    mtlFileName += ".mtl";

    std::ifstream mtlFile(mtlFileName.c_str(), std::ios::in);

    if(!mtlFile.is_open()){
        printf("Failed to open object %s\n", objFileName.c_str());
        exit(1);
    }

    std::string dataTypeString;
    float xVal, yVal, zVal;
    std::string valString;
    std::stringstream valStream;
    int iVal;

    while(mtlFile >> dataTypeString){

        mtlDataType mtlDataTypeVal = getMtlDataType(dataTypeString);

        switch(mtlDataTypeVal){
            case mtlDataType::mtlDataNEWMTL:
                mtlFile >> valString;
                materials.push_back(Material(valString));
                valString.clear();
                break;

            case mtlDataType::mtlDataNS:
                mtlFile >> xVal;
                materials.back().shine = xVal;
                break;

            case mtlDataType::mtlDataKA:
                mtlFile >> xVal;
                mtlFile >> yVal;
                mtlFile >> zVal;

                materials.back().Ka = glm::vec3(xVal, yVal, zVal);

                break;

            case mtlDataType::mtlDataKD:
                mtlFile >> xVal;
                mtlFile >> yVal;
                mtlFile >> zVal;

                materials.back().Kd = glm::vec3(xVal, yVal, zVal);

                break;

            case mtlDataType::mtlDataKS:
                mtlFile >> xVal;
                mtlFile >> yVal;
                mtlFile >> zVal;

                materials.back().Ks = glm::vec3(xVal, yVal, zVal);

                break;

            case mtlDataType::mtlDataMAP:
            {
                if(materials.back().textureSet)
                    break;
                getline(mtlFile, valString);
                int fileNameLocation = valString.find_last_of("/\\");
                if(fileNameLocation != -1)
                    valString = valString.substr(fileNameLocation + 1);
                while(valString[0] == ' ' || valString[0] == '\t')
                    valString = valString.substr(1);
                if(valString.size() < 4 || valString.substr(valString.size() - 4) != ".dds"){
                    valString = valString.substr(0, valString.find_last_of('.') + 1);
                    valString += "dds";
                }
                materials.back().textureName = valString;
                bool textureExists = false;
                for(int i = 0; i < materials.size() - 1; i++){
                    if(materials[i].textureName == valString){
                        textureExists = true;
                        materials.back().texture = materials[i].texture;
                        break;
                    }
                }
                if(textureExists){
                    valString.clear();
                    break;
                }
                materials.back().texture = loadImage((folderName + valString).c_str());
                materials.back().textureSet = true;
                valString.clear();
                break;
            }

            default:
                break;
        }
    }

    mtlFile.close();

    printf("Loading object %s... ", objFileName.c_str());

    std::ifstream objFile(objFileName.c_str(), std::ios::in);

    if(!objFile.is_open()){
        printf("Failed to open object %s\n", objFileName.c_str());
        exit(1);
    }

    std::vector<glm::vec3> vList_in;
    std::vector<glm::vec2> vTextureList_in;
    std::vector<glm::vec3> vNormalList_in;
    std::vector<GLuint> iVertex;
    std::vector<GLuint> iTexture;
    std::vector<GLuint> iNormal;

    std::vector<unsigned int> materialIndices_in;

    while(objFile >> dataTypeString){

        dataType dataTypeVal = getDataType(dataTypeString);

        switch(dataTypeVal){
            case dataType::dataV:
                objFile >> xVal;
                objFile >> yVal;
                objFile >> zVal;

                vList_in.push_back(glm::vec3(xVal, yVal, zVal));

                break;

            case dataType::dataVT:
                objFile >> xVal;
                objFile >> yVal;

                vTextureList_in.push_back(glm::vec2(xVal, yVal));

                break;

            case dataType::dataVN:
                objFile >> xVal;
                objFile >> yVal;
                objFile >> zVal;

                vNormalList_in.push_back(glm::vec3(xVal, yVal, zVal));

                break;

            case dataType::dataUSEMTL:
            {
                int index = -1;
                objFile >> valString;

                for(int i = 0; i < materials.size(); i++){
                    if(materials[i].materialName == valString){
                        index = i;
                        break;
                    }
                }

                if(index == -1)
                    exit(1);

                valString.clear();

                materialIndices_in.push_back(iVertex.size());
                materialIndices_in.push_back(index);

                break;
            }


            case dataType::dataF:
            {
                char lastChar;

                for(int i = 0; i < 3; i++){
                    getline(objFile, valString, '/');
                    valStream << valString;
                    valString.clear();
                    valStream >> iVal;
                    valStream.str(std::string());
                    valStream.clear();
                    iVertex.push_back(iVal);

                    getline(objFile, valString, '/');
                    valStream << valString;
                    valString.clear();
                    valStream >> iVal;
                    valStream.str(std::string());
                    valStream.clear();
                    iTexture.push_back(iVal);

                    objFile >> iVal;
                    iNormal.push_back(iVal);

                    lastChar = objFile.get();
                }

                if(lastChar != '\n'){
                    while(objFile.peek() == ' ' || objFile.peek() == '\t'){
                        objFile.get();
                    }

                    if(objFile.peek() == '\n')
                        break;

                    iVertex.push_back(iVertex[iVertex.size() - 3]);
                    iTexture.push_back(iTexture[iTexture.size() - 3]);
                    iNormal.push_back(iNormal[iNormal.size() - 3]);

                    iVertex.push_back(iVertex[iVertex.size() - 2]);
                    iTexture.push_back(iTexture[iTexture.size() - 2]);
                    iNormal.push_back(iNormal[iNormal.size() - 2]);

                    getline(objFile, valString, '/');
                    valStream << valString;
                    valString.clear();
                    valStream >> iVal;
                    valStream.str(std::string());
                    valStream.clear();
                    iVertex.push_back(iVal);

                    getline(objFile, valString, '/');
                    valStream << valString;
                    valString.clear();
                    valStream >> iVal;
                    valStream.str(std::string());
                    valStream.clear();
                    iTexture.push_back(iVal);

                    objFile >> iVal;
                    iNormal.push_back(iVal);
                }

                break;
            }

            default:
                break;
        }
    }

    objFile.close();

    int first, last;

    std::map<FullVertex,unsigned int> vertexToOutIndex;

    for(int k = 0; k < materialIndices_in.size()/2; ++k){

        first = materialIndices_in[2*k];
        if((2*k + 2) > (materialIndices_in.size() - 1))
            last = iVertex.size();
        else
            last = materialIndices_in[2*k + 2];

        materialIndices.push_back(fList.size());
        materialIndices.push_back(materialIndices_in[2*k + 1]);

        for(int i = first; i < last; i++){

            FullVertex nextVertex = {vList_in[iVertex[i] - 1], vTextureList_in[iTexture[i] - 1], vNormalList_in[iNormal[i] - 1]};

            std::map<FullVertex,unsigned int>::iterator vLocation = vertexToOutIndex.find(nextVertex);

            if(vLocation == vertexToOutIndex.end()){
                vList.push_back(vList_in[iVertex[i]-1]);
                vTextureList.push_back(vTextureList_in[iTexture[i]-1]);
                vNormalList.push_back(vNormalList_in[iNormal[i]-1]);

                vertexToOutIndex[nextVertex] = vList.size() - 1;
                fList.push_back(vList.size() - 1);
            }
            else {
                fList.push_back(vLocation->second);
            }
        }
    }


    //  Invert all texture v-coordinates for use with DXT compression textures

    for(int i = 0; i < vTextureList.size(); i++){
        vTextureList[i][1] = 1 - vTextureList[i][1];
    }

    printf("DONE\n");

    return;

}


ObjGPUData::dataType ObjGPUData::getDataType(std::string dataTypeString){
    if(dataTypeString == "v")
        return dataType::dataV;
    if(dataTypeString == "vn")
        return dataType::dataVN;
    if(dataTypeString == "vt")
        return dataType::dataVT;
    if(dataTypeString == "f")
        return dataType::dataF;
    if(dataTypeString == "usemtl")
        return dataType::dataUSEMTL;
    else
        return dataType::dataUNKNOWN;
}

ObjGPUData::mtlDataType ObjGPUData::getMtlDataType(std::string dataTypeString){
    if(dataTypeString == "Ns")
        return mtlDataType::mtlDataNS;
    if(dataTypeString == "Ka")
        return mtlDataType::mtlDataKA;
    if(dataTypeString == "Kd")
        return mtlDataType::mtlDataKD;
    if(dataTypeString == "Ks")
        return mtlDataType::mtlDataKS;
    if(dataTypeString.substr(0,3) == "map")
        return mtlDataType::mtlDataMAP;
    if(dataTypeString == "newmtl")
        return mtlDataType::mtlDataNEWMTL;
    else
        return mtlDataType::mtlDataUNKNOWN;
}
