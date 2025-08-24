cmake_minimum_required(VERSION 3.7)

# requeired by main code, use FlatBuffers for model seriallization
set(FLATBUFFERS_INSTALL OFF CACHE BOOL "disable FlatBuffers install" FORCE)
set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "disable FlatBuffers tests" FORCE)
set(FLATBUFFERS_BUILD_BENCHMARKS OFF CACHE BOOL "disable FlatBuffers benchmark" FORCE)
set(FLATBUFFERS_BUILD_GRPCTEST OFF CACHE BOOL "disable FlatBuffers gRPC tests" FORCE)
set(FLATBUFFERS_BUILD_FLATC OFF CACHE BOOL "disable FlatBuffers execatable" FORCE)

set(FLATBUFFERS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/flatbuffers/flatbuffers-23.5.26" CACHE PATH "FlatBuffers src dir")
add_subdirectory("${FLATBUFFERS_SOURCE_DIR}")
target_compile_options(FlatBuffers INTERFACE "-w")
add_library(flatbuffers::flatbuffers ALIAS FlatBuffers)

set(CPUINFO_BUILD_MOCK_TESTS OFF CACHE BOOL "disable CPUINFO_BUILD_MOCK_TESTS" FORCE)
set(CPUINFO_BUILD_UNIT_TESTS OFF CACHE BOOL "disable CPUINFO_BUILD_UNIT_TESTS" FORCE)
set(CPUINFO_BUILD_BENCHMARKS OFF CACHE BOOL "disable CPUINFO_BUILD_BENCHMARKS" FORCE)
set(CPUINFO_BUILD_TOOLS OFF CACHE BOOL "disable cpuinfo tools" FORCE)
set(CPUINFO_BUILD_PKG_CONFIG OFF CACHE BOOL "disable cpuinfo PkgConfig" FORCE)
set(CPUINFO_RUNTIME_TYPE "static" CACHE STRING "static MSVC runtime" FORCE)
set(CPUINFO_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpuinfo" CACHE PATH "cpu info src dir")
add_subdirectory("${CPUINFO_SOURCE_DIR}")

set(PSIMD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/psimd" CACHE PATH "psimd src dir")
add_subdirectory("${PSIMD_SOURCE_DIR}")

set(ABSL_BUILD_TESTING OFF CACHE BOOL "disable ABSEIL tests" FORCE)
set(ABSL_ENABLE_INSTALL OFF CACHE BOOL "disable ABSEIL install" FORCE)
set(ABSL_PROPAGATE_CXX_STD ON CACHE BOOL "enable some strange feature, maybe should not" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/abseil-cpp")
add_library(absl ALIAS absl_base)

set(BUILD_TESTING OFF CACHE BOOL "disable GEMMLOWP tests" FORCE)
set(GEMMLOWP_SOURCE_DIR "${gemmlowp_SOURCE_DIR}" CACHE PATH "Source directory")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gemmlowp/contrib")
add_library(gemmlowp::gemmlowp ALIAS gemmlowp)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/neon2sse/ARM_NEON_2_x86_SSE")
add_library(neon2sse ALIAS NEON_2_SSE)
add_library(NEON_2_SSE::NEON_2_SSE ALIAS NEON_2_SSE)

set(FXDIV_BUILD_TESTS OFF CACHE BOOL "disable fxdiv tests" FORCE)
set(FXDIV_BUILD_BENCHMARKS OFF CACHE BOOL "disable fxdiv benchmark" FORCE)
set(FXDIV_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/fxdiv" CACHE PATH "fxdiv src dir")
add_subdirectory("${FXDIV_SOURCE_DIR}")

set(PTHREADPOOL_BUILD_TESTS OFF CACHE BOOL "disable pthreadpool tests" FORCE)
set(PTHREADPOOL_BUILD_BENCHMARKS OFF CACHE BOOL "disable pthreadpool benchmark" FORCE)
set(PTHREADPOOL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/pthreadpool" CACHE PATH "pthreadpool src dir")
add_subdirectory("${PTHREADPOOL_SOURCE_DIR}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/fft2d/OouraFFT-1.0")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ml_dtypes")

### even if TFLITE_ENABLE_RUY if OFF, some code still use RUY sources, so it's must have
set(RUY_MINIMAL_BUILD TRUE CACHE BOOL "minimal RUY build" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ruy")

set(EIGEN_BUILD_BTL OFF CACHE BOOL "disble EIGEN benchmark" FORCE)
set(EIGEN_BUILD_SPBENCH OFF CACHE BOOL "disble EIGEN sparse benchmark" FORCE)
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "disble EIGEN pkg config" FORCE)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "disale Eigen docs generation" FORCE)
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "disale Eigen tests" FORCE)
set(EIGEN_TEST_SYCL OFF CACHE BOOL "disable test with c++17 requirements" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/eigen3")


set(FARMHASH_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/farmhash" CACHE PATH "farmhash srd dir" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/farmhash")
target_compile_options(eigen INTERFACE "-w")


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/re2")
# add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/highwayhash")


set(JSONCPP_WITH_TESTS OFF CACHE BOOL "disable JSONCPP tests" FORCE)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "disable JSONCPP unittest" FORCE)
set(JSONCPP_WITH_PKGCONFIG_SUPPORT OFF CACHE BOOL "disable JSONCPP pkgconfig" FORCE)
set(JSONCPP_WITH_CMAKE_PACKAGE OFF CACHE BOOL "disable JSONCPP cmake package" FORCE)
set(JSONCPP_WITH_EXAMPLE OFF CACHE BOOL "disable JSONCPP example" FORCE)
set(JSONCPP_STATIC_WINDOWS_RUNTIME ON CACHE BOOL "use static Windows runtime" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp")


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/double-conversion")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/nsync")

### only for TF-Core and XLA libs
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest")
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/google_benchmark")
#set(ZLIB_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zlib")
#add_subdirectory("${ZLIB_SOURCES_DIR}")
#include_directories("${CMAKE_CURRENT_BINARY_DIR}/zlib")
#set(ZLIB_INCLUDE_DIR "${ZLIB_SOURCES_DIR}" CACHE PATH "zlib include" FORCE)
#set(ZLIB_LIBRARY "${CMAKE_CURRENT_BINARY_DIR}/bin" CACHE PATH "zlib bin" FORCE)

if(TFLITE_ENABLE_XNNPACK)
    set(FP16_BUILD_TESTS OFF CACHE BOOL "disable fp16 tests" FORCE)
    set(FP16_BUILD_BENCHMARKS OFF CACHE BOOL "disable fp16 benchmarks" FORCE)
    set(FP16_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/fp16" CACHE PATH "fp16 path" FORCE)
    add_subdirectory("${FP16_SOURCE_DIR}")
    include_directories("${FP16_SOURCE_DIR}/include")

    set(XNNPACK_BUILD_TESTS OFF CACHE BOOL "disable xnnpack tests" FORCE)
    set(XNNPACK_BUILD_BENCHMARKS OFF CACHE BOOL "disable xnnpack benchmarks" FORCE)

    message(STATUS "compiler: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

    # Для Clang 11.0.1 флаг -maxvvnni не компилируется, на версии 16.0.6 с этим флагом уже всё окей.
    # промежуточные версии Clang не тестировал
    # Для GCC с документацией чуть лучше, если ей верить, то флаг -maxvvnni появляется в версии 11, а в версии 10 и младше его нет
    # https://gcc.gnu.org/onlinedocs/gcc-9.5.0/gcc/x86-Options.html    <-- нет
    # https://gcc.gnu.org/onlinedocs/gcc-10.5.0/gcc/x86-Options.html   <-- нет
    # https://gcc.gnu.org/onlinedocs/gcc-11.5.0/gcc/x86-Options.html   <-- есть
    if (((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "16.0"))
            OR ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") AND UNIX AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11.0")))
        message(STATUS "AVXVNNI optimization in XNNPACK: OFF")
        set(XNNPACK_ENABLE_AVXVNNI OFF CACHE BOOL "AVXVNNI optimization" FORCE)
    else()
        message(STATUS "AVXVNNI optimization in XNNPACK: ON")
        set(XNNPACK_ENABLE_AVXVNNI ON CACHE BOOL "AVXVNNI optimization" FORCE)
    endif()

    # внутри XNNPACK есть часть исходников, которые компилируются в объект microkernels-all
    # он нужен только для тестов, но его нельзя отключить флагами,
    # поэтому он закомментирован руками в файле `CUSTOM_SRCS/xnnpack/CMakeLists.txt`
    # ADD_LIBRARY(microkernels-all
    # и далее

    set(xnnpack_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/xnnpack" CACHE PATH "xnnpack path" FORCE)
    add_subdirectory("${xnnpack_SOURCE_DIR}")
endif()

