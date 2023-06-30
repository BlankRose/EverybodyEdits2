/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - EverybodyEdits2.hpp                */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Thursday, June 29, 2023 4:50 PM        */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

// Standard libraries
////////////////////

#include <iostream>

// Base classes
//////////////

#include "base/Configs.hpp"
#include "base/Assets.hpp"
#include "base/Context.hpp"
#include "base/Framework.hpp"
#include "base/Logging.hpp"

// Game's Core Mechanics classes
///////////////////////////////

#include "game/Tile.hpp"
#include "game/World.hpp"
#include "game/GameView.hpp"

// saving.cpp: Handles savestates for the game
/////////////////////////////////////////////

bool save_world(Context *&ctx, const std::string &path);
bool load_world(Context *&ctx, const std::string &path);
bool new_world(Context *&ctx);

// setup.cpp: Prepares and free the game's resources
///////////////////////////////////////////////////

void unload(Context *&ctx);
bool configure(const std::string &path);
bool get_ready(Context *&ctx);
void threads_unit(Context *&ctx);

// drawing.cpp: Handles the drawing of the game
//////////////////////////////////////////////

void event_unit(Context *&ctx);
bool logic_unit(Context *&ctx);
void draws_unit(Context *&ctx);

// testing.cpp: Tests some features of the game
//////////////////////////////////////////////

void test(Context *ctx);
