cmake_minimum_required(VERSION 3.7)

# Double colon in target name means ALIAS or IMPORTED target.
cmake_policy(SET CMP0028 NEW)

project(tensorflow-delegate-flex C CXX)

find_package(Protobuf REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(TENSORFLOW_SOURCE_DIR "" CACHE PATH
  "Directory that contains the TensorFlow project"
)

if(NOT TENSORFLOW_SOURCE_DIR)
  abort()
endif()

file(GLOB DELEGATE_SRCS
    ${TF_SOURCE_DIR}/lite/delegates/flex/*.h
    ${TF_SOURCE_DIR}/lite/delegates/flex/*.cc
    ${TF_SOURCE_DIR}/lite/delegates/utils/*.cc
    ${TF_SOURCE_DIR}/lite/tools/tool_params.h
    ${TF_SOURCE_DIR}/lite/tools/tool_params.cc

)

add_library(${PROJECT_NAME} STATIC ${DELEGATE_SRCS})

if (MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE "TFL_EXTERNAL_DELEGATE_COMPILE_LIBRARY")
endif(MSVC)

target_include_directories(${PROJECT_NAME} PRIVATE ${TENSORFLOW_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}
PUBLIC
    gtest
    gmock
    tsl-lib-protobuf
    tensorflow-lib-protobuf
    ${Protobuf_LIBRARIES}
    tensorflow-lite
    tsl-lib-interface
    tensorflow-core-mix-interface
)
