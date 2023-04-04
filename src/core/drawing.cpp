/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - drawing.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Tue Apr  4 15:10:37 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * Drawing loop, which handles all of the
 * SFML drawings elements onto the target window
 * 
 * @param	ctx: Context of the target instance
 * */
void	draw_loop(Context *&ctx)
{
	sf::RenderWindow	&win = ctx->fw->get_window();
	sf::View			view = win.getView();

	while (win.isOpen())
	{
		event_cycle(ctx);

		if (ctx->up || ctx->down || ctx->right || ctx->left)
		{
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
				ctx->ui->set_selected(ctx->map->get_tile_at(tile_pos).get_id());
		}

		win.clear();
		ctx->map->render(ctx->fw);
		ctx->ui->render(ctx->fw);
		win.display();
	}
}
