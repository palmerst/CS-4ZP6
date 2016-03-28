#please use 'make clean' to clean the directory of intermediate build files and the executable
#simply typing 'make' will compile all source code files to object files .o, and then link all
#object files into an executable
#we are using a lot of makefile macros

#changing platform dependant stuff, do not change this
# Linux (default)
CC = gcc
CXX = g++
LDFLAGS = -lGL -lGLU -lglut 
CFLAGS = -Wall -g -Os
CXXFLAGS = -g -Os -Dlinux -DGLM_FORCE_RADIANS -DGLEW_STATIC -std=c++11
EXEEXT=
RM=rm

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	EXEEXT=.exe #on windows applications must have .exe extension
	RM=del #rm command for windows powershell
    LDFLAGS = -Llib/win -lglfw3 -lglew32 -lopengl32 -lglu32 -lgdi32 -lchipmunk -lalut -lOpenAL32.dll
    CXXFLAGS = -g -Os -DWIN32 -DGLM_FORCE_RADIANS -DGLEW_STATIC -DAL_LIBTYPE_STATIC -DALUT_STATIC -std=c++11
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		LDFLAGS = -Llib/linux -lglfw3 -lGLEW -lGL -lchipmunk -lalut -lopenal -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lpthread -ldl -Wl,-Rlib/linux
		CXXFLAGS = -g -Os -DLINUX -DGLM_FORCE_RADIANS -DGLEW_STATIC -std=c++11
	endif
	# OS X
	ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -Llib/apple -framework Carbon -framework OpenGL -lglfw3 -lGLEW -lchipmunk
    CXXFLAGS = -g -Os -DAPPLE -DGLM_FORCE_RADIANS -DGLEW_STATIC -std=c++11
	endif
endif

#change the 't1' name to the name you want to call your application
PROGRAM_NAME := Demo
C_SRCS := $(wildcard *.c)
CXX_SRCS := $(wildcard *.cpp)
C_OBJS := $(C_SRCS:.c=.o)
CXX_OBJS := $(CXX_SRCS:.cpp=.o)
OBJS := $(C_OBJS) $(CXX_OBJS)

#run target to compile and build, and then launch the executable
run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)$(EXEEXT)

#when adding additional source files, such as boilerplateClass.cpp
#or yourFile.cpp, add the filename with an object extension below
#ie. boilerplateClass.o and yourFile.o
#make will automatically know that the objectfile needs to be compiled
#form a cpp source file and find it itself :)
$(PROGRAM_NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(PROGRAM_NAME) $(LDFLAGS)

clean:
	$(RM) *.o $(PROGRAM_NAME)$(EXEEXT)
