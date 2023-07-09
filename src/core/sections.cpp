/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - sections.cpp                       */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Sunday, July 9, 2023 3:15 PM           */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "EverybodyEdits2.hpp"

/**
 * Loads the game world from loaded configurations
 * 
 * @return	True or False depending on the success of the operation
 * */
bool prepareGame(Context *ctx)
{
	__TIME_INIT
	__TIME_TEST("Loading the world",
		if (!ctx->game->loadWorld(Configs::misc::save_file)
			|| !ctx->game->newWorld(Configs::misc::test_width, Configs::misc::test_height))
			return (Logging::error("Failed to prepare the game!"), false);
	)

	__DEBUG(
		World *world = ctx->game->getWorld();
		std::cout << "World size: " << world->get_width() << "x" << world->get_height() << std::endl;
		std::cout << "Tile at 0:0 is " << world->get_fg_tile(0, 0).get_id() << " | " << world->get_bg_tile(0, 0).get_id() << std::endl;
		std::cout << "Tile at 1:1 is " << world->get_fg_tile(1, 1).get_id() << " | " << world->get_bg_tile(1, 1).get_id() << std::endl;
	)

	__TIME_TEST("Initializing the camera",
		if (!ctx->game->newCamera(ctx->fw->get_window().getView()))
			return (Logging::error("Failed to prepare the gamea!"), false);
	)

	return true;
}

/**
 * Unloads the game world from loaded configurations
 * 
 * @return	True or False depending on the success of the operation
 * */
bool unloadGame(Context *ctx)
{
	__TIME_INIT
	__TIME_TEST("Saving the world",
		if (!ctx->game->saveWorld(Configs::misc::save_file)
			|| !ctx->game->destroyWorld())
			return (Logging::error("Failed to unload the game!"), false);
	)

	return true;
}
