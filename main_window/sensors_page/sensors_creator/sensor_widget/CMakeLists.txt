cmake_minimum_required(VERSION 3.26)
project(sensor_widget)

####################### insert subdirectories here ##############################

#################################################################################

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/sensor_widget.hpp
PRIVATE
	sensor_widget.cpp
	# sw_icons.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt::Widgets
)



