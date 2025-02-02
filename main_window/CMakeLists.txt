cmake_minimum_required(VERSION 3.5.0)
project(main_window)

add_library(${PROJECT_NAME}  )

target_sources(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.hpp
PRIVATE
	main_window.cpp
	icons.qrc
)


target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Qt::Widgets
)



