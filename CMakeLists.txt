cmake_minimum_required(VERSION 3.22)
project(test_apple_dragndrop)

#C++ init
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
#

#Qt6 init
function(init_qt6)
	find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core Sql)
    set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTORCC ON)
	set(CMAKE_AUTOUIC ON)
endfunction()

#option(_QT_6_PATH "Set _QT_6_PATH like: ${WRONG_PATH_MESSAGE}" OFF)
set(CMAKE_PREFIX_PATH "S:\\Code\\Qt\\6.2.2\\msvc2019_64")
init_qt6()
#

#general source-targets processing
file(GLOB IN_PROJECT_CPP_FILES
     ${SOURCE_DIR}*.cpp *.h)
message(" ### IN_PROJECT_CPP_FILES = ${IN_PROJECT_CPP_FILES}")
add_executable(${PROJECT_NAME} ${IN_PROJECT_CPP_FILES})
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Gui Qt6::Core Qt6::Sql)

#post build actions
set(FULL_PATH_TO_EXECUTABLE $<TARGET_FILE:${PROJECT_NAME}>)
set(FULL_PATH_TO_EXECUTABLE_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>)
set(IMAGES_DIR ${${PROJECT_NAME}_SOURCE_DIR}/images)

#1
message(" ### Add post build event : windeployqt.exe")
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E echo "POST_BUILD: Using windeployqt to copy all depends to executable path"
	COMMAND ${CMAKE_PREFIX_PATH}/bin/windeployqt.exe 
			${FULL_PATH_TO_EXECUTABLE}
			--no-quick-import 
				--no-translations 
)

#2
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E echo "POST_BUILD:copy_directory ${IMAGES_DIR} to ${FULL_PATH_TO_EXECUTABLE_DIR}/images"
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${IMAGES_DIR} ${FULL_PATH_TO_EXECUTABLE_DIR}/images
)

#3
#set(POST_BUILD_EXECUTION ON)
if(POST_BUILD_EXECUTION)
	message(" ### Add post build event : ./${PROJECT_NAME}.exe")
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E echo "POST_BUILD:Launch an app after build."
		COMMAND ${FULL_PATH_TO_EXECUTABLE} 
		
	)
endif()#POST_BUILD_EXECUTION

#



