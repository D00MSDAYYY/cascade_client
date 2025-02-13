cmake_minimum_required(VERSION 3.31.5)
project(script_area)

####################### insert subdirectories here ##############################
find_package(Lua REQUIRED)
#################################################################################

####################### insert subdirectories here ##############################

#################################################################################

add_library(${PROJECT_NAME} OBJECT)

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/script_area.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/script_area.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} 
PRIVATE
	${LUA_LIBRARIES}
)



