cmake_minimum_required(VERSION 2.8)

project(game)

include(ExternalProject)

set(INSTALL_DIR ${CMAKE_SOURCE_DIR})
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(LIB_SOURCE_LOCATION ${CMAKE_SOURCE_DIR}/libsrc)
set(INSTALL_DEST ${CMAKE_SOURCE_DIR}/../game)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -O2 -DGLM_FORCE_RADIANS -DGLEW_STATIC -DALUT_STATIC -DAL_LIBTYPE_STATIC -std=c++11")

if(WIN32)
    set(GENERATOR_NAME "MinGW Makefiles")
endif()

if(UNIX)
    if(APPLE)
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(GENERATOR_NAME "Unix Makefiles")
        endif()
    else()
        set(GENERATOR_NAME "Unix Makefiles")
    endif()
endif()
    

add_library(chipmunk STATIC IMPORTED)
add_library(glfw STATIC IMPORTED)
add_library(glew STATIC IMPORTED)
add_library(openal STATIC IMPORTED)
add_library(freealut STATIC IMPORTED)

set_property(TARGET chipmunk PROPERTY IMPORTED_LOCATION ${LIB_DIR}/libchipmunk.a)
set_property(TARGET glfw PROPERTY IMPORTED_LOCATION ${LIB_DIR}/libglfw3.a)
set_property(TARGET freealut PROPERTY IMPORTED_LOCATION ${LIB_DIR}/libalut.a)

if(WIN32)
    set_property(TARGET glew PROPERTY IMPORTED_LOCATION ${LIB_DIR}/libglew32.a)
    set_property(TARGET openal PROPERTY IMPORTED_LOCATION ${LIB_DIR}/libOpenAL32.a)
else()
    set_property(TARGET glew PROPERTY IMPORTED_LOCATION ${LIB_DIR}/libGLEW.a)
    set_property(TARGET openal PROPERTY IMPORTED_LOCATION ${LIB_DIR}/libopenal.a)
endif()

if(NOT EXISTS "${LIB_DIR}/libchipmunk.a")
    ExternalProject_Add(project_chipmunk
       URL ${LIB_SOURCE_LOCATION}/chipmunk
       PREFIX ./chipmunk
       INSTALL_DIR ${INSTALL_DIR}
       CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
       CMAKE_GENERATOR ${GENERATOR_NAME}
    )
    add_dependencies(chipmunk project_chipmunk)
endif()

if(NOT EXISTS "${LIB_DIR}/libglfw3.a")
    ExternalProject_Add(project_glfw
       URL ${LIB_SOURCE_LOCATION}/glfw
       PREFIX ./glfw
       INSTALL_DIR ${INSTALL_DIR}
       CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
       CMAKE_GENERATOR ${GENERATOR_NAME}
    )
    add_dependencies(glfw project_glfw)
endif()

if(NOT (EXISTS "${LIB_DIR}/libglew32.a" OR EXISTS "${LIB_DIR}/libGLEW.a"))
    ExternalProject_Add(project_glew
        URL ${LIB_SOURCE_LOCATION}/glew
        PREFIX ./glew
        INSTALL_DIR ${INSTALL_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
        CMAKE_GENERATOR ${GENERATOR_NAME}
    )
    add_dependencies(glew project_glew)
endif()

if(NOT (EXISTS "${LIB_DIR}/libOpenAL32.a" OR EXISTS "${LIB_DIR}/libopenal.a"))
    ExternalProject_Add(project_openal
        URL ${LIB_SOURCE_LOCATION}/openal-soft
        PREFIX ./openal-soft
        INSTALL_DIR ${INSTALL_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
        CMAKE_GENERATOR ${GENERATOR_NAME}
    )
    add_dependencies(openal project_openal)
endif()

if(NOT EXISTS "${LIB_DIR}/libalut.a")
    ExternalProject_Add(project_freealut
        URL ${LIB_SOURCE_LOCATION}/freealut
        PREFIX ./freealut
        INSTALL_DIR ${INSTALL_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
        CMAKE_GENERATOR ${GENERATOR_NAME}
    )
    add_dependencies(project_freealut openal)
    add_dependencies(freealut project_freealut)
endif()

add_subdirectory(src)
