cmake_minimum_required(VERSION 3.26)
project(main_window)

####################### insert subdirectories here ##############################
add_subdirectory(sensors_page)
#################################################################################

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.hpp
PRIVATE
	main_window.cpp
	mw_icons.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt::Widgets
	sensors_page
)



