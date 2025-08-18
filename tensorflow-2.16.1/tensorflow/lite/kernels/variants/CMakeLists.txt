cmake_minimum_required(VERSION 3.7)

project(tflite_list_ops CXX)

file(GLOB TFLITE_LIST_OPS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/list_kernels/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/list_kernels/*.h
)

add_library(${PROJECT_NAME} STATIC ${TFLITE_LIST_OPS_SOURCES})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    tensorflow-lite
)

