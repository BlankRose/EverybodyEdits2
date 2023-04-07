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
	sf::RenderWindow	&win = ctx->fw->get_window();

	if (ctx->display == Context::LOADING && !ctx->map)
	{
		draws_unit(ctx);
		if (!load_world(ctx, Configs::misc::save_file)
			&& !new_world(ctx))
			return false;
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
	return true;
}
