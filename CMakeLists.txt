# ********************************************************************* #
#          .-.                                                          #
#    __   /   \   __                                                    #
#   (  `'.\   /.'`  )   Everybody Edits 2 - Framework.hpp               #
#    '-._.(;;;)._.-'                                                    #
#    .-'  ,`"`,  '-.                                                    #
#   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        #
#       //\   /         Last Updated: Wed Mar 29 18:44:10 CEST 2023     #
#      ||  '-'                                                          #
# ********************************************************************* #

#==--------------------------------------==#
# *                                      * #
#             PROJECT SETTINGS             #
# *                                      * #
#==--------------------------------------==#

cmake_minimum_required(VERSION 3.25.2)

project(EverybodyEdits2 VERSION 1.0)
message(STATUS "${PROJECT_NAME} (Alpha ${CMAKE_PROJECT_VERSION})")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

add_compile_options(
	-Wall
	-Wextra
	-Wpedantic
	-Wunreachable-code-aggressive
	-Werror
	-g3
)

if(APPLE)
	add_link_options(
		-fsanitize=address
	)
	set(BREW_DIR $ENV{HOME}/.brew)
	set(EXTERN_INCLUDE_DIR
		${BREW_DIR}/include
		${BREW_DIR}/Cellar/nlohmann-json/3.11.2/include )
	set(LIBRARY_DIR
		${BREW_DIR}/opt/glfw/lib/
		${BREW_DIR}/lib/ )
	set(LIBRARY_NAMES glfw sfml-system sfml-window sfml-graphics sfml-audio)
endif()

#==--------------------------------------==#
# *                                      * #
#             SOURCES LISTING              #
# *                                      * #
#==--------------------------------------==#

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CLASS_FILES Logging Framework)
set(CORE_FILES )
set(CXX_FILES main)

macro(append_targets base)
	foreach (arg IN ITEMS ${ARGN})
		list(APPEND CXX_FILES ${base}/${arg})
	endforeach()
endmacro()

macro(append_sources extension)
	foreach(file IN ITEMS ${ARGN})
		set(file_name ${SOURCE_DIR}/${file}.${extension})
		message("\t" ${file} " >> " ${file_name})
		list(APPEND SOURCES ${file_name})
	endforeach()
endmacro()

foreach(include IN ITEMS ${INCLUDE_DIR} ${EXTERN_INCLUDE_DIR})
	list(APPEND INCLUDES ${include})
endforeach()

message("-- Sources:")
append_targets(class ${CLASS_FILES})
append_targets(core ${CORE_FILES})
append_sources(cpp ${CXX_FILES})

#==--------------------------------------==#
# *                                      * #
#           SOFTWARE COMPILATION           #
# *                                      * #
#==--------------------------------------==#

function(print_list title)
	message("-- " ${title} ":")
	foreach(arg IN ITEMS ${ARGN})
		message("\t" ${arg})
	endforeach()
endfunction()

add_executable(${PROJECT_NAME} ${SOURCES})

if(DEFINED INCLUDES)
	print_list("Includes" ${INCLUDES})
	target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
endif()

if(DEFINED LIBRARY_DIR)
	print_list("Library Directories" ${LIBRARY_DIR})
	target_link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})
endif()

if(DEFINED LIBRARY_NAMES)
	print_list("Libraries" ${LIBRARY_NAMES})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARY_NAMES})
endif()
