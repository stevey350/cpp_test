
add_executable(eigen_test "eigen_test.cpp")

# gflags
find_package(gflags REQUIRED)

add_executable(gflags_test "gflags_test.cpp")
target_link_libraries(gflags_test gflags)

# glog
# find_package(glog REQUIRED)

add_executable(glog_test glog_test.cpp)
target_link_libraries(glog_test glog)

# Protocol Buffers
find_package(Protobuf REQUIRED)
message(STATUS "DST_DIR=${PROTOBUF_PROTOC_EXECUTABLE}")
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I=${CMAKE_SOURCE_DIR}/3rdparty --cpp_out=${CMAKE_SOURCE_DIR}/3rdparty ${CMAKE_SOURCE_DIR}/3rdparty/proto_person.proto)
add_executable(proto_test "proto_test.cpp" "proto_person.pb.cc")
target_link_libraries(proto_test protobuf)
