/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - logic.cpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Apr  7 13:44:03 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * Logic Unit, which computes all of the
 * game's inner calculus and its systems
 * 
 * @param	ctx: Context of the target process
 * 
 * @return	True or False upon Success or Failure
 * */
bool	logic_unit(Context *&ctx)
{
	sf::RenderWindow &win = ctx->fw->get_window();
	World *world = ctx->game->getWorld();

	if (ctx->up || ctx->down || ctx->right || ctx->left)
	{
		// Move the view to the right direction
		sf::View view = win.getView();
		view.move((-ctx->left + ctx->right) * 10.f, (-ctx->up + ctx->down) * 10.f);

		// Make sure the view doesn't go out of bounds
		sf::Vector2f center = view.getCenter();
		if (center.x < TILE_WIDTH / 2)
			center.x = TILE_WIDTH / 2;
		else if (center.x > world->get_width() * TILE_WIDTH - TILE_WIDTH / 2)
			center.x = world->get_width() * TILE_WIDTH - TILE_WIDTH / 2;
		if (center.y < TILE_HEIGHT / 2)
			center.y = TILE_HEIGHT / 2;
		else if (center.y > world->get_height() * TILE_HEIGHT - TILE_HEIGHT / 2)
			center.y = world->get_height() * TILE_HEIGHT - TILE_HEIGHT / 2;
		view.setCenter(center);

		// Apply the final view
		win.setView(view);
		ctx->game->moveCamera(view);
	}

	if (ctx->mouse_L || ctx->mouse_R)
	{
		sf::Vector2f	pos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
		sf::Vector2u	tile_pos(pos.x / TILE_WIDTH, pos.y / TILE_HEIGHT);

		if (world->has_tile(tile_pos.x, tile_pos.y))
			world->set_fg_tile(tile_pos.x, tile_pos.y, ctx->game->getSelected());
	}

	else if (ctx->mouse_M)
	{
		sf::Vector2f	pos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
		sf::Vector2u	tile_pos(pos.x / TILE_WIDTH, pos.y / TILE_HEIGHT);

		if (world->has_tile(tile_pos.x, tile_pos.y))
			ctx->game->setSelected(world->get_fg_tile(tile_pos.x, tile_pos.y));
	}

	return true;
}
