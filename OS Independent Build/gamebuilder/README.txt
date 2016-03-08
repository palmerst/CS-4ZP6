Building the game requires cmake:  https://cmake.org/download/

If using Windows, mingw-w64 is required:  http://sourceforge.net/projects/mingw-w64/
This is a fork of mingw and much more up to date.  Regular mingw installations will likely not include the pthreads library and chipmunk will not build.
Install with default settings (threads should be set to POSIX).


To build, navigate to the local '/source/build' directory and run via terminal/cmd and run:

    FOR MAC/LINUX:

    cmake -G "Unix Makefiles" ..
    make
    make install 

    
    FOR WINDOWS**:
    
    cmake -G "MinGW Makefiles" ..
    mingw32-make
    mingw32-make install
    
    
    ** Ensure that the generator is detecting gcc v 5.3.0 that was installed with mingw-w64.  If it is detecting a different version you have installed, you will either need to put the location of the mingw-w64 bin directory before all others on the PATH env. variable, or add CC and CXX environment variables that point to the correct gcc.exe and g++.exe

The game will install to the local '/game' directory.
