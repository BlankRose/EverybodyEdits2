/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - GameView.cpp                       */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Friday, June 30, 2023 6:27 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/GameView.hpp"
#include "base/Assets.hpp"

/** ---------------------- **/
/*        ATTRIBUTES        */
/** ---------------------- **/

using pos_type = GameView::pos_type;
using vertex_array = GameView::vertex_array;

#define CHUNK_SIZE 50
#define TILE_SCALE 16

/** ---------------------- **/
/*       CONSTRUCTORS       */
/** ---------------------- **/

GameView::Chunk::Chunk():
	_fg_vertices(sf::Quads, CHUNK_SIZE * CHUNK_SIZE * 4),
	_bg_vertices(sf::Quads, CHUNK_SIZE * CHUNK_SIZE * 4)
{
	for (uint8_t x = 0; x < CHUNK_SIZE; x++)
		for (uint8_t y = 0; y < CHUNK_SIZE; y++)
		{
			sf::Vertex *fg_quad = &_fg_vertices[(x + y * CHUNK_SIZE) * 4];
			sf::Vertex *bg_quad = &_bg_vertices[(x + y * CHUNK_SIZE) * 4];

			fg_quad[0].position = sf::Vector2f(x * TILE_SCALE, y * TILE_SCALE);
			fg_quad[1].position = sf::Vector2f((x + 1) * TILE_SCALE, y * TILE_SCALE);
			fg_quad[2].position = sf::Vector2f((x + 1) * TILE_SCALE, (y + 1) * TILE_SCALE);
			fg_quad[3].position = sf::Vector2f(x * TILE_SCALE, (y + 1) * TILE_SCALE);

			bg_quad[0].position = sf::Vector2f(x * TILE_SCALE, y * TILE_SCALE);
			bg_quad[1].position = sf::Vector2f((x + 1) * TILE_SCALE, y * TILE_SCALE);
			bg_quad[2].position = sf::Vector2f((x + 1) * TILE_SCALE, (y + 1) * TILE_SCALE);
			bg_quad[3].position = sf::Vector2f(x * TILE_SCALE, (y + 1) * TILE_SCALE);
		}
}

GameView::Chunk::~Chunk() {}

GameView::GameView(World *world, const pos_type &position) : _world(world), _position(position)
{
	// Assign chunk positions
	// (-1, -1) for top left, (0, 0) for center, (1, 1) for bottom right
	for (uint8_t i = 0; i < 9; i++)
		_chunks[i].setPosition(
			(CHUNK_SIZE * TILE_SCALE) * (i % 3 - 1),
			(CHUNK_SIZE * TILE_SCALE) * (i / 3 - 1)
		);
}

GameView::~GameView() {}

/** ---------------------- **/
/*          METHODS         */
/** ---------------------- **/

World *GameView::get_world() const { return _world; }
const pos_type &GameView::get_position() const { return _position; }
pos_type &GameView::get_position() { return _position; }

void GameView::set_world(World *world) { _world = world; }
void GameView::set_position(const pos_type &position) { _position = position; }

/**
 * Update the internal position of the view
 * (Usually being the main player's position)
 * 
 * When moving from one chunk to another, it will move the chunks around,
 * destroying the farthest ones and creating the nearest ones.
 * */
void GameView::update_position(const pos_type &position)
{
	if (position == _position)
		return;

	// Direction: 1st byte: left, 2nd byte: right, 3rd byte: up, 4th byte: down
	uint8_t direction =
		(position.x < _position.x) << 3 |
		(position.x > _position.x) << 2 |
		(position.y < _position.y) << 1 |
		(position.y > _position.y);

	// Move the chunks around
	// ...
}

/**
 * Force update the display of a tile
 * (Usually called when a tile is changed)
 * */
void GameView::update_tile(const pos_type &position)
{
	Tile &fg_tile = _world->get_fg_tile(position.x, position.y);
	Tile &bg_tile = _world->get_bg_tile(position.x, position.y);

	// Calculate the position relative to the view
	// ...
}

void GameView::Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &Assets::get_tilemap();
	target.draw(_fg_vertices, states);

	states.texture = &Assets::get_tilemap(true);
	target.draw(_bg_vertices, states);
}

void GameView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (uint8_t i = 0; i < 9; i++)
		_chunks[i].draw(target, states);
}
