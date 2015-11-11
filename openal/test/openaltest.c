#include "openaltest.h"


void init(void)
{
    ALenum err;

    alutInit(0,NULL);
    alGetError();// Clear the error code.

    //define a listener
	ALfloat listenerPosition[] = {0.0f, 0.0f, 0.0f};
	ALfloat listenerVelocity[] = {0.0f, 0.0f, 0.0f};
	ALfloat listenerOrientation[] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};
	alListenerfv(AL_POSITION,listenerPosition);
	alListenerfv(AL_VELOCITY,listenerVelocity);
	alListenerfv(AL_ORIENTATION,listenerOrientation);
}

ALuint make_al_buffer(char *szPath)
{
    ALuint ret = 0;
    ALsizei size, freq;//load audio steam to buff
    ALenum format;
    ALvoid *data = NULL;

    alGenBuffers((ALuint)1, &ret);
    data = alutLoadMemoryFromFile(szPath,&format,&size,&freq);
    freq = 11025;
    alBufferData(ret,format,data,size,freq);
    alutUnloadWAV(format, data, size,(ALsizei)freq);

    return ret;
}

ALuint make_al_source(ALuint buf)//source able to invite more parm later but now set everything as default
{
    ALuint ret = 0;

    alGenSources((ALuint)1, &ret);
    alSourcei(ret, AL_BUFFER, buf);//source
    alSourcef(ret, AL_PITCH, 1.0f);
    alSourcef(ret, AL_GAIN, 1.0f);
    alSource3f(ret, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(ret, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(ret, AL_LOOPING, AL_FALSE);

    return ret;
}

void play(ALuint buffer,ALuint source,ALint source_state){
    alSourcePlay(source);

    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    // check for errors
    while (source_state == AL_PLAYING)
    {
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        // check for errors
    }

    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

}
