# ********************************************************************* #
#          .-.                                                          #
#    __   /   \   __                                                    #
#   (  `'.\   /.'`  )   Everybody Edits 2 - CMakeLists.txt              #
#    '-._.(;;;)._.-'                                                    #
#    .-'  ,`"`,  '-.                                                    #
#   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        #
#       //\   /         Last Updated: Tue Mar 28 19:56:39 CEST 2023     #
#      ||  '-'                                                          #
# ********************************************************************* #

#==--------------------------------------==#
# *                                      * #
#             PROJECT SETTINGS             #
# *                                      * #
#==--------------------------------------==#

cmake_minimum_required(VERSION 3.25.2)
project(EverybodyEdits2 VERSION 1.0)
message(STATUS "${PROJECT_NAME} (V-${CMAKE_PROJECT_VERSION})")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

if(UNIX)
	add_compile_options(
		-Wall
		-Wextra
		-Wpedantic
		-Wunreachable-code-aggressive
		-Werror
		-g3
	)
endif()

#==--------------------------------------==#
# *                                      * #
#           SOFTWARE COMPILATION           #
# *                                      * #
#==--------------------------------------==#

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CXX_FILES main)
foreach(FILE IN ITEMS ${CXX_FILES})
	list(APPEND SOURCES ${SOURCE_DIR}/${FILE}.cpp)
endforeach()

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
#target_link_directories(${PROJECT_NAME} PUBLIC ...)
#target_link_libraries(${PROJECT_NAME} PUBLIC ...)