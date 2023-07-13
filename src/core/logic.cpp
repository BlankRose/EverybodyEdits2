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
 * Applies the player's movement on the map. If the player is in god mode,
 * they can move freely in all directions. Otherwise, they can only move
 * horizontally, as long as there's no tiles in the way (tiles before id 10
 * are not collidable)
 * 
 * @param	ctx: Context of the target process
 * */
static void move_player(Context *&ctx)
{
	sf::RenderWindow &win = ctx->fw->get_window();
	World *world = ctx->game->getWorld();
	sf::View view = win.getView();

	// While in god mode, players can freely move in all directions
	if (ctx->getFlag(Context::GOD))
		view.move(
			(-ctx->getFlag(Context::LEFT) + ctx->getFlag(Context::RIGHT)) * 10.f,
			(-ctx->getFlag(Context::UP) + ctx->getFlag(Context::DOWN)) * 10.f
		);

	// While others, they can only move in the horizontal axis as long as
	// there's no tiles in the way (tiles before id 10 are not collidable)
	else
	{
		float move = (-ctx->getFlag(Context::LEFT) + ctx->getFlag(Context::RIGHT)) * 7.f;
		const sf::Vector2f &pos = view.getCenter();
		World::size_type x = pos.x / TILE_WIDTH, y = pos.y / TILE_HEIGHT;

		// Checks if there's a tile in the way (and set move to the closest position to colliding tile)
		if (move < 0)
		{
			// Check straight left
			if (world->has_tile(x - 1, y)
				&& world->get_fg_tile(x - 1, y).get_id() >= 10)
				move = x * TILE_WIDTH - pos.x + (TILE_WIDTH / 2);
			// If slightly down, also check lower left
			else if (pos.y > y * TILE_HEIGHT + (TILE_HEIGHT / 10 * 9)
				&& world->has_tile(x - 1, y + 1)
				&& world->get_fg_tile(x - 1, y + 1).get_id() >= 10)
				move = x * TILE_WIDTH - pos.x + (TILE_WIDTH / 2);
			// If slightly up, also check upper left
			else if (pos.y < y * TILE_HEIGHT + (TILE_HEIGHT / 10)
				&& world->has_tile(x - 1, y - 1)
				&& world->get_fg_tile(x - 1, y - 1).get_id() >= 10)
				move = x * TILE_WIDTH - pos.x + (TILE_WIDTH / 2);
		}
		else if (move > 0)
		{
			// Check straight right
			if (world->has_tile(x + 1, y)
				&& world->get_fg_tile(x + 1, y).get_id() >= 10)
				move = x * TILE_WIDTH - pos.x + (TILE_WIDTH / 2);
			// If slightly down, also check lower right
			else if (pos.y > y * TILE_HEIGHT + (TILE_HEIGHT / 10 * 9)
				&& world->has_tile(x + 1, y + 1)
				&& world->get_fg_tile(x + 1, y + 1).get_id() >= 10)
				move = x * TILE_WIDTH - pos.x + (TILE_WIDTH / 2);
			// If slightly up, also check upper right
			else if (pos.y < y * TILE_HEIGHT + (TILE_HEIGHT / 10)
				&& world->has_tile(x + 1, y - 1)
				&& world->get_fg_tile(x + 1, y - 1).get_id() >= 10)
				move = x * TILE_WIDTH - pos.x + (TILE_WIDTH / 2);
		}
		view.move(move, 0);
	}

	// Make sure the view doesn't go out of bounds
	sf::Vector2f center = view.getCenter();
	if (center.x < (TILE_WIDTH / 2))
		center.x = (TILE_WIDTH / 2);
	else if (center.x > world->get_width() * TILE_WIDTH - (TILE_WIDTH / 2))
		center.x = world->get_width() * TILE_WIDTH - (TILE_WIDTH / 2);
	if (center.y < (TILE_HEIGHT / 2))
		center.y = (TILE_HEIGHT / 2);
	else if (center.y > world->get_height() * TILE_HEIGHT - (TILE_HEIGHT / 2))
		center.y = world->get_height() * TILE_HEIGHT - (TILE_HEIGHT / 2);
	view.setCenter(center);

	// Apply the final view
	win.setView(view);
	ctx->game->moveCamera(view);
}

