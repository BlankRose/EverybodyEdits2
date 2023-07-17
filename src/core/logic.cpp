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
 * Defines wether or not the player's gravity has been enforced by a tile.
 * If so, it will set the gravity's direction according to the tile's id.
 * 
 * @param	ctx: Context of the target process
 * */
static void set_forced_gravity(Context *&ctx)
{
	const sf::Vector2f &pos = ctx->fw->get_window().getView().getCenter();
	Tile::id_type id = ctx->game->getWorld()->get_fg_tile(pos.x / TILE_WIDTH, pos.y / TILE_HEIGHT).get_id();

	if (id == _TILEID_UP || id == _TILEID_DOWN || id == _TILEID_LEFT || id == _TILEID_RIGHT)
	{
		ctx->setFlag(Context::FORCED_GRAVITY_FLIP, id == _TILEID_UP || id == _TILEID_LEFT);
		ctx->setFlag(Context::FORCED_GRAVITY_SIDE, id == _TILEID_LEFT || id == _TILEID_RIGHT);
		ctx->enableFlag(Context::FORCED_GRAVITY);
	}
	else
		ctx->disableFlag(Context::FORCED_GRAVITY);
}

/**
 * Convert player's inputs into movements, and apply them to the player.
 * While in god mode, players can freely move in all directions, without
 * any restriction. Otherwise, they can only move according to the gravity
 * they were given, and with the restriction of collidable tiles.
 * 
 * @param	ctx: Context of the target process
 * */
