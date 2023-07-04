/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - EverybodyEdits2.hpp                */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, July 4, 2023 8:53 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

// INCLUDES
////////////////////

#include <iostream>

#include "base/Configs.hpp"
#include "base/Assets.hpp"
#include "base/Context.hpp"
#include "base/Framework.hpp"
#include "base/Logging.hpp"

#include "game/Tile.hpp"
#include "game/World.hpp"
#include "game/Camera.hpp"
#include "game/GameController.hpp"

// FUNCTIONS
////////////////////

// setup.cpp: Prepares and free the game's resources
void unload(Context *&ctx);
bool configure(const std::string &path);
bool get_ready(Context *&ctx);
void threads_unit(Context *&ctx);

// drawing.cpp: Handles the drawing of the game
void event_unit(Context *&ctx);
bool logic_unit(Context *&ctx);
void draws_unit(Context *&ctx);

// testing.cpp: Tests some features of the game
void test(Context *ctx);