/**
 * Applies gravity on the player. Moving downwards until they collide with a tile.
 * (Usually called after move_player and ignored by god mode). Causes the player
 * clips back to the top or bottom of the tile they collided with if space is available
 * (no tile above or below and still within the map's bounds).
 * 
 * @param	ctx: Context of the target process
 * */
static void apply_gravity(Context *&ctx)
{
	sf::RenderWindow &win = ctx->fw->get_window();
	World *world = ctx->game->getWorld();
	sf::View view = win.getView();

	const sf::Vector2f &pos = view.getCenter();
	World::size_type x = pos.x / TILE_WIDTH, y = pos.y / TILE_HEIGHT;

	// If the player is not on the ground, move them down (unless out of bounds))
	// (Checks to prevent player going in half-tiles on edges)
	if ((!world->has_tile(x, y + 1) || world->get_fg_tile(x, y + 1).get_id() < 10)
		&& (!world->has_tile(x + 1, y + 1) || world->get_fg_tile(x + 1, y + 1).get_id() < 10 || pos.x < x * TILE_WIDTH + (TILE_WIDTH / 10 * 9))
		&& (!world->has_tile(x - 1, y + 1) || world->get_fg_tile(x - 1, y + 1).get_id() < 10 || pos.x > x * TILE_WIDTH + (TILE_WIDTH / 10)))
	{
		if (y + 1 >= world->get_height())
			view.setCenter(sf::Vector2f(pos.x, world->get_height() * TILE_HEIGHT - (TILE_HEIGHT / 2)));
		else
			view.move(0, 8.f);
	}
	// If the player is on the ground, clip them to the top of the tile
	else
		view.setCenter(sf::Vector2f(pos.x, (y + 1) * TILE_HEIGHT - (TILE_HEIGHT / 2)));

	// Apply the final view
	win.setView(view);
	ctx->game->moveCamera(view);
}

/**
 * Places a tile on the map. If the tile is already present, it will be ignored.
 * It also adds to the world's data new meta or remove them when neccessary.
 * 
 * @param	ctx: Context of the target process
 * */
static void place_tile(Context *&ctx)
{
	sf::RenderWindow &win = ctx->fw->get_window();
	World *world = ctx->game->getWorld();

	sf::Vector2f pos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
	sf::Vector2u tile_pos(pos.x / TILE_WIDTH, pos.y / TILE_HEIGHT);

	if (!world->has_tile(tile_pos.x, tile_pos.y))
		return;
	const Tile &tile = world->get_fg_tile(tile_pos.x, tile_pos.y);
	const Tile &selected = ctx->game->getSelected();
	if (tile == selected)
		return;

	if (tile.get_id() == _TILEID_SPAWN)
		world->remove_spawn({(World::size_type) tile_pos.x, (World::size_type) tile_pos.y});
	if (selected.get_id() == _TILEID_SPAWN)
		world->add_spawn({(World::size_type) tile_pos.x, (World::size_type) tile_pos.y});

	world->set_fg_tile(tile_pos.x, tile_pos.y, selected);
}

/**
 * Picks a tile on the map. Copying its whole data into the context's selected tile.
 * 
 * @param	ctx: Context of the target process
 * */
static void pick_tile(Context *&ctx)
{
	sf::RenderWindow &win = ctx->fw->get_window();
	World *world = ctx->game->getWorld();

	sf::Vector2f	pos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
	sf::Vector2u	tile_pos(pos.x / TILE_WIDTH, pos.y / TILE_HEIGHT);

	if (world->has_tile(tile_pos.x, tile_pos.y))
		ctx->game->setSelected(world->get_fg_tile(tile_pos.x, tile_pos.y));
}

/**
 * Logic Unit, which computes all of the
 * game's inner calculus and its systems
 * 
 * @param	ctx: Context of the target process
 * 
 * @return	True or False upon Success or Failure
 * */
bool logic_unit(Context *&ctx)
{
	if (ctx->getFlag(Context::UP) || ctx->getFlag(Context::DOWN)
		|| ctx->getFlag(Context::RIGHT) || ctx->getFlag(Context::LEFT))
		move_player(ctx);
	if (ctx->getFlag(Context::MOUSE_L) || ctx->getFlag(Context::MOUSE_R))
		place_tile(ctx);
	else if (ctx->getFlag(Context::MOUSE_M))
		pick_tile(ctx);
	if (!ctx->getFlag(Context::GOD))
		apply_gravity(ctx);
	return true;
}
