cmake_minimum_required(VERSION 3.5.0)
project(main_window)

add_library(${PROJECT_NAME}  )

qt_add_resources(RCC 
	icons.qrc
)

target_sources(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.ui
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/square_list_widget.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/square_push_button.hpp

	main_window.cpp
	${RCC}
	
)


target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Qt::Widgets
)



