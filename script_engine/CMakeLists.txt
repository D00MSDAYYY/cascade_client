cmake_minimum_required(VERSION 3.31.5)
project(script_engine)

####################### insert subdirectories here ##############################

#################################################################################

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} 
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/script_engine.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/script_engine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/script_engine.qrc
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

# target_link_libraries(${PROJECT_NAME}

# )



