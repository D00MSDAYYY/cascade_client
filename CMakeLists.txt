cmake_minimum_required(VERSION 3.31.5)
project(cascade_client)

########################### find packages here ##################################
find_package(Qt6 REQUIRED Core Widgets)
#################################################################################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
qt_standard_project_setup()

####################### insert subdirectories here ##############################
add_subdirectory(libraries)
add_subdirectory(application)
#################################################################################

add_executable(${PROJECT_NAME}  )

target_sources(${PROJECT_NAME} 
PRIVATE
	main.cpp # DON'T FORGET TO AVOID "PUBLIC" FIELD HERE (https://gitlab.kitware.com/cmake/cmake/-/issues/20489)

)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt::Widgets
	application
)

