
#include "gameInput.h"
#include <assert.h>

static gameInput *s_input = NULL;

bool gameinput_initialze(GLFWwindow* wnd)
{
    if(s_input != NULL)
        return false;

    s_input = new gameInput;

    //here define the input configuration
    s_input->uUp = GLFW_KEY_W;
	s_input->uLeft = GLFW_KEY_A;
	s_input->uDown = GLFW_KEY_S;
	s_input->uRight = GLFW_KEY_D;
	s_input->uA = GLFW_KEY_I;
	s_input->uB = GLFW_KEY_O;
	s_input->uC = GLFW_KEY_J;
	s_input->uD = GLFW_KEY_K;

    s_input->uPreFlags = 0;
    s_input->uInputFlags = 0;
    s_input->wnd = wnd;

    return true;
}

void gameinput_cleanup()
{
    if(s_input != NULL)
    {
        delete s_input;
        s_input = NULL;
    }
}

//get user input
uint get_input_msg()
{
    int state = 0;

    assert(s_input!=NULL);

    s_input->uPreFlags = (s_input->uPreFlags&0x000e0000)|(s_input->uInputFlags&0x0000ffff);
    s_input->uInputFlags = 0;


	state = glfwGetKey(s_input->wnd,s_input->uUp);
	switch(state)
	{
    case GLFW_PRESS:
        if(!(s_input->uPreFlags&INPUT_OP_UP_START ||
                s_input->uPreFlags&INPUT_OP_UP))
            s_input->uInputFlags |= INPUT_OP_UP_START;
        else
            s_input->uInputFlags |= INPUT_OP_UP;
        break;
    case GLFW_RELEASE:
        if(s_input->uPreFlags&INPUT_OP_UP_START ||
                s_input->uPreFlags&INPUT_OP_UP)
            s_input->uInputFlags |= INPUT_OP_UP_STOP;
        break;
    case GLFW_REPEAT:
        s_input->uInputFlags |= INPUT_OP_UP;
        break;
    default:
        break;
	}

	state = glfwGetKey(s_input->wnd,s_input->uLeft);
	switch(state)
	{
    case GLFW_PRESS:
        if(!(s_input->uPreFlags&INPUT_OP_LEFT_START ||
                s_input->uPreFlags&INPUT_OP_LEFT))
            s_input->uInputFlags |= INPUT_OP_LEFT_START;
        else
            s_input->uInputFlags |= INPUT_OP_LEFT;
        break;
    case GLFW_RELEASE:
        if(s_input->uPreFlags&INPUT_OP_LEFT_START ||
                s_input->uPreFlags&INPUT_OP_LEFT)
            s_input->uInputFlags |= INPUT_OP_LEFT_STOP;
        break;
    case GLFW_REPEAT:
        s_input->uInputFlags |= INPUT_OP_LEFT;
        break;
    default:
        break;
	}

	state = glfwGetKey(s_input->wnd,s_input->uRight);
	switch(state)
	{
    case GLFW_PRESS:
        if(!(s_input->uPreFlags&INPUT_OP_RIGHT_START ||
                s_input->uPreFlags&INPUT_OP_RIGHT))
            s_input->uInputFlags |= INPUT_OP_RIGHT_START;
        else
            s_input->uInputFlags |= INPUT_OP_RIGHT;
        break;
    case GLFW_RELEASE:
        if(s_input->uPreFlags&INPUT_OP_RIGHT_START ||
                s_input->uPreFlags&INPUT_OP_RIGHT)
            s_input->uInputFlags |= INPUT_OP_RIGHT_STOP;
        break;
    case GLFW_REPEAT:
        s_input->uInputFlags |= INPUT_OP_RIGHT;
        break;
    default:
        break;
	}

    state = glfwGetKey(s_input->wnd,s_input->uDown);
	switch(state)
	{
    case GLFW_PRESS:
        if(!(s_input->uPreFlags&INPUT_OP_DOWN_START ||
                s_input->uPreFlags&INPUT_OP_DOWN))
            s_input->uInputFlags |= INPUT_OP_DOWN_START;
        else
            s_input->uInputFlags |= INPUT_OP_DOWN;
        break;
    case GLFW_RELEASE:
        if(s_input->uPreFlags&INPUT_OP_DOWN_START ||
                s_input->uPreFlags&INPUT_OP_DOWN)
            s_input->uInputFlags |= INPUT_OP_DOWN_STOP;
        break;
    case GLFW_REPEAT:
        s_input->uInputFlags |= INPUT_OP_DOWN;
        break;
    default:
        break;
	}

    state = glfwGetKey(s_input->wnd,s_input->uA);
	switch(state)
	{
    case GLFW_PRESS:
        if(!(s_input->uPreFlags&INPUT_OP_A_START ||
                s_input->uPreFlags&INPUT_OP_A))
            s_input->uInputFlags |= INPUT_OP_A_START;
        else
            s_input->uInputFlags |= INPUT_OP_A;
        break;
    case GLFW_RELEASE:
        if(s_input->uPreFlags&INPUT_OP_A_START ||
                s_input->uPreFlags&INPUT_OP_A)
            s_input->uInputFlags |= INPUT_OP_A_STOP;
        break;
    case GLFW_REPEAT:
        s_input->uInputFlags |= INPUT_OP_A;
        break;
    default:
        break;
	}

    state = glfwGetKey(s_input->wnd,s_input->uB);
	switch(state)
	{
    case GLFW_PRESS:
        if(!(s_input->uPreFlags&INPUT_OP_B_START ||
                s_input->uPreFlags&INPUT_OP_B))
            s_input->uInputFlags |= INPUT_OP_B_START;
        else
            s_input->uInputFlags |= INPUT_OP_B;
        break;
    case GLFW_RELEASE:
        if(s_input->uPreFlags&INPUT_OP_B_START ||
                s_input->uPreFlags&INPUT_OP_B)
            s_input->uInputFlags |= INPUT_OP_B_STOP;
        break;
    case GLFW_REPEAT:
        s_input->uInputFlags |= INPUT_OP_B;
        break;
    default:
        break;
	}

    state = glfwGetKey(s_input->wnd,s_input->uC);
	switch(state)
	{
    case GLFW_PRESS:
        if(!(s_input->uPreFlags&INPUT_OP_C_START ||
                s_input->uPreFlags&INPUT_OP_C))
            s_input->uInputFlags |= INPUT_OP_C_START;
        else
            s_input->uInputFlags |= INPUT_OP_C;
        break;
    case GLFW_RELEASE:
        if(s_input->uPreFlags&INPUT_OP_C_START ||
                s_input->uPreFlags&INPUT_OP_C)
            s_input->uInputFlags |= INPUT_OP_C_STOP;
        break;
    case GLFW_REPEAT:
        s_input->uInputFlags |= INPUT_OP_C;
        break;
    default:
        break;
	}

    state = glfwGetKey(s_input->wnd,s_input->uD);
	switch(state)
	{
    case GLFW_PRESS:
        if(!(s_input->uPreFlags&INPUT_OP_D_START ||
                s_input->uPreFlags&INPUT_OP_D))
            s_input->uInputFlags |= INPUT_OP_D_START;
        else
            s_input->uInputFlags |= INPUT_OP_D;
        break;
    case GLFW_RELEASE:
        if(s_input->uPreFlags&INPUT_OP_D_START ||
                s_input->uPreFlags&INPUT_OP_D)
            s_input->uInputFlags |= INPUT_OP_D_STOP;
        break;
    case GLFW_REPEAT:
        s_input->uInputFlags |= INPUT_OP_D;
        break;
    default:
        break;
	}

    return s_input->uInputFlags;
}
