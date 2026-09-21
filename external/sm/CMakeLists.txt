cmake_minimum_required(VERSION 3.20)

project(SM) 

set(SOURCE_FILES
    src/MathUtil.cpp
    src/Matrix3x3.cpp
    src/Matrix3x4.cpp
    src/Orientations.cpp
    src/Quaternion.cpp
    src/Transformations.cpp
    src/Vec2.cpp
    src/Vec3.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)