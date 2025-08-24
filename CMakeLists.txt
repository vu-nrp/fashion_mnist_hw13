cmake_minimum_required(VERSION 3.16)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

#
project(fashion_mnist VERSION ${PROJECT_VERSION})

# executable
add_executable(${PROJECT_NAME}
    main.cpp
    logres/helpers.h
    logres/helpers.cpp
    logres/classifier.h
    logres/logreg_classifier.h
    logres/logreg_classifier.cpp
)

# set compiller flags
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

#
install(FILES test/test.csv DESTINATION test ${CMAKE_INSTALL_BINDIR})
install(FILES model/logreg_coef.txt DESTINATION model ${CMAKE_INSTALL_BINDIR})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT vu-nrp@yandex.ru)
include(CPack)
