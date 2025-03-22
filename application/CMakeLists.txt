cmake_minimum_required(VERSION 3.31.5)
project(application)

####################### insert subdirectories here ##############################
add_subdirectory(main_window)
#################################################################################

add_library(${PROJECT_NAME}  STATIC)

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/application.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Qt::Widgets 
PUBLIC
	main_window
	script_engine
	
)

