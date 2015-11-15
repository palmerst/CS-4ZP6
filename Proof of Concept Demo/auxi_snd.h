
#ifndef AUXI_SND_H
#define AUXI_SND_H

#ifndef NULL
#define NULL 0
#endif // NULL

#include <alut.h>

int snd_initialize();//initialize
void snd_cleanup();//clean when exit

//one auxi_snd repersent a new music file
typedef struct _tag_auxi_snd
{
    int    loop;
	ALuint audioBuffer;   //buff
	ALuint audioSource;   //source
}auxi_snd;

//read wav
//read wav path
auxi_snd *snd_new(char* szPath,int loop);

//clean
void      snd_free(auxi_snd* snd);

int snd_play(auxi_snd* snd);     //play


#endif // AUXI_SND_H
