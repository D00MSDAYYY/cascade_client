cmake_minimum_required(VERSION 3.26)
project(sensors_page)

####################### insert subdirectories here ##############################

#################################################################################

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/sensors_page.hpp
PRIVATE
	sensors_page.cpp
	sp_icons.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt::Widgets
)



