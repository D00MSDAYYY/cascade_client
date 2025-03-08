cmake_minimum_required(VERSION 3.31.5)
project(main_window)


####################### insert subdirectories here ##############################
add_subdirectory(alerts_page)
add_subdirectory(sensors_page)
add_subdirectory(connections_page)
add_subdirectory(logbook_page)
add_subdirectory(charts_page)
add_subdirectory(scenarios_page)

#################################################################################

add_library(${PROJECT_NAME}  OBJECT)

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mw_icons.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Qt::Widgets 
	alerts_page
	sensors_page
	connections_page
	logbook_page
	charts_page
	scenarios_page

	$<TARGET_OBJECTS:alerts_page>
	$<TARGET_OBJECTS:sensors_page>
	$<TARGET_OBJECTS:connections_page>
	$<TARGET_OBJECTS:logbook_page>
	$<TARGET_OBJECTS:charts_page>
	$<TARGET_OBJECTS:scenarios_page>
	$<TARGET_OBJECTS:script_engine>
PUBLIC 
	script_engine
)

