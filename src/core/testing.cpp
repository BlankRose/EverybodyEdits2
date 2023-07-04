/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - testing.cpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, July 4, 2023 10:29 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "EverybodyEdits2.hpp"
#include <chrono>
#include <unistd.h>

#define __TIME_TEST(label, x) \
	start = clock.now(); \
	x; \
	end = clock.now(); \
	Logging::info(label + std::string(" took ") + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) + "ms");

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
	__TIME_TEST("Loading the world",
		if (!ctx->game->loadWorld(Configs::misc::save_file))
			ctx->game->newWorld(Configs::misc::test_width, Configs::misc::test_height);
	);

	World *world = ctx->game->getWorld();
	std::cout << "World size: " << world->get_width() << "x" << world->get_height() << std::endl;

	// Test initialize camera time
	sf::View view = ctx->fw->get_window().getView();
	//view.setCenter(0, 0);
	//ctx->fw->get_window().setView(view);

	__TIME_TEST("Initializing the camera",
		ctx->game->newCamera(view);
	);

	// Test rendering time
	__TIME_TEST("Rendering the world",
		ctx->fw->get_window().clear();
		ctx->game->render(ctx->fw);
		ctx->fw->get_window().display();
	);
	//sleep(2);

	// Test saving time
	__TIME_TEST("Saving the world",
		ctx->game->saveWorld(Configs::misc::save_file);
	);
}
