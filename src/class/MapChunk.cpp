/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - MapChunk.cpp                */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Apr  7 19:36:43 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/MapChunk.hpp"
#include <sstream>
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

MapChunk::MapChunk(const coord_type &x, const coord_type &y,
			const bool &top_edge, const bool &low_edge,
			const bool &left_edge, const bool &right_edge):
	_position(x, y), _fg_tiles(WIDTH * HEIGHT), _bg_tiles(WIDTH * HEIGHT)
{
	_fg_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	_fg_vertices.resize(WIDTH * HEIGHT * 4);

	_bg_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	_bg_vertices.resize(WIDTH * HEIGHT * 4);

	for (size_type dx = 0; dx < WIDTH; dx++)
		for (size_type dy = 0; dy < HEIGHT; dy++)
		{
			sf::Vertex	*fg_quad = get_tilevertex(dx, dy);
			sf::Vertex	*bg_quad = get_tilevertex(dx, dy, true);
			float		pos_x = dx + x, pos_y = dy + y;

			fg_quad[0].position = sf::Vector2f(pos_x * _tile_size, pos_y * _tile_size);				// Upper Left
			fg_quad[1].position = sf::Vector2f((pos_x + 1) * _tile_size, pos_y * _tile_size);		// Upper Right
			fg_quad[2].position = sf::Vector2f((pos_x + 1) * _tile_size, (pos_y + 1) * _tile_size);	// Lower Right
			fg_quad[3].position = sf::Vector2f(pos_x * _tile_size, (pos_y + 1) * _tile_size);		// Lower Left

			bg_quad[0].position = sf::Vector2f(pos_x * _tile_size, pos_y * _tile_size);				// Upper Left
			bg_quad[1].position = sf::Vector2f((pos_x + 1) * _tile_size, pos_y * _tile_size);		// Upper Right
			bg_quad[2].position = sf::Vector2f((pos_x + 1) * _tile_size, (pos_y + 1) * _tile_size);	// Lower Right
			bg_quad[3].position = sf::Vector2f(pos_x * _tile_size, (pos_y + 1) * _tile_size);		// Lower Left

			get_tile_at(dx, dy, true) = Tile(position_type(dx, dy), bg_quad, 1, Assets::SPECIAL);
			if ((top_edge && !dx) || (low_edge && dx == WIDTH - 1)
				|| (left_edge && !dy) || (right_edge && dy == HEIGHT - 1))
				get_tile_at(dx, dy) = Tile(position_type(dx, dy), fg_quad, 1, Assets::BASIC);
			else
				get_tile_at(dx, dy) = Tile(position_type(dx, dy), fg_quad, 1, Assets::SPECIAL);
		}
}

MapChunk::MapChunk(const char *data):
	_fg_tiles(WIDTH * HEIGHT), _bg_tiles(WIDTH * HEIGHT)
{
	const uint32_t	*pos = (const uint32_t *) data;
	_position = MapChunk::position_type(*pos, *(pos + 1));

	_fg_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	_fg_vertices.resize(WIDTH * HEIGHT * 4);

	_bg_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	_bg_vertices.resize(WIDTH * HEIGHT * 4);

	const uint8_t	*tiles = (const uint8_t *) data + 2 * sizeof(uint32_t);
	for (size_type dx = 0; dx < WIDTH; dx++)
		for (size_type dy = 0; dy < HEIGHT; dy++)
		{
			sf::Vertex	*fg_quad = get_tilevertex(dx, dy);
			sf::Vertex	*bg_quad = get_tilevertex(dx, dy, true);
			float		pos_x = dx + _position.x, pos_y = dy + _position.y;

			fg_quad[0].position = sf::Vector2f(pos_x * _tile_size, pos_y * _tile_size);				// Upper Left
			fg_quad[1].position = sf::Vector2f((pos_x + 1) * _tile_size, pos_y * _tile_size);		// Upper Right
			fg_quad[2].position = sf::Vector2f((pos_x + 1) * _tile_size, (pos_y + 1) * _tile_size);	// Lower Right
			fg_quad[3].position = sf::Vector2f(pos_x * _tile_size, (pos_y + 1) * _tile_size);		// Lower Left

			bg_quad[0].position = sf::Vector2f(pos_x * _tile_size, pos_y * _tile_size);				// Upper Left
			bg_quad[1].position = sf::Vector2f((pos_x + 1) * _tile_size, pos_y * _tile_size);		// Upper Right
			bg_quad[2].position = sf::Vector2f((pos_x + 1) * _tile_size, (pos_y + 1) * _tile_size);	// Lower Right
			bg_quad[3].position = sf::Vector2f(pos_x * _tile_size, (pos_y + 1) * _tile_size);		// Lower Left

			uint32_t	base = (dy * WIDTH + dx) * 4;

			get_tile_at(dx, dy) = Tile(position_type(dx, dy), fg_quad, *(tiles + base), Assets::Packs(*(tiles + base + 1)));
			get_tile_at(dx, dy, true) = Tile(position_type(dx, dy), bg_quad, *(tiles + base + 2), Assets::Packs(*(tiles + base + 3)));
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

Tile				&MapChunk::get_tile_at(const coord_type &x, const coord_type &y, const bool &bg)
{
	if (bg) return _bg_tiles[y * WIDTH + x];
	return _fg_tiles[y * WIDTH + x];
}

const Tile			&MapChunk::get_tile_at(const coord_type &x, const coord_type &y, const bool &bg) const
{
	if (bg) return _bg_tiles[y * WIDTH + x];
	return _fg_tiles[y * WIDTH + x];
}

sf::Vertex *		MapChunk::get_tilevertex(const coord_type &x, const coord_type &y, const bool &bg)
{
	if (bg) return &_bg_vertices[(x + y * WIDTH) * 4];
	return &_fg_vertices[(x + y * WIDTH) * 4];
}

const sf::Vertex *	MapChunk::get_tilevertex(const coord_type &x, const coord_type &y, const bool &bg) const
{
	if (bg) return &_bg_vertices[(x + y * WIDTH) * 4];
	return &_fg_vertices[(x + y * WIDTH) * 4];
}

position_type		&MapChunk::get_position()
	{ return _position; }

const position_type	&MapChunk::get_position() const
	{ return _position; }

void				MapChunk::set_position(const position_type &pos)
	{ _position = pos; }

void				MapChunk::update_tile(const Tile &tile, const bool &bg)
{
	position_type	pos = tile.get_position();
	sf::Vertex		*cquad = get_tilevertex(pos.x, pos.y, bg);
	sf::Vertex		*tquad = tile.get_vertex();

	for (uint8_t i = 0; i < 4; i++)
		cquad[i].texCoords = tquad[i].texCoords;
	get_tile_at(pos.x, pos.y, bg) = tile;
}

std::string			MapChunk::as_data() const
{
	std::string		data;

	uint32_t	pos[2] = {_position.x, _position.y};
	data.append((char *) pos, 2 * sizeof(uint32_t));

	for (uint32_t i = 0, end = _fg_tiles.size(); i < end; i++)
	{
		uint8_t		tiles[4] = {
			_fg_tiles[i].get_id(), static_cast<uint8_t>(_fg_tiles[i].get_group()),
			_bg_tiles[i].get_id(), static_cast<uint8_t>(_bg_tiles[i].get_group())};
		data.append((char *) tiles, 4 * sizeof(uint8_t));
	}
	return data;
}

void				MapChunk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &Assets::get_tilemap(true);
	target.draw(_bg_vertices, states);
	states.texture = &Assets::get_tilemap();
	target.draw(_fg_vertices, states);
}
