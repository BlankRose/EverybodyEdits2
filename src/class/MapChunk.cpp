/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - MapChunk.cpp                */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Tue Apr  4 15:15:09 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/MapChunk.hpp"
#include <limits>
#include <iostream>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using Tile = MapChunk::Tile;

using id_type = MapChunk::id_type;
using size_type = MapChunk::size_type;
using coord_type = MapChunk::coord_type;
using position_type = MapChunk::position_type;

const size_type		MapChunk::WIDTH = 50;
const size_type		MapChunk::HEIGHT = 50;
size_type			MapChunk::_tile_size = 50;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Tile::Tile():
	_vertex(nullptr), _coords(0, 0), _id(0) {}

Tile::Tile(const position_type &pos, sf::Vertex *vertex, const id_type &id):
	_vertex(vertex), _coords(pos) { set_id(id); }

Tile::Tile(const Tile &other)
	{ operator=(other); }

Tile::~Tile() {}

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

			get_tile_at(dx, dy) = Tile(position_type(dx, dy), quad, 0);
		}
}

MapChunk::~MapChunk() {}

	/** ---------------------- **/
	/*        OVERLOADS         */
	/** ---------------------- **/

Tile				&Tile::operator=(const Tile &other)
{
	_vertex = other._vertex;
	_coords = other._coords;
	set_id(other._id);

	return *this;
}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

sf::Vertex *		Tile::get_vertex() const
	{ return _vertex; }

position_type		Tile::get_position() const
	{ return _coords; }

id_type				Tile::get_id() const
	{ return _id; }

void				Tile::set_position(const position_type &pos)
	{ _coords = pos; }

void				Tile::set_id(const id_type &id)
{
	if (!_vertex)
		return;

	uint32_t				length = Assets::get_size().x;
	Assets::rect_type		coords = Assets::get_tile_coords(id % length, id / length);

	_id = id;
	_vertex[0].texCoords = sf::Vector2f(coords.x.x, coords.x.y);
	_vertex[1].texCoords = sf::Vector2f(coords.y.x, coords.x.y);
	_vertex[2].texCoords = sf::Vector2f(coords.y.x, coords.y.y);
	_vertex[3].texCoords = sf::Vector2f(coords.x.x, coords.y.y);
}

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
