cmake_minimum_required(VERSION 3.7)

# Double colon in target name means ALIAS or IMPORTED target.
cmake_policy(SET CMP0028 NEW)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions(
        "-DNOMINMAX"
        "-D_WINSOCKAPI_"
        "-DTSL_COMPILE_LIBRARY"
    )

endif()

project(tsl-lib C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(TSL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "TSL lib sources" FORCE)  

find_package(Protobuf REQUIRED)

include(ProtobufGenerateDfpost)
include(EnableMsvcSystemInclude)

## TSL proto files
file(GLOB_RECURSE TSL_PROTO_FILES
    ${TSL_SOURCE_DIR}/tsl/*.proto
)

protobuf_generate_dfpost(TSL_PROTO_SRCS TSL_PROTO_HDRS ${TSL_SOURCE_DIR} ${TSL_PROTO_FILES})

set(TSL_PROTOBUF_LIB "tsl-lib-protobuf")
add_library(${TSL_PROTOBUF_LIB} STATIC ${TSL_PROTO_SRCS} ${TSL_PROTO_HDRS} ${TSL_PROTO_FILES})

if (MSVC AND WIN32)
    if (MSVC_VERSION GREATER_EQUAL 1914)
        target_compile_definitions(${TSL_PROTOBUF_LIB} PUBLIC _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS)
    endif()
endif()

set_target_properties(${TSL_PROTOBUF_LIB} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
enable_msvc_system_include(${TSL_PROTOBUF_LIB})
target_include_directories(${TSL_PROTOBUF_LIB}
SYSTEM
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
    PRIVATE
        ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(${TSL_PROTOBUF_LIB}
PRIVATE
    ${Protobuf_LIBRARIES}
)


file(GLOB_RECURSE TSL_SOURCES
    ${TSL_SOURCE_DIR}/*.h
    ${TSL_SOURCE_DIR}/*.c
    ${TSL_SOURCE_DIR}/*.cc
)

if (MSVC)
    set(NOT_WINDOWS_PLATFORM_FILTER ".*platform\\/default\\/.*$")
    list(FILTER TSL_SOURCES EXCLUDE REGEX "${NOT_WINDOWS_PLATFORM_FILTER}")
    list(APPEND TSL_SOURCES "${TSL_SOURCE_DIR}/tsl/platform/default/logging.h")
    list(APPEND TSL_SOURCES "${TSL_SOURCE_DIR}/tsl/platform/default/logging.cc")
    list(APPEND TSL_SOURCES "${TSL_SOURCE_DIR}/tsl/platform/default/error_logging.cc")
    list(APPEND TSL_SOURCES "${TSL_SOURCE_DIR}/tsl/platform/default/mutex.h")
    list(APPEND TSL_SOURCES "${TSL_SOURCE_DIR}/tsl/platform/default/mutex.cc")
    list(APPEND TSL_SOURCES "${TSL_SOURCE_DIR}/tsl/platform/default/unbounded_work_queue.h")
    list(APPEND TSL_SOURCES "${TSL_SOURCE_DIR}/tsl/platform/default/unbounded_work_queue.cc")
    list(APPEND TSL_SOURCES "${TSL_SOURCE_DIR}/tsl/platform/default/resource.cc")
else()
    set(WINDOWS_PLATFORM_FILTER ".*platform\\/windows\\/.*$")
    list(FILTER TSL_SOURCES EXCLUDE REGEX "${WINDOWS_PLATFORM_FILTER}")
endif(MSVC)

add_library(${PROJECT_NAME} STATIC ${TSL_SOURCES})

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${TSL_SOURCE_DIR}
    ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    ml_dtypes
    farmhash
    re2
    absl_statusor
    ${TSL_PROTOBUF_LIB}
    ${CMAKE_DL_LIBS}
PRIVATE
    zlibstatic
    $<$<PLATFORM_ID:Windows>:ws2_32>
    absl::log
    jsoncpp_static
    nsync_cpp
    double-conversion
    Eigen3::Eigen
    gtest
    gmock
    benchmark
    ${Protobuf_LIBRARIES}
)


set(PROJECT_INTERFACE "${PROJECT_NAME}-interface")
add_library(${PROJECT_INTERFACE} INTERFACE)
target_include_directories(${PROJECT_INTERFACE} INTERFACE ${TSL_SOURCE_DIR})
target_link_libraries(${PROJECT_INTERFACE}
INTERFACE
    ml_dtypes
    farmhash
    re2
    absl_statusor
    ${TSL_PROTOBUF_LIB}
    ${CMAKE_DL_LIBS}
)
