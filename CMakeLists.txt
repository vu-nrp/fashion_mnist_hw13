cmake_minimum_required(VERSION 3.16)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(fashio_mnist VERSION ${PROJECT_VERSION})

if (TENSORFLOW_SUPPORT)
    add_compile_definitions(TENSORFLOW_DEFINED)
endif()

if (${TENSORFLOW_SUPPORT})
    # include(OldCMakeWholeArchive)
    target_link_libraries(${PROJECT_NAME} PRIVATE tensorflow-lite)
    # target_link_libraries(${PROJECT_NAME} PRIVATE tensorflow-delegate-flex)
    # link_as_whole_archive(${PROJECT_NAME} PRIVATE tsl-lib)
    # link_as_whole_archive(${PROJECT_NAME} PRIVATE tensorflow-core-mix)
endif()


#
add_subdirectory(tensorflow-2.16.1)

# app executable
add_executable(${PROJECT_NAME}
    main.cpp
)

# set compiller flags
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

#
#target_include_directories(${PROJECT_NAME}
#PUBLIC
#    ${CMAKE_SOURCE_DIR}/lib
#    ${CMAKE_BINARY_DIR}
#)

#
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT vu-nrp@yandex.ru)
include(CPack)
