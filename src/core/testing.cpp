/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - testing.cpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, June 28, 2023 7:47 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "EverybodyEdits2.hpp"
#include <chrono>

/**
 * Testing unit to test some components of the software
 * 
 * @param	ctx: Context of the software
 * */
void	test(Context *ctx)
{
	std::chrono::steady_clock clock;
	std::chrono::steady_clock::time_point start, end;

	// Test loading time
	start = clock.now();
	if (!load_world(ctx, Configs::misc::save_file))
		new_world(ctx);
	end = clock.now();
	Logging::info("Loading the world took " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) + "ms");

	std::cout << "World size: " << ctx->map->get_width() << "x" << ctx->map->get_height() << std::endl;

	// Test saving time
	start = clock.now();
	save_world(ctx, Configs::misc::save_file);
	end = clock.now();
	Logging::info("Saving the world took " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) + "ms");
}
