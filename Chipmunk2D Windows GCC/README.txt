This should make compiling w/ gcc on windows easier.  I made changes to the cmake files and added the required libraries + added a batch script for compiling.


TO COMPILE:


YOU WILL NEED:		

MinGW		

I recommend getting codeblocks x86 if you don't have it and installing the version that includes MinGW as codeblocks is a very good IDE for C/C++.



cmake

https://cmake.org/download/    -- use win32 installer + select option to add to PATH

	

Make sure that the mingw/bin and cmake folders are in the PATH variable after installing so they can be run anywhere from the command line.  If you are using codeblocks the mingw/bin directory is in program files (x86)/codeblocks/mingw/bin.   I *think* cmake has an option to add to PATH when installing.


	
Then just run the win32-gcc-compile.bat file in the Chipmunk-7.0.1 directory.  If everything completes successfully the chipmunk library files will be in build/lib and the demo will be in build/demo in the Chipmunk-7.0.1 directory.