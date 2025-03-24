cmake_minimum_required(VERSION 3.31.5)
project(libraries)

include(FetchContent)

set(DEP_NAME ${PROJECT_NAME})
set(REMOTE_REPO "https://github.com/D00MSDAYYY/common_libraries.git")
set(TAG "main")  
set(DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${DEP_NAME}")

if(EXISTS "${DEP_DIR}/.git")
    execute_process(
        COMMAND ${GIT_EXECUTABLE} fetch --dry-run
        WORKING_DIRECTORY ${DEP_DIR}
        OUTPUT_VARIABLE GIT_CHANGES
        RESULT_VARIABLE GIT_RESULT
        OUTPUT_QUIET  
    )

    if(GIT_RESULT EQUAL 0 AND NOT GIT_CHANGES STREQUAL "")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} pull origin ${TAG}
            WORKING_DIRECTORY ${DEP_DIR}
            COMMAND_ERROR_IS_FATAL ANY
        )
        message(STATUS "Dependency '${DEP_NAME}' updated ")
    else()
        message(STATUS "Dependency '${DEP_NAME}' is up to date")
    endif()
else()
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone --branch ${TAG} ${REMOTE_REPO} ${DEP_NAME}
        WORKING_DIRECTORY ${DEP_DIR}
        COMMAND_ERROR_IS_FATAL ANY
    )
endif()


FetchContent_Declare(
    ${DEP_NAME}
    SOURCE_DIR ${DEP_DIR}
    GIT_REPOSITORY ${REMOTE_REPO}  
    GIT_TAG ${TAG}
	GIT_SUBMODULES_RECURSE YES
    GIT_SHALLOW TRUE  
)

FetchContent_MakeAvailable(${DEP_NAME})

