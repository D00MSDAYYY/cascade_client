cmake_minimum_required(VERSION 3.31.5)
project(sensors_creator)

####################### insert subdirectories here ##############################
add_subdirectory(sensor_widget)
#################################################################################

add_library(${PROJECT_NAME}  OBJECT)

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/sensors_creator.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sensors_creator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sc_icons.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Qt::Widgets
	sensor_widget
	$<TARGET_OBJECTS:sensor_widget>

)



