cmake_minimum_required(VERSION 3.25.1)
project(main_window)

####################### insert subdirectories here ##############################
add_subdirectory(pages)
add_subdirectory(ui_toolkit)
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

