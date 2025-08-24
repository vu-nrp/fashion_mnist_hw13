cmake_minimum_required(VERSION 3.7)

project(xla-lib-protobuf C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Protobuf REQUIRED)

include(ProtobufGenerateDfpost)
include(EnableMsvcSystemInclude)

## XLA proto files
file(GLOB_RECURSE XLA_PROTO_FILES
    ${XLA_SOURCE_DIR}/xla/*.proto
)

set(Protobuf_IMPORT_DIRS ${TSL_SOURCE_DIR})

protobuf_generate_dfpost(XLA_PROTO_SRCS XLA_PROTO_HDRS ${XLA_SOURCE_DIR} ${XLA_PROTO_FILES})

set(XLA_PROTOBUF_LIB "xla-lib-protobuf")
add_library(${XLA_PROTOBUF_LIB} STATIC ${XLA_PROTO_SRCS} ${XLA_PROTO_HDRS} ${XLA_PROTO_FILES})

if (MSVC AND WIN32)
    if (MSVC_VERSION GREATER_EQUAL 1914)
        target_compile_definitions(${XLA_PROTOBUF_LIB} PUBLIC _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS)
    endif()
endif()

set_target_properties(${XLA_PROTOBUF_LIB} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
enable_msvc_system_include(${XLA_PROTOBUF_LIB})
target_include_directories(${XLA_PROTOBUF_LIB}
SYSTEM
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
    PRIVATE
        ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(${XLA_PROTOBUF_LIB}
PRIVATE
    ${Protobuf_LIBRARIES}
    tsl-lib-protobuf
)
