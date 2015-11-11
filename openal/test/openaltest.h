#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <al.h>
#include <alc.h>
#include <alut.h>
#include <windows.h>
//#include "openaltest.c"
void init(void);
ALuint make_al_buffer(char *szPath);
ALuint make_al_source(ALuint buf);
void play(ALuint buffer,ALuint source,ALint source_state);

