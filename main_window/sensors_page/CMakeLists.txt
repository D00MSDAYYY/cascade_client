cmake_minimum_required(VERSION 3.31.5)
project(sensors_page)

####################### insert subdirectories here ##############################
add_subdirectory(sensors_creator)
#################################################################################

add_library(${PROJECT_NAME}  )

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/sensors_page.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sensors_page.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sp_icons.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Qt::Widgets
	sensors_creator
)



