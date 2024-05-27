#* ************************************************************************** *#
##         .-.
##   __   /   \   __
##  (  `'.\   /.'`  )  EverybodyEdits2 - CMakeLists.txt
##   '-._.(;;;)._.-'
##   .-'  ,`"`,  '-.
##  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
##      //\   /        Created at: May 27, 2024 [6:38 AM]
##     ||  '-'
#* ************************************************************************** *#

cmake_minimum_required(VERSION 3.20)

#   PROJECT DEFINITION
# ############################

project(EverybodyEdits2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#   DEPENDENCIES
# ############################

include(FetchContent)
FetchContent_Declare(roselib # latest
        # Personal library
        GIT_REPOSITORY  https://github.com/BlankRose/roselib.git
        GIT_TAG         master)
FetchContent_Declare(nlohmann_json # v3.11.3
        # Handles JSON operations
        GIT_REPOSITORY  https://github.com/nlohmann/json.git
        GIT_TAG         9cca280a4d0ccf0c08f47a99aa71d1b0e52f8d03)
FetchContent_Declare(sfml # 2.6.1
        # Handles graphics and events
        GIT_REPOSITORY  https://github.com/SFML/SFML.git
        GIT_TAG         69ea0cd863aed1d4092b970b676924a716ff718b)
FetchContent_MakeAvailable(roselib nlohmann_json sfml)

#   PROJECT SOURCES
# ############################

set(SOURCES
        src/base/Assets.cpp
        src/base/Configs.cpp
        src/base/Context.cpp
        src/base/Framework.cpp
        src/base/Logging.cpp

        src/core/drawing.cpp
        src/core/logic.cpp
        src/core/events.cpp
        src/core/predicates.cpp
        src/core/sections.cpp
        src/core/setup.cpp
        src/core/testing.cpp

        src/game/Camera.cpp
        src/game/GameController.cpp
        src/game/Player.cpp
        src/game/Tile.cpp
        src/game/TileSelector.cpp
        src/game/World.cpp

        src/menu/WorldSelector.cpp

        src/main.cpp
)

#   COMPILATION
# ############################

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE roselib nlohmann_json sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PRIVATE include)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wunreachable-code -Werror -g3)
    if (NOT WIN32)
        target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
    endif ()
else () # MATCHES "Release"
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
endif ()