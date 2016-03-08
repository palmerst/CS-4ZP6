file(GLOB GAME_SOURCE_FILES "*.cpp")

add_executable(game ${GAME_SOURCE_FILES})


if(WIN32)
    target_link_libraries(game glfw glew opengl32 glu32 gdi32 chipmunk freealut openal winmm)
    add_definitions(-DWIN32)
endif()

if(APPLE)
    
    find_library(CARBON_LIB NAMES Carbon)
    find_library(COCOA_LIB NAMES Cocoa)
    find_library(GL_LIB NAMES OpenGL)
    find_library(COREAUDIO_LIB NAMES CoreAudio)
    find_library(AUDIOTOOLBOX_LIB NAMES AudioToolBox)
    if(AUDIOTOOLBOX_LIB)
        set(FRAMEWORKS ${AUDIOTOOLBOX_LIB} ${FRAMEWORKS})
    endif()
    find_library(IOKIT_LIB NAMES IOKit)
    find_library(CORE_FOUNDATION_LIB CoreFoundation)
    find_library(CORE_VIDEO_LIB CoreVideo)
    set(FRAMEWORKS /System/Library/Frameworks/AudioUnit.framework ${FRAMEWORKS})
    set(FRAMEWORKS /System/Library/Frameworks/ApplicationServices.framework ${FRAMEWORKS})
    set(FRAMEWORKS ${CARBON_LIB} ${COCOA_LIB} ${GL_LIB} ${COREAUDIO_LIB} ${IOKIT_LIB} ${CORE_FOUNDATION_LIB} ${CORE_VIDEO_LIB} ${FRAMEWORKS})

    target_link_libraries(game glfw glew chipmunk freealut openal ${FRAMEWORKS}) 
endif()

if(UNIX AND NOT APPLE)

    target_link_libraries(game glfw glew GL chipmunk freealut openal X11 Xi Xrandr Xxf86vm Xinerama Xcursor pthread dl)
    
endif()


install(TARGETS game RUNTIME DESTINATION ${INSTALL_DEST})
    
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION ${INSTALL_DEST})