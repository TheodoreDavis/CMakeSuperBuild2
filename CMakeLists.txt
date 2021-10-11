cmake_minimum_required(VERSION 3.5.1)
project(CMaizeSuperbuild2 VERSION 1.0.0 LANGUAGES CXX)

# This is where we will install artifacts during the build stage
set(stage_directory "${CMAKE_BINARY_DIR}/stage${CMAKE_INSTALL_PREFIX}")

# Tell compiler to not include debug flags
set(CMAKE_BUILD_TYPE_INIT "Release")
set(EXTERNAL_DIR "hellogalaxy/external")

include(ExternalProject)
include(GNUInstallDirs)

# Add project with no dependencies from git
ExternalProject_Add(
    CMakeSuperBuild
    GIT_REPOSITORY "https://github.com/CMaizeExamples/CMakeSuperBuild"
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX:PATH=${stage_directory}
        # Switch install path to be inside .../helloworld/cmake/external
        -DCMAKE_INSTALL_INCLUDEDIR=${CMAKE_INSTALL_INCLUDEDIR}/${EXTERNAL_DIR}
        -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}/${EXTERNAL_DIR}
        -DCMAKE_INSTALL_BINDIR=${CMAKE_INSTALL_BINDIR}/${EXTERNAL_DIR}
    BUILD_ALWAYS ON
)

# Builds the main library and installs it to the staging directory
# Allows CMakePublic to build first since it's a dependency
ExternalProject_Add(
    "${PROJECT_NAME}_core"
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/hello_galaxy"
    LIST_SEPARATOR |
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
	    -DCMAKE_INSTALL_PREFIX:PATH=${stage_directory}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_ALT_PATH}
    DEPENDS CMakeSuperBuild
    BUILD_ALWAYS ON
)

# Installing a superbuild just means copying the stage directory to its final location.
INSTALL(DIRECTORY "${stage_directory}/" DESTINATION ${CMAKE_INSTALL_PREFIX})
