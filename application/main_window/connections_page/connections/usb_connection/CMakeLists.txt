cmake_minimum_required(VERSION 3.31.5)
project(usb_connection)

####################### insert subdirectories here ##############################
#################################################################################

add_library(${PROJECT_NAME}  STATIC)

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/usb_connection.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/usb_connection.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	connection
)



