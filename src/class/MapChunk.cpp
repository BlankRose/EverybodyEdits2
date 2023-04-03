/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - MapChunk.cpp                */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Mon Apr  3 18:38:40 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/MapChunk.hpp"
#include <limits>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using size_type = MapChunk::size_type;
using position_type = MapChunk::position_type;

const size_type		MapChunk::WIDTH = 5;
const size_type		MapChunk::HEIGHT = 5;
size_type			MapChunk::_tile_size = 50;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

MapChunk::MapChunk():
	MapChunk(0, 0) {}

MapChunk::MapChunk(const size_type &x, const size_type &y)
{
	_position = position_type(x * _tile_size, y * _tile_size);
	_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	_vertices.resize(WIDTH * HEIGHT * 4);

	for (size_type dx = 0; dx < WIDTH; dx++)
	{
		for (size_type dy = 0; dy < HEIGHT; dy++)
		{
			sf::Vertex	*quad = &_vertices[(dx + dy * WIDTH) * 4];
			float	pos_x = dx + x, pos_y = dy + y;

			quad[0].position = sf::Vector2f(pos_x * _tile_size, pos_y * _tile_size);				// Upper Left
			quad[1].position = sf::Vector2f((pos_x + 1) * _tile_size, pos_y * _tile_size);			// Upper Right
			quad[2].position = sf::Vector2f((pos_x + 1) * _tile_size, (pos_y + 1) * _tile_size);	// Lower Right
			quad[3].position = sf::Vector2f(pos_x * _tile_size, (pos_y + 1) * _tile_size);			// Lower Left

			Assets::rect_type coords = Assets::get_tile_coords(0, 0);

			quad[0].texCoords = sf::Vector2f(coords.x.x, coords.x.y);
			quad[1].texCoords = sf::Vector2f(coords.y.x, coords.x.y);
			quad[2].texCoords = sf::Vector2f(coords.y.x, coords.y.y);
			quad[3].texCoords = sf::Vector2f(coords.x.x, coords.y.y);
		}
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

sf::Vertex			&MapChunk::get_tilevertex(const size_type &x, const size_type &y)
	{ return _vertices[(x + y * WIDTH) * 4]; }

const sf::Vertex	&MapChunk::get_tilevertex(const size_type &x, const size_type &y) const
	{ return _vertices[(x + y * WIDTH) * 4]; }

void				MapChunk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &Assets::get_tilemap();

	target.draw(_vertices, states);
}

position_type		&MapChunk::get_position()
	{ return _position; }

const position_type	&MapChunk::get_position() const
	{ return _position; }

void				MapChunk::set_position(const position_type &pos)
	{ _position = pos; }
