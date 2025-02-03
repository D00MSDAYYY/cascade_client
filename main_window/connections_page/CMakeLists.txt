cmake_minimum_required(VERSION 3.26)
project(connections_page)

####################### insert subdirectories here ##############################

#################################################################################

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/connections_page.hpp
PRIVATE
	connections_page.cpp
	cn_icons.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt::Widgets
)



