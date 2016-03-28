#include "gtest/gtest.h"
#include "gl/glew.h"    
#include "GLFW/glfw3.h" 
  
int main(int argc, char **argv){
    
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW");
        exit(1);
    }
    
    GLFWwindow* window = glfwCreateWindow(100, 100, "", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    glewExperimental = true;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(3);
    }
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}