
# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV_INCLUDE_DIRS is " ${OpenCV_INCLUDE_DIRS})

add_executable(geometry_test "geometry_test.cpp")
target_link_libraries(geometry_test ${OpenCV_LIBS})

add_executable(highgui_test highgui_test.cpp)
target_link_libraries(highgui_test  ${OpenCV_LIBS})

add_executable(core_test core_test.cpp)
target_link_libraries(core_test ${OpenCV_LIBS})

add_executable(imgproc_test imgproc_test.cpp)
target_link_libraries(imgproc_test ${OpenCV_LIBS})

add_executable(feature2d_test feature2d_test.cpp)
target_link_libraries(feature2d_test ${OpenCV_LIBS})

add_executable(optical_flow optical_flow.cpp)
target_link_libraries(optical_flow ${OpenCV_LIBS})