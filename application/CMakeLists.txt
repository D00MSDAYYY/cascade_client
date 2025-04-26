cmake_minimum_required(VERSION 3.25.1)
project(application)

####################### insert subdirectories here ##############################
add_subdirectory(time)
add_subdirectory(main_window)
add_subdirectory(debug_console)
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
	Qt::Widgets 
PUBLIC
	debug_console
	main_window
	scripting
	clock
)

