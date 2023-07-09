/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - testing.cpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Sunday, July 9, 2023 8:07 PM           */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "EverybodyEdits2.hpp"
#include <unistd.h>

/**
 * Testing unit to test some components of the software
 * 
 * @param	ctx: Context of the software
 * */
void	test(Context *ctx)
{
	__TIME_INIT
	sf::View view = ctx->fw->get_window().getView();
	int i = 0;

	while (i++ < 20)
	{
		__TIME_TEST("Rendering the world",
			ctx->fw->get_window().clear();
			ctx->game->render(ctx->fw);
			ctx->fw->get_window().display();
		)

		__TIME_TEST("Moving the camera",
			view.move(0.f, 5.f);
			ctx->fw->get_window().setView(view);
			ctx->game->moveCamera(view);
		)

		usleep(250000);
	}
}
