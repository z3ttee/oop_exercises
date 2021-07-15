cmake_minimum_required(VERSION 3.19)
project(gracomp)

set(CMAKE_CXX_STANDARD 11)

# IMPORTANT TO ADD THIS LINE BEFORE add_executable !!!
link_libraries("-static -lmingw32
-Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32
-lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32
-lversion -luuid -static-libgcc -lhid -lsetupapi -static-libstdc++")

# Add sdlinterf.c to executable
add_executable(${PROJECT_NAME} main.cpp include/sdlinterf.c color/color.h color/color.cpp rect/Rect.cpp rect/Rect.h circ/circ.cpp circ/circ.h parent/GraphicObject.cpp parent/GraphicObject.h comp/comp.cpp comp/comp.h)

# ADD SDL2 TO THE LINKER
set(SDL2_DIR F:/Coding/libraries/SDL2)
set(SDL2_LIB_DIR ${SDL2_DIR}/lib)
set(SDL2_INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include)

include_directories(${SDL2_DIR}/include)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/libSDL2.dll.a ${SDL2_LIB_DIR}/libSDL2main.a ${SDL2_INCLUDE_FILES})
