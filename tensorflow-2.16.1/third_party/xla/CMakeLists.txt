cmake_minimum_required(VERSION 3.7)

set(XLA_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "XLA lib sources" FORCE)

add_subdirectory("third_party/tsl" "TSL sources")
add_subdirectory("xla" "XLA sources")
