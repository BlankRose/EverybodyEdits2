/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - MapChunk.cpp                */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Wed Apr  5 20:43:07 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/MapChunk.hpp"
#include <limits>
#include <iostream>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using size_type = MapChunk::size_type;
using coord_type = MapChunk::coord_type;
using position_type = MapChunk::position_type;

const size_type		MapChunk::WIDTH = 50;
const size_type		MapChunk::HEIGHT = 50;
size_type			MapChunk::_tile_size = 50;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

MapChunk::MapChunk():
	MapChunk(0, 0) {}

MapChunk::MapChunk(const coord_type &x, const coord_type &y):
	_tiles(WIDTH * HEIGHT), _position(x, y)
{
	_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	_vertices.resize(WIDTH * HEIGHT * 4);

	for (size_type dx = 0; dx < WIDTH; dx++)
		for (size_type dy = 0; dy < HEIGHT; dy++)
		{
			sf::Vertex	*quad = get_tilevertex(dx, dy);
			float		pos_x = dx + x, pos_y = dy + y;

			quad[0].position = sf::Vector2f(pos_x * _tile_size, pos_y * _tile_size);				// Upper Left
			quad[1].position = sf::Vector2f((pos_x + 1) * _tile_size, pos_y * _tile_size);			// Upper Right
			quad[2].position = sf::Vector2f((pos_x + 1) * _tile_size, (pos_y + 1) * _tile_size);	// Lower Right
			quad[3].position = sf::Vector2f(pos_x * _tile_size, (pos_y + 1) * _tile_size);			// Lower Left

			get_tile_at(dx, dy) = Tile(position_type(dx, dy), quad, 2, "basic");
		}
}

MapChunk::~MapChunk() {}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

void				MapChunk::set_tilesize(const size_type &size) /* STATIC */ 
	{ _tile_size = size; }

size_type			&MapChunk::get_tilesize() /* STATIC */
	{ return _tile_size; }

Tile				&MapChunk::get_tile_at(const coord_type &x, const coord_type &y)
	{ return _tiles[y * WIDTH + x]; }

const Tile			&MapChunk::get_tile_at(const coord_type &x, const coord_type &y) const
	{ return _tiles[y * WIDTH + x]; }

sf::Vertex *		MapChunk::get_tilevertex(const coord_type &x, const coord_type &y)
	{ return &_vertices[(x + y * WIDTH) * 4]; }

const sf::Vertex *	MapChunk::get_tilevertex(const coord_type &x, const coord_type &y) const
	{ return &_vertices[(x + y * WIDTH) * 4]; }

position_type		&MapChunk::get_position()
	{ return _position; }

const position_type	&MapChunk::get_position() const
	{ return _position; }

void				MapChunk::set_position(const position_type &pos)
	{ _position = pos; }

void				MapChunk::update_tile(const Tile &tile)
{
	position_type	pos = tile.get_position();
	sf::Vertex		*cquad = get_tilevertex(pos.x, pos.y);
	sf::Vertex		*tquad = tile.get_vertex();

	for (uint8_t i = 0; i < 4; i++)
		cquad[i].texCoords = tquad[i].texCoords;
	get_tile_at(pos.x, pos.y) = tile;
}

void				MapChunk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &Assets::get_tilemap();

	target.draw(_vertices, states);
}
