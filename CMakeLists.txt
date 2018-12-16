#file      CMakeLists.txt
#date      09-12-2018
#project   Kubbler
#author    Warkerings

CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(Kubbler)

INCLUDE_DIRECTORIES(Includes)
LINK_DIRECTORIES(Librairies)

FILE(GLOB_RECURSE SRC Sources/*.cpp Sources/*.c)

SET(CMAKE_CXX_FLAGS -march=nocona)
ADD_EXECUTABLE(Kubbler ${SRC})
TARGET_LINK_LIBRARIES(Kubbler mingw32 opengl32 glfw3)
