/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - main.cpp                           */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Sunday, July 9, 2023 8:48 PM           */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "EverybodyEdits2.hpp"
#define CONFIG_FILE "configs/settings.json"

int main()
{
	Context *ctx = nullptr;

	if (!configure(CONFIG_FILE)
		|| !get_ready(ctx))
		return EXIT_FAILURE;

	if (!prepareGame(ctx))
	{
		unload(ctx);
		Logging::error("Failed to load world!");
		return EXIT_FAILURE;
	}

	//test(ctx);
	threads_unit(ctx);

	unloadGame(ctx);
	unload(ctx);

	Configs::save_configs(CONFIG_FILE);
	Logging::info("Software ended!");

	return EXIT_SUCCESS;
}
