cmake_minimum_required(VERSION 3.31.5)
project(sensor_widget)

####################### insert subdirectories here ##############################

#################################################################################

add_library(${PROJECT_NAME}  )

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/sensor_widget.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sensor_widget.cpp
	# sw_icons.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Qt::Widgets
)



