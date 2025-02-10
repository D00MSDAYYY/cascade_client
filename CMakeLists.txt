cmake_minimum_required(VERSION 3.31.5)
project(c_gui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED Core Widgets)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
qt_standard_project_setup()

####################### insert subdirectories here ##############################
add_subdirectory(main_window)
#################################################################################

add_executable(${PROJECT_NAME}  )

target_sources(${PROJECT_NAME} 
PRIVATE
	main.cpp # DON'T FORGET https://gitlab.kitware.com/cmake/cmake/-/issues/20489 
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Qt::Widgets
	main_window

)



