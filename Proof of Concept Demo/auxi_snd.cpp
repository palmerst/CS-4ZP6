#include "auxi_snd.h"
#include <stdlib.h>

static int s_initialize = 0;

//openal initialize
int snd_initialize()
{
    int bOK = 1;

	if(s_initialize==1)
        return bOK;

	// Initialize OpenAL.
	alutInit(0,NULL);

	// Clear the error code.
	alGetError();

    //source setting
	ALfloat listenerPosition[] = {0.0f, 0.0f, 0.0f};
	ALfloat listenerVelocity[] = {0.0f, 0.0f, 0.0f};
	ALfloat listenerOrientation[] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};

	alListenerfv(AL_POSITION,listenerPosition);
	if (alGetError()!=AL_NO_ERROR)
		bOK = 0;

	alListenerfv(AL_VELOCITY,listenerVelocity);
	if (alGetError()!=AL_NO_ERROR)
		bOK = 0;

	alListenerfv(AL_ORIENTATION,listenerOrientation);
	if (alGetError()!=AL_NO_ERROR)
		bOK = 0;

	return s_initialize=bOK;
}

//clean entire openal
void snd_cleanup()
{
	if(s_initialize==1)
	{
		alutExit();
		s_initialize = 0;
	}
}

//base on http://ffainelli.github.io/openal-example/
auxi_snd *snd_new(char* szPath,int loop)
{
    int bOK = 1;
	ALenum  format;
	ALsizei size;
	ALvoid* data;
	ALfloat freq;
	auxi_snd *snd;

    if(s_initialize==0)
        return NULL;

	if(alGetError() != AL_NO_ERROR)
		bOK = 0;

    snd = (auxi_snd*)malloc(sizeof(auxi_snd));
    snd->audioBuffer = 0;
    snd->audioSource = 0;

	if(bOK == 1)
	{
		alGenBuffers(1,&snd->audioBuffer);
		if (alGetError() != AL_NO_ERROR)
			bOK = 0;
	}

	if(bOK == 1)
	{
		alGenSources(1,&snd->audioSource);
		if(alGetError() != AL_NO_ERROR)
			bOK = 0;
	}

	if(bOK == 1)
	{
        data = alutLoadMemoryFromFile(szPath,&format,&size,&freq);
		bOK =  (data!=NULL) ? 1:0;
	}

	if(bOK == 1)
	{
		alBufferData(snd->audioBuffer, format, data, size, (ALsizei)freq);
		if(alGetError() != AL_NO_ERROR)
			bOK = 0;
	}

	if(bOK == 1)
	{
		// Unload the WAV file. It's not needed now.
		alutUnloadWAV(format, data, size,(ALsizei)freq);
		if(alGetError() != AL_NO_ERROR)
			bOK = 0;
	}

	if(bOK == 1)
	{
		alSourcei(snd->audioSource,AL_BUFFER,snd->audioBuffer);
		if (alGetError()!=AL_NO_ERROR)
			bOK = 0;
	}

	if(bOK == 1)
	{
		// Position of the source of the sound.
		ALfloat sourcePosition[] = { 0.0f, 0.0f, 0.0f };

		// Velocity of the source of the sound.
		ALfloat sourceVelocity[] = { 0.0f, 0.0f, 0.0f };

		alSourcef(snd->audioSource, AL_PITCH, 1.0f);
		alSourcef(snd->audioSource, AL_GAIN, 1.0f);
		alSourcefv(snd->audioSource, AL_POSITION, sourcePosition);
		alSourcefv(snd->audioSource, AL_VELOCITY, sourceVelocity);
		alSourcei(snd->audioSource, AL_LOOPING, loop);

		snd->loop = loop;

		if(alGetError() != AL_NO_ERROR)
			bOK = 0;
	}

	if(bOK==0)
    {
        snd_free(snd);
        return NULL;
    }
	else
		return snd;
}

void snd_free(auxi_snd* snd)
{
    if( snd == NULL )
        return;
    if (snd->audioSource!=0)
       alDeleteSources(1,&snd->audioSource);

    if (snd->audioBuffer!=0)
        alDeleteBuffers(1,&snd->audioBuffer);

    snd->audioBuffer = 0;
    snd->audioSource = 0;
}

int snd_play(auxi_snd* snd)
{
    if(snd->audioSource==0)
        return 1;

    alSourcePlay(snd->audioSource);

    return (alGetError() == AL_NO_ERROR);
}

