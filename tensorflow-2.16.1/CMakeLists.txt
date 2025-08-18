cmake_minimum_required(VERSION 3.0)

project(tensorflowcustom)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(TENSORFLOW_SOURCE_DIR "" CACHE PATH
  "Directory that contains the TensorFlow project"
)

if(NOT TENSORFLOW_SOURCE_DIR)
  get_filename_component(TENSORFLOW_SOURCE_DIR
    "${CMAKE_CURRENT_LIST_DIR}"
    ABSOLUTE
  )
endif()

unset(TENSORFLOW_SUPPORT CACHE)

if ((DEFINED DISABLE_TENSORFLOW_SUPPORT) AND (${DISABLE_TENSORFLOW_SUPPORT}))
    message(STATUS "'DISABLE_TENSORFLOW_SUPPORT' cmake variable is defined by user or top-level cmake")
    message(STATUS "DISABLE_TENSORFLOW_SUPPORT = ${DISABLE_TENSORFLOW_SUPPORT}, Tensorflow support OFF")
    set(TRY_TO_BUILD FALSE)
else()
    # или DISABLE_TENSORFLOW_SUPPORT не задана,
    # или DISABLE_TENSORFLOW_SUPPORT == FALSE
    # будем пытаться собирать
    set(TRY_TO_BUILD TRUE)
endif()

if (TRY_TO_BUILD)
    # но перед подключение TF всё равно нужно проверить, что у нас достаточная версия компилятора и CMake

    if(MSVC)
        # минимальная версия MSVC Toolset для сборки -- v142
        if(MSVC_VERSION VERSION_GREATER_EQUAL 1920)
            set(TENSORFLOW_SUPPORT TRUE CACHE BOOL "Tensorflow support" FORCE)
        else()
            set(TENSORFLOW_SUPPORT FALSE CACHE BOOL "Tensorflow support" FORCE)
            message(STATUS "MSVC_VERSION ${MSVC_VERSION} is too old (needs >= 1920), Tensorflow support OFF")
        endif()
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # точная версия начиная с которой соберётся мне неизвестна
        # на Астре 1.6 с GCC 6.3.0 проект не собирается, т.к. там точно нет поддержки с++17
        # на Астре 1.7 с GCC 8.3.0 всё компилируется без проблем
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "8.3.0")
            set(TENSORFLOW_SUPPORT TRUE CACHE BOOL "Tensorflow support" FORCE)
        else()
            set(TENSORFLOW_SUPPORT FALSE CACHE BOOL "Tensorflow support" FORCE)
            message(STATUS "GCC ${CMAKE_CXX_COMPILER_VERSION} is too old (needs >= 8.3.0), Tensorflow support OFF")
        endif()
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # точная версия начиная с которой соберётся мне неизвестна
        # Астре 1.6 Tensorflow можно собрать, если поставить Clang 9.0.1 из апдейта,
        #   при этом нужно линковаться с реализацией "libc++" стандартной библиотеки, а не "libstdc++"
        # На Астре 1.7 по умолчанию идёт clang 11.0.2 и он всё собирает "из коробки"
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "9.0.1")
            set(TENSORFLOW_SUPPORT TRUE CACHE BOOL "Tensorflow support" FORCE)
        else()
            set(TENSORFLOW_SUPPORT FALSE CACHE BOOL "Tensorflow support" FORCE)
            message(STATUS "Clang ${CMAKE_CXX_COMPILER_VERSION} is too old (needs >= 9.0.1), Tensorflow support OFF")
        endif()
    endif()


    # вроде бы версии 3.14 должно хватать. На 3.16.3 точно компилируется.
    if(${CMAKE_VERSION} VERSION_LESS 3.14.0)
        set(TENSORFLOW_SUPPORT FALSE CACHE BOOL "Tensorflow support" FORCE)
        message(STATUS "CMake ${CMAKE_VERSION} is too old (needs >= 3.14.0), Tensorflow support OFF")
    endif()


    if(${TENSORFLOW_SUPPORT})
        message(STATUS "build project with Tensorflow support, Tensorflow support ON")
        add_compile_definitions(TENSORFLOW_DEFINED)

        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)

        if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS_EQUAL "9.0.1"))
            message(STATUS "XNNPACK optimization: disabled, Clang ${CMAKE_CXX_COMPILER_VERSION} is TOO old")
            set(TFLITE_ENABLE_XNNPACK OFF CACHE BOOL "XNNPACK support" FORCE)
        else()
            # работает на всех сборках, где есть Tensorflow, кроме Astra1.6_update10 -> Clang 9.0.1
            set(TFLITE_ENABLE_XNNPACK ON CACHE BOOL "XNNPACK support" FORCE)
            message(STATUS "XNNPACK optimization: enabled")
        endif()

        # external sources from internet
        add_subdirectory("${TENSORFLOW_SOURCE_DIR}/CUSTOM_SRCS")

        if(MSVC)
            add_definitions(
                "-D_CRT_SECURE_NO_WARNINGS"
                "-D_USE_MATH_DEFINES"
    #            "-D_ITERATOR_DEBUG_LEVEL=0"
                "-DNOMINMAX"
                "-DNOGDI"       # fix ERROR logging level
            )

            add_compile_options(
                /bigobj
                /Zm1000
                /EHsc
                /wd4351
                /wd4291
                /wd4250
                /wd4996
            )

        endif(MSVC)

        add_compile_definitions(${PROJECT_NAME} PUBLIC IS_SLIM_BUILD)
        add_compile_definitions(${PROJECT_NAME} PUBLIC NO_LLVM_SUPPORT)

        set(TF_SOURCE_DIR "${TENSORFLOW_SOURCE_DIR}/tensorflow" CACHE PATH "tensorflow sources dir (without 3d party)" FORCE)
        # set(XLA_DIR "${TENSORFLOW_SOURCE_DIR}/third_party/xla" CACHE PATH "XLA 3d lib sources" FORCE)
        # add_subdirectory("${XLA_DIR}")
        set(TSL_DIR "${TENSORFLOW_SOURCE_DIR}/third_party/xla/third_party/tsl" CACHE PATH "TSL 3d lib sources" FORCE)
        set(TSL_SOURCE_DIR "${TSL_DIR}" CACHE PATH "TSL lib sources" FORCE)
        # add_subdirectory("${TSL_DIR}")

        ### top level Tensorflow-only (not 3dparty) path
        # add_subdirectory("${TF_SOURCE_DIR}/core")
        add_subdirectory("${TF_SOURCE_DIR}/lite")
        # add_subdirectory("${TF_SOURCE_DIR}/lite/delegates/flex")

        # need only one time for very strange
        #    *.pb_text.h
        #    *.pb_text.cc
        #    *.pb_text-impl.h
        # add_subdirectory("${TENSORFLOW_SOURCE_DIR}/tensorflow/tools/proto_text/")

    endif()
endif()
