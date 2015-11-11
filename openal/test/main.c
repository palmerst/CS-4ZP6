#include "openaltest.h"



int main()
{
    //all the music must stay with same file as main
    ALuint buffer = 0;//buff
    ALuint source = 0;//source
    ALint loop=0;
    ALint source_state;

    init();
    buffer = make_al_buffer("hit.wav");//load
    loop=0;//1 for loop, 0 for not loop
    source = make_al_source(buffer,loop);//set default source
    play(buffer,source,source_state);//play

    return 0;
}
