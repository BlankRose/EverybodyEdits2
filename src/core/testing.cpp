/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - testing.cpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 10, 2023 6:47 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "EverybodyEdits2.hpp"
#include <dirent.h>
#include <unistd.h>

/**
 * Testing unit to test some components of the software
 * 
 * @param	ctx: Context of the software
 * */
void	test(Context *ctx)
{
	__TIME_INIT
	Framework::window_type &win = ctx->fw->get_window();
	sf::View view = win.getView();
	int i = 0;

	while (i++ < 20)
	{
		__TIME_TEST("Rendering the world",
			win.clear();
			win.draw(*ctx->game);
			win.display();
		)

		__TIME_TEST("Moving the camera",
			view.move(0.f, 5.f);
			win.setView(view);
			ctx->game->moveCamera(view);
		)

		usleep(250000);
	}
}
