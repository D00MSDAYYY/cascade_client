cmake_minimum_required(VERSION 3.25.1)
project(connection)

########################### find packages here ##################################
find_package(Qt6 REQUIRED Core SerialPort Network)
#################################################################################

add_library(${PROJECT_NAME}  STATIC)

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC 
	Qt::Core
    Qt::SerialPort
    Qt::Network
	scripting
)



