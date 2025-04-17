cmake_minimum_required(VERSION 3.31.5)
project(main_window)

####################### insert subdirectories here ##############################
add_subdirectory(page)
add_subdirectory(alerts_page)
add_subdirectory(sensors_page)
add_subdirectory(connections_page)
add_subdirectory(logbook_page)
add_subdirectory(charts_page)
add_subdirectory(scenarios_page)
add_subdirectory(settings_page)
#################################################################################

add_library(${PROJECT_NAME}  STATIC)

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	alerts_page
	sensors_page
	connections_page
	logbook_page
	charts_page
	scenarios_page
	settings_page
PUBLIC
	Qt::Widgets
	actions_tree
	scripting
	page
)

