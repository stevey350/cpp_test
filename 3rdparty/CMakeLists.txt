
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
execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I=${CMAKE_SOURCE_DIR}/3rdparty --cpp_out=${CMAKE_SOURCE_DIR}/3rdparty ${CMAKE_SOURCE_DIR}/3rdparty/proto_addressbook.proto)
add_executable(proto_addressbook_test "proto_addressbook_test.cpp" "proto_addressbook.pb.cc")
add_executable(proto_addressbook_write "proto_addressbook_write.cpp" "proto_addressbook.pb.cc")
add_executable(proto_addressbook_read  "proto_addressbook_read.cpp" "proto_addressbook.pb.cc")
target_link_libraries(proto_addressbook_test protobuf)
target_link_libraries(proto_addressbook_write protobuf)
target_link_libraries(proto_addressbook_read  protobuf)

# abseil
find_package(absl REQUIRED)
add_executable(abseil_test "abseil_test.cpp")
target_link_libraries(abseil_test absl::strings)

# gtest
add_executable(gtest_demo "gtest_demo.cpp")
target_link_libraries(gtest_demo gtest pthread)

