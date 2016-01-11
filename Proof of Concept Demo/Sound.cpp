#include "Sound.h"
#include <cstdlib>
#include <cstdio>

//based on http://ffainelli.github.io/openal-example/
Sound::Sound(char* path, int loop)
{
    int LOAD_OK = 1;
	ALenum  format;
	ALsizei size;
	ALvoid* data;
	ALfloat freq;

	if(alGetError() != AL_NO_ERROR)
		LOAD_OK = 0;

    audioBuffer = 0;
    audioSource = 0;

	if(LOAD_OK == 1)
	{
		alGenBuffers(1,&audioBuffer);
		if (alGetError() != AL_NO_ERROR)
			LOAD_OK = 0;
	}

	if(LOAD_OK == 1)
	{
		alGenSources(1,&audioSource);
		if(alGetError() != AL_NO_ERROR)
			LOAD_OK = 0;
	}

	if(LOAD_OK == 1)
	{
        data = alutLoadMemoryFromFile(path,&format,&size,&freq);
		LOAD_OK =  (data!=NULL) ? 1:0;
	}

	if(LOAD_OK == 1)
	{
		alBufferData(audioBuffer, format, data, size, (ALsizei)freq);
		if(alGetError() != AL_NO_ERROR)
			LOAD_OK = 0;
	}

	if(LOAD_OK == 1)
	{
		// Unload the WAV file. It's not needed now.
		alutUnloadWAV(format, data, size,(ALsizei)freq);
		if(alGetError() != AL_NO_ERROR)
			LOAD_OK = 0;
	}

	if(LOAD_OK == 1)
	{
		alSourcei(audioSource,AL_BUFFER,audioBuffer);
		if (alGetError()!=AL_NO_ERROR)
			LOAD_OK = 0;
	}

	if(LOAD_OK == 1)
	{
		// Position of the source of the sound.
		ALfloat sourcePosition[] = { 0.0f, 0.0f, 0.0f };

		// Velocity of the source of the sound.
		ALfloat sourceVelocity[] = { 0.0f, 0.0f, 0.0f };

		alSourcef(audioSource, AL_PITCH, 1.0f);
		alSourcef(audioSource, AL_GAIN, 1.0f);
		alSourcefv(audioSource, AL_POSITION, sourcePosition);
		alSourcefv(audioSource, AL_VELOCITY, sourceVelocity);
		alSourcei(audioSource, AL_LOOPING, loop);

		if(alGetError() != AL_NO_ERROR)
			LOAD_OK = 0;
	}

    if(!LOAD_OK)
    {
        printf("Failed to load sound: %s", path);
        exit(5);
    }
}


Sound::~Sound(){
    if (audioSource!=0)
       alDeleteSources(1,&audioSource);

    if (audioBuffer!=0)
        alDeleteBuffers(1,&audioBuffer);
}



void Sound::play()
{
    alSourcePlay(audioSource);
}

