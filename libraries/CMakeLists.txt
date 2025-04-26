cmake_minimum_required(VERSION 3.25.1)
project(libraries)

include(FetchContent)

set(DEP_NAME "common_libraries")
set(REMOTE_REPO "https://github.com/D00MSDAYYY/common_libraries.git")
set(TAG "main")
set(DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${DEP_NAME}")

FetchContent_Declare(
    ${DEP_NAME}
    GIT_REPOSITORY ${REMOTE_REPO}
    GIT_TAG ${TAG}
    GIT_SUBMODULES_RECURSE YES
    GIT_SHALLOW TRUE
    SOURCE_DIR "${DEP_DIR}" 
)

FetchContent_MakeAvailable(${DEP_NAME})


set(DEP_NAME "lua")
set(REMOTE_REPO "https://github.com/lubgr/lua-cmake.git")
set(TAG "master")
set(DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${DEP_NAME}")

FetchContent_Declare(
    ${DEP_NAME}
    GIT_REPOSITORY ${REMOTE_REPO}
    GIT_TAG ${TAG}
    GIT_SUBMODULES_RECURSE YES
    GIT_SHALLOW TRUE
    SOURCE_DIR "${DEP_DIR}" 
)

FetchContent_MakeAvailable(${DEP_NAME})