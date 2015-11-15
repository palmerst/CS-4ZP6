
#ifndef GAMEINPUT_H_INCLUDED
#define GAMEINPUT_H_INCLUDED

#include "include/GLFW/glfw3.h"

//set 8 keys wsad and iojk
//wsad=up down left right, and i=a o=b j=c k=d for simulation handle


//since that user may using the multiple keys to input ,so it is necessary to
//use bit map for the situation

//here define the key which is pressing.
#define INPUT_OP_UP		    0x00000001
#define INPUT_OP_LEFT       0x00000002
#define INPUT_OP_DOWN	    0x00000004
#define INPUT_OP_RIGHT      0x00000008
#define INPUT_OP_A          0x00000010
#define INPUT_OP_B			0x00000020
#define INPUT_OP_C          0x00000040
#define INPUT_OP_D          0x00000080

//here define keys not pressed but player just press it at first time
#define INPUT_OP_UP_START    0x00000100
#define INPUT_OP_LEFT_START  0x00000200
#define INPUT_OP_DOWN_START  0x00000400
#define INPUT_OP_RIGHT_START 0x00000800
#define INPUT_OP_A_START     0x00001000
#define INPUT_OP_B_START	 0x00002000
#define INPUT_OP_C_START     0x00004000
#define INPUT_OP_D_START     0x00008000

//player release the bottom here
#define INPUT_OP_UP_STOP     0x00010000
#define INPUT_OP_LEFT_STOP   0x00020000
#define INPUT_OP_DOWN_STOP   0x00040000
#define INPUT_OP_RIGHT_STOP  0x00080000
#define INPUT_OP_A_STOP		 0x00100000
#define INPUT_OP_B_STOP		 0x00200000
#define INPUT_OP_C_STOP      0x00400000
#define INPUT_OP_D_STOP      0x00800000


typedef unsigned int uint;

typedef struct _tagGameInput
{
    //record 8 key
	uint uUp;
	uint uLeft;
	uint uDown;
	uint uRight;
	uint uA;
	uint uB;
	uint uC;
	uint uD;

    //record current input
	uint   uInputFlags;

	//record last input
	uint   uPreFlags;

	GLFWwindow *wnd;
}gameInput;

//initial and cleanup
bool gameinput_initialze(GLFWwindow* wnd);
void gameinput_cleanup();

//get user input
uint get_input_msg();

#endif // GAMEINPUT_H_INCLUDED
