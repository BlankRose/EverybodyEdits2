/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - main.cpp                           */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, June 28, 2023 7:50 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "EverybodyEdits2.hpp"

int main()
{
	Context *ctx = nullptr;

	if (!configure("configs/settings.json")
		|| !get_ready(ctx))
		return EXIT_FAILURE;

	test(ctx);

	unload(ctx);
	Configs::save_configs("configs/settings.json");
	Logging::info("Software ended!");

	return EXIT_SUCCESS;
}
