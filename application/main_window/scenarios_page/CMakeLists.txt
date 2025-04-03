cmake_minimum_required(VERSION 3.31.5)
project(scenarios_page)

####################### insert subdirectories here ##############################

#################################################################################

add_library(${PROJECT_NAME}  STATIC)

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/scenarios_page.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/scenarios_page.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scn_icons.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Qt::Widgets
	script_engine
	script_object
)



