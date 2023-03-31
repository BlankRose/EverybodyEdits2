# ********************************************************************* #
#          .-.                                                          #
#    __   /   \   __                                                    #
#   (  `'.\   /.'`  )   Everybody Edits 2 - setup.cpp                   #
#    '-._.(;;;)._.-'                                                    #
#    .-'  ,`"`,  '-.                                                    #
#   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        #
#       //\   /         Last Updated: Fri Mar 31 20:43:43 CEST 2023     #
#      ||  '-'                                                          #
# ********************************************************************* #

#==--------------------------------------==#
# *                                      * #
#             PROJECT SETTINGS             #
# *                                      * #
#==--------------------------------------==#

cmake_minimum_required(VERSION 3.24.0)

project(EverybodyEdits2 VERSION 1.0)
message(STATUS "${PROJECT_NAME} (Alpha ${CMAKE_PROJECT_VERSION})")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

add_compile_options(
	-Wall
	-Wextra
	-Wpedantic
	-Wunreachable-code
	-Werror
	-g3
)

add_definitions(-D LOG_DEBUG)

if(APPLE)
	add_link_options(-fsanitize=address)
	add_compile_options(-Wunreachable-code-aggressive)
	set(BREW_DIR $ENV{HOME}/.brew)
	set(EXTERN_INCLUDE_DIR
		${BREW_DIR}/include
		${BREW_DIR}/Cellar/nlohmann-json/3.11.2/include )
	set(LIBRARY_DIR
		${BREW_DIR}/opt/glfw/lib/
		${BREW_DIR}/lib/ )
	set(LIBRARY_NAMES glfw sfml-system sfml-window sfml-graphics sfml-audio)
endif()

if(WIN32)
	set(LIBRARY_PATH C:/Librairies)
	set(EXTERN_INCLUDE_DIR
		${LIBRARY_PATH}/SFML-2.5.1/include
		${LIBRARY_PATH}/JSON-3.11.2
	)
	set(LIBRARY_DIR ${LIBRARY_PATH}/SFML-2.5.1/lib)
	set(LIBRARY_NAMES glfw3 opengl32 gdi32 sfml-system sfml-window sfml-graphics sfml-audio)
endif()

#==--------------------------------------==#
# *                                      * #
#             SOURCES LISTING              #
# *                                      * #
#==--------------------------------------==#

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CLASS_FILES Logging Framework Assets TileMap MapChunk)
set(CORE_FILES setup drawing events logic main)

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
