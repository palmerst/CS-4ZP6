#include "openaltest.h"



int main()
{
    //all the music must stay with same file as main
    ALuint buffer = 0;//buff
    ALuint source = 0;//source
    ALint source_state;

    init();
    buffer = make_al_buffer("hit.wav");//load
    source = make_al_source(buffer);//set default source
    play(buffer,source,source_state);//play

    return 0;
}
