cmake_minimum_required(VERSION 3.31.5)
project(common_libraries)

include(FetchContent)

FetchContent_Declare(
    ${PROJECT_NAME} 
    GIT_REPOSITORY https://github.com/D00MSDAYYY/common_libraries.git
    GIT_TAG main  
)

FetchContent_MakeAvailable(${PROJECT_NAME} )

set(THIS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(COPY ${${PROJECT_NAME}_SOURCE_DIR} DESTINATION ${THIS_DIR})

