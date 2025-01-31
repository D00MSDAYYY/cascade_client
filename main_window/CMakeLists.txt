cmake_minimum_required(VERSION 3.5.0)
project(main_window)


add_library(${PROJECT_NAME}  )

target_sources(${PROJECT_NAME} 

PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.ui
PRIVATE
	main_window.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt::Widgets
)



