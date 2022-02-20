cmake_minimum_required(VERSION 2.6)
project(vscode_cmake)   # 工程vscode_cmake

# C++11, dubug模式
set(CMAKE_BUILD_TYPE Debug)     # Release
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g")


message(STATUS "root This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "root This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 添加子文件夹
add_subdirectory(OpenCV)
add_subdirectory(Cxx)
add_subdirectory(3rdparty)


add_executable(${PROJECT_NAME} "main.cpp")
