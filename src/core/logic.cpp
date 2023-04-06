/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - logic.cpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Apr  6 21:23:03 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * Logic Unit, which computes all of the
 * game's inner calculus and its systems
 * 
 * @param	ctx: Context of the target process
 * */
void	logic_unit(Context *&ctx)
{
	sf::RenderWindow	&win = ctx->fw->get_window();

	if (ctx->display == Context::LOADING && !ctx->map)
	{
		draws_unit(ctx);
		ctx->map = new World(Configs::misc::test_width, Configs::misc::test_height);
		if (!ctx->map)
		{
			Logging::fatal("Couldn't generate the target World!");
			return;
		}
		ctx->display = Context::WORLD;
	}

	if (ctx->up || ctx->down || ctx->right || ctx->left)
	{
		sf::View		view = win.getView();
		view.move((-ctx->left + ctx->right) * 10.f, (-ctx->up + ctx->down) * 10.f);
		win.setView(view);
	}

	if (ctx->mouse_L || ctx->mouse_R)
	{
		sf::Vector2f	pos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
		sf::Vector2u	tile_pos(pos.x / MapChunk::get_tilesize(), pos.y / MapChunk::get_tilesize());

		if (ctx->map->has_tile(tile_pos))
		{
			Tile			tile = ctx->ui->get_selected();
			tile.set_position(ctx->map->get_tile_at(tile_pos).get_position());
			ctx->map->get_chunk_at(tile_pos).update_tile(tile);
		}
	}

	else if (ctx->mouse_M)
	{
		sf::Vector2f	pos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
		sf::Vector2u	tile_pos(pos.x / MapChunk::get_tilesize(), pos.y / MapChunk::get_tilesize());

		if (ctx->map->has_tile(tile_pos))
		{
			Tile		target = ctx->map->get_tile_at(tile_pos);
			ctx->ui->set_selected(target.get_id(), target.get_group());
		}
	}
}
