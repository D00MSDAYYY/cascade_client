cmake_minimum_required(VERSION 3.25.1)
project(connections_page)

####################### insert subdirectories here ##############################
# add_subdirectory(connections)
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
PUBLIC
	Qt::Widgets
	page
	# connection
)



