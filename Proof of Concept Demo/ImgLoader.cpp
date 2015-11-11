#include <fstream>
#include <cstdlib>
#include "include/gl/glew.h"

/******************************************************************************************************************************
 ***  Loads DDS file type images for use as textures                                                                        ***
 ***  Adapted from online code;   source:  http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/   ***
 ***  A large amount is unchanged from the source.                                                                          ***
 ******************************************************************************************************************************/


/***  Defines copied from source. ***/

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII


GLuint loadImage(const char* imageFileName){

    printf("Loading texture %s... ", imageFileName);

    std::ifstream imageFile(imageFileName, std::ifstream::binary);

    if(!imageFile.is_open()){
        printf("Failed to open texture %s\n", imageFileName);
        exit(1);
    }

    unsigned char headerBuffer[128];

    imageFile.read((char*)headerBuffer, 128);

    unsigned int h = *(unsigned int*)&(headerBuffer[12]);
    unsigned int w = *(unsigned int*)&(headerBuffer[16]);
    unsigned int size = *(unsigned int*)&(headerBuffer[20]);
    unsigned int mipMapCount = *(unsigned int*)&(headerBuffer[28]);
    unsigned int fourCC = *(unsigned int*)&(headerBuffer[84]);

    delete(headerBuffer);

    unsigned char* dataBuffer;

    if(mipMapCount == 1)
        dataBuffer = new unsigned char[size];
    else{
        size *= 2;
        dataBuffer = new unsigned char[2*size];
    }

    imageFile.read((char*)dataBuffer, size);
    imageFile.close();

    /***  The following snippet is copied directly from the source. ***/

    /******************
     *** BEGIN COPY ***
     ******************/

    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch(fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		delete(dataBuffer);
		return 0;
	}

    /*** Create OpenGL texture ***/
	GLuint textureID;
	glGenTextures(1, &textureID);

	/*** "Bind" the newly created texture : all future texture functions will modify this texture ***/
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /*** load the mipmaps ***/
    for (unsigned int level = 0; level < mipMapCount && (w || h); ++level)
    {
        unsigned int mipMapSize = ((w+3)/4)*((h+3)/4)*blockSize;

        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, w, h,
            0, mipMapSize, dataBuffer + offset);

        offset += mipMapSize;
        w /= 2;
        h /= 2;

        if(!w)
            w = 1;
        if(!h)
            h = 1;

    }

    /****************
     *** END COPY ***
     ****************/

    printf("DONE\n");

    delete(dataBuffer);
    return textureID;
}
