cmake_minimum_required(VERSION 3.31.5)
project(debug_console)

####################### insert subdirectories here ##############################

#################################################################################

add_library(${PROJECT_NAME}  STATIC)

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/debug_console.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/debug_console.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	script_object
	script_engine
	Qt::Widgets
)

