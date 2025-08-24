cmake_minimum_required(VERSION 3.7)

project(proto_text LANGUAGES C CXX)

find_package(Protobuf REQUIRED)

add_executable(proto_text
    gen_proto_text_functions_lib.cc
    gen_proto_text_functions_lib.h
    gen_proto_text_functions.cc
)


target_include_directories(${PROJECT_NAME}
SYSTEM PUBLIC
    "../../.."
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    ${Protobuf_LIBRARIES}
    tsl-lib
)