static void move_player(Context *&ctx)
{
	sf::RenderWindow &win = ctx->fw->get_window();
	World *world = ctx->game->getWorld();
	sf::View view = win.getView();
	sf::Vector2f pos = view.getCenter();

	// While in god mode, players can freely move in all directions
	if (ctx->getFlag(Context::GOD))
		view.move(
			(-ctx->getFlag(Context::LEFT) + ctx->getFlag(Context::RIGHT)) * 10.f,
			(-ctx->getFlag(Context::UP) + ctx->getFlag(Context::DOWN)) * 10.f
		);

	// While others, they can only move in the horizontal axis as long as
	// there's no tiles in the way (tiles before id 10 are not collidable)
	// (Sideways gravity version)
	else if (ctx->getFlag(Context::FORCED_GRAVITY)
		? ctx->getFlag(Context::FORCED_GRAVITY_SIDE)
		: ctx->getFlag(Context::GRAVITY_SIDE))
	{
		float move = (-ctx->getFlag(Context::UP) + ctx->getFlag(Context::DOWN)) * 7.f;
		World::size_type x = pos.x / TILE_WIDTH, y = pos.y / TILE_HEIGHT;

		// Checks if there's a tile in the way
		// (and set move to the closest position to colliding tile)
		if ((move < 0 &&
					((world->has_tile(x, y - 1)
					&& world->get_fg_tile(x, y - 1).get_id() >= 10)
				|| (pos.x > x * TILE_WIDTH + (TILE_WIDTH - 1.f)
					&& world->has_tile(x + 1, y - 1)
					&& world->get_fg_tile(x + 1, y - 1).get_id() >= 10)
				|| (pos.x < x * TILE_WIDTH + (1.f)
					&& world->has_tile(x - 1, y - 1)
					&& world->get_fg_tile(x - 1, y - 1).get_id() >= 10)))
			|| (move > 0 &&
					((world->has_tile(x, y + 1)
					&& world->get_fg_tile(x, y + 1).get_id() >= 10)
				|| (pos.x > x * TILE_WIDTH + (TILE_WIDTH - 1.f)
					&& world->has_tile(x + 1, y + 1)
					&& world->get_fg_tile(x + 1, y + 1).get_id() >= 10)
				|| (pos.x < x * TILE_WIDTH + (1.f)
					&& world->has_tile(x - 1, y + 1)
					&& world->get_fg_tile(x - 1, y + 1).get_id() >= 10))))
			move = y * TILE_HEIGHT - pos.y + (TILE_HEIGHT / 2);
		view.move(0, move);
	}

	// Same as above, but for the vertical axis
	// (Regular gravity version)
	else
	{
		float move = (-ctx->getFlag(Context::LEFT) + ctx->getFlag(Context::RIGHT)) * 7.f;
		World::size_type x = pos.x / TILE_WIDTH, y = pos.y / TILE_HEIGHT;

		// Checks if there's a tile in the way
		// (and set move to the closest position to colliding tile)
		if ((move < 0 &&
					((world->has_tile(x - 1, y)
					&& world->get_fg_tile(x - 1, y).get_id() >= 10)
				|| (pos.y > y * TILE_HEIGHT + (TILE_HEIGHT - 1.f)
					&& world->has_tile(x - 1, y + 1)
					&& world->get_fg_tile(x - 1, y + 1).get_id() >= 10)
				|| (pos.y < y * TILE_HEIGHT + (1.f)
					&& world->has_tile(x - 1, y - 1)
					&& world->get_fg_tile(x - 1, y - 1).get_id() >= 10)))
			|| (move > 0 &&
					((world->has_tile(x + 1, y)
					&& world->get_fg_tile(x + 1, y).get_id() >= 10)
				|| (pos.y > y * TILE_HEIGHT + (TILE_HEIGHT - 1.f)
					&& world->has_tile(x + 1, y + 1)
					&& world->get_fg_tile(x + 1, y + 1).get_id() >= 10)
				|| (pos.y < y * TILE_HEIGHT + (1.f)
					&& world->has_tile(x + 1, y - 1)
					&& world->get_fg_tile(x + 1, y - 1).get_id() >= 10))))
			move = x * TILE_WIDTH - pos.x + (TILE_WIDTH / 2);
		view.move(move, 0);
	}

	// Make sure the view doesn't go out of bounds
	pos = view.getCenter();
	if (pos.x < (TILE_WIDTH / 2))
		pos.x = (TILE_WIDTH / 2);
	else if (pos.x > world->get_width() * TILE_WIDTH - (TILE_WIDTH / 2))
		pos.x = world->get_width() * TILE_WIDTH - (TILE_WIDTH / 2);
	if (pos.y < (TILE_HEIGHT / 2))
		pos.y = (TILE_HEIGHT / 2);
	else if (pos.y > world->get_height() * TILE_HEIGHT - (TILE_HEIGHT / 2))
		pos.y = world->get_height() * TILE_HEIGHT - (TILE_HEIGHT / 2);
	view.setCenter(pos);

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

	bool gravity_flip = ctx->getFlag(Context::FORCED_GRAVITY)
		? ctx->getFlag(Context::FORCED_GRAVITY_FLIP)
		: ctx->getFlag(Context::GRAVITY_FLIP);
	bool gravity_side = ctx->getFlag(Context::FORCED_GRAVITY)
		? ctx->getFlag(Context::FORCED_GRAVITY_SIDE)
		: ctx->getFlag(Context::GRAVITY_SIDE);
	int flip = gravity_flip ? -1 : 1;
	float fall = 12.f * flip;

	// If the player is not on the ground, move them down (unless out of bounds))
	// (Checks to prevent player going in half-tiles on edges)
	if (!gravity_side)
	{
		/*if ((!world->has_tile(x, y + flip)
				|| world->get_fg_tile(x, y + flip).get_id() < 10)
			&& (!world->has_tile(x + 1, y + flip)
				|| world->get_fg_tile(x + 1, y + flip).get_id() < 10
				|| pos.x < x * TILE_WIDTH + (TILE_WIDTH - .5f))
			&& (!world->has_tile(x - 1, y + flip)
				|| world->get_fg_tile(x - 1, y + flip).get_id() < 10
				|| pos.x > x * TILE_WIDTH + (.5f)))*/

		if (world->has_tile(x, y + flip)
			&& world->get_fg_tile(x, y + flip).get_id() < 10
			&& world->has_tile(x + 1, y + flip)
			&& world->has_tile(x - 1, y + flip))
		{
			if (y + flip >= world->get_height() && y + flip < 0)
				view.setCenter(sf::Vector2f(pos.x, world->get_height() * TILE_HEIGHT - (TILE_HEIGHT / 2)));
			else
			{
				// Checks if the player is slightly within a tile, if so, move it out
				if ((pos.x - x * TILE_WIDTH > (TILE_WIDTH / 2)
						&& world->has_tile(x + 1, y + flip)
						&& world->get_fg_tile(x + 1, y + flip).get_id() >= 10)
					|| (pos.x - x * TILE_WIDTH < (TILE_WIDTH / 2)
						&& world->has_tile(x - 1, y + flip)
						&& world->get_fg_tile(x - 1, y + flip).get_id() >= 10))
					view.move(x * TILE_WIDTH - pos.x + (TILE_WIDTH / 2), fall);
				else
					view.move(0, fall);
			}
		}
		// If the player is on the ground, clip them to the top of the tile
		else
			view.setCenter(sf::Vector2f(pos.x, (y + 1) * TILE_HEIGHT - (TILE_HEIGHT / 2)));
	}
	else
	{
		/*if ((!world->has_tile(x + flip, y)
				|| world->get_fg_tile(x + flip, y).get_id() < 10)
			&& (!world->has_tile(x + flip, y + 1)
				|| world->get_fg_tile(x + flip, y + 1).get_id() < 10
				|| pos.y < y * TILE_HEIGHT + (TILE_HEIGHT - .5f))
			&& (!world->has_tile(x + flip, y - 1)
				|| world->get_fg_tile(x + flip, y - 1).get_id() < 10
				|| pos.y > y * TILE_HEIGHT + (.5f)))*/

		if (world->has_tile(x + flip, y)
			&& world->get_fg_tile(x + flip, y).get_id() < 10
			&& world->has_tile(x + flip, y + 1)
			&& world->has_tile(x + flip, y - 1))
		{
			if (x + flip >= world->get_width() && x + flip < 0)
				view.setCenter(sf::Vector2f(world->get_width() * TILE_WIDTH - (TILE_WIDTH / 2), pos.y));
			else
			{
				// Checks if the player is slightly within a tile, if so, move it out
				if ((pos.y - y * TILE_HEIGHT > (TILE_HEIGHT / 2)
						&& world->has_tile(x + flip, y + 1)
						&& world->get_fg_tile(x + flip, y + 1).get_id() >= 10)
					|| (pos.y - y * TILE_HEIGHT < (TILE_HEIGHT / 2)
						&& world->has_tile(x + flip, y - 1)
						&& world->get_fg_tile(x + flip, y - 1).get_id() >= 10))
					view.move(fall, y * TILE_HEIGHT - pos.y + (TILE_HEIGHT / 2));
				else
					view.move(fall, 0);
			}
		}
		// If the player is on the ground, clip them to the top of the tile
		else
			view.setCenter(sf::Vector2f((x + 1) * TILE_WIDTH - (TILE_WIDTH / 2), pos.y));
	}

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
	if (ctx->game->getSelector()->interact(ctx->fw->get_window()))
		return;

	sf::RenderWindow &win = ctx->fw->get_window();
	World *world = ctx->game->getWorld();

	sf::Vector2f pos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
	sf::Vector2u tile_pos(pos.x / TILE_WIDTH, pos.y / TILE_HEIGHT);

	if (!world->has_tile(tile_pos.x, tile_pos.y))
		return;
	const Tile &selected = ctx->game->getSelected();
	const bool &bg = ctx->game->isSelectedBackground();

	if (!bg)
	{
		const Tile &tile = world->get_fg_tile(tile_pos.x, tile_pos.y);
		if (tile == selected)
			return;
		if (tile.get_id() == _TILEID_SPAWN)
			world->remove_spawn({(World::size_type) tile_pos.x, (World::size_type) tile_pos.y});
		if (selected.get_id() == _TILEID_SPAWN)
			world->add_spawn({(World::size_type) tile_pos.x, (World::size_type) tile_pos.y});
		world->set_fg_tile(tile_pos.x, tile_pos.y, selected);
	}
	else
	{
		const Tile &tile = world->get_bg_tile(tile_pos.x, tile_pos.y);
		if (tile == selected)
			return;
		world->set_bg_tile(tile_pos.x, tile_pos.y, selected);
	}
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
		ctx->game->setSelected(
			world->get_tile(tile_pos.x, tile_pos.y, ctx->getFlag(Context::BACKGROUND)),
			ctx->getFlag(Context::BACKGROUND));
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
	set_forced_gravity(ctx);
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
