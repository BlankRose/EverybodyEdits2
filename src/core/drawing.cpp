/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - drawing.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Apr  6 16:47:28 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * Drawing loop, which handles all of the
 * SFML drawings elements onto the target window
 * 
 * @param	ctx: Context of the target instance
 * */
void	draws_unit(Context *&ctx)
{
	sf::RenderWindow	&win = ctx->fw->get_window();
	while (win.isOpen())
	{
		event_unit(ctx);
		if (!win.isOpen())
			break;

		logic_unit(ctx);
		if (!win.isOpen())
			break;

		win.clear();
		ctx->map->render(ctx->fw);
		ctx->ui->render(ctx->fw);
		win.display();
	}
}
