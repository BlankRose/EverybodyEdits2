/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   class - World.cpp                                    */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, June 27, 2023 6:21 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "class/World.hpp"
#include "class/Framework.hpp"
#include "class/Context.hpp"
#include <cmath>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using size_type = World::size_type;
using chunks_type = World::chunks_type;
using data_type = World::data_type;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

World::World(const size_type &width, const size_type &height):
	_width(width), _height(height),
	_chunks_width((width / MapChunk::WIDTH) + (width % MapChunk::WIDTH ? 1 : 0)),
	_chunks_height((height / MapChunk::HEIGHT) + (height % MapChunk::HEIGHT ? 1 : 0)),
	_chunks(_chunks_width * _chunks_height)
{
	for (uint32_t x = 0; x < _chunks_width; x++)
		for (uint32_t y = 0; y < _chunks_height; y++)
			_chunks[y * _chunks_width + x] = MapChunk(
				x * MapChunk::WIDTH, y * MapChunk::HEIGHT, !x,
				x == _chunks_width - 1, !y, y == _chunks_height - 1);
}

World::World(const size_type &width, const size_type &height, const data_type &data):
	_width(width), _height(height),
	_chunks_width((width / MapChunk::WIDTH) + (width % MapChunk::WIDTH ? 1 : 0)),
	_chunks_height((height / MapChunk::HEIGHT) + (height % MapChunk::HEIGHT ? 1 : 0)),
	_chunks(_chunks_width * _chunks_height)
{
	for (uint32_t i = 0; i < data.size(); i++)
		_chunks[i] = MapChunk(data[i].c_str());
}

World::~World() {}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

bool		World::has_chunk(const sf::Vector2u &pos) const
{
	return pos.x / MapChunk::WIDTH < _chunks_width
		&& pos.y / MapChunk::HEIGHT < _chunks_height;
}

bool		World::has_chunk(const size_type &x, const size_type &y) const
{
	return x / MapChunk::WIDTH < _chunks_width
		&& y / MapChunk::HEIGHT < _chunks_height;
}

bool		World::has_tile(const sf::Vector2u &pos) const
	{ return pos.x < _width && pos.y < _height; }

bool		World::has_tile(const size_type &x, const size_type &y) const
	{ return x < _width && y < _height; }

MapChunk	&World::get_chunk_at(const sf::Vector2u &pos)
	{ return _chunks[(pos.y / MapChunk::HEIGHT) * _chunks_width + pos.x / MapChunk::WIDTH]; }

MapChunk	&World::get_chunk_at(const size_type &x, const size_type &y)
	{ return _chunks[(y / MapChunk::HEIGHT) * _chunks_width + x / MapChunk::WIDTH]; }

Tile		&World::get_tile_at(const sf::Vector2u &pos)
	{ return get_chunk_at(pos).get_tile_at(pos.x % MapChunk::WIDTH, pos.y % MapChunk::HEIGHT); }

Tile		&World::get_tile_at(const size_type &x, const size_type &y)
	{ return get_chunk_at(x, y).get_tile_at(x % MapChunk::WIDTH, y % MapChunk::HEIGHT); }

void		World::render(Framework *&fw)
{
	size_type		tile_size = MapChunk::get_tilesize();
	sf::Vector2f	center = fw->get_view().getCenter();
	sf::Vector2f	size = fw->get_view().getSize();

	sf::FloatRect	view_bounds(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);
	sf::Vector2f	begin(
		std::max(0.f, std::floor(view_bounds.left / tile_size)),
		std::max(0.f, std::floor(view_bounds.top / tile_size)));
	sf::Vector2f	end(
		std::min(float(_chunks_width * MapChunk::WIDTH),
			std::ceil((view_bounds.left + view_bounds.width) / tile_size + MapChunk::WIDTH)),
		std::min(float(_chunks_height * MapChunk::HEIGHT),
			std::ceil((view_bounds.top + view_bounds.height) / tile_size + MapChunk::HEIGHT)));

	for (size_type x = begin.x; x < end.x; x += MapChunk::WIDTH)
		for (size_type y = begin.y; y < end.y; y += MapChunk::HEIGHT)
			if (has_chunk(x, y))
				fw->get_window().draw(get_chunk_at(x, y));
}

data_type	World::as_data() const
{
	data_type	data(_chunks_width * _chunks_height);

	for (uint32_t i = 0, end = _chunks.size(); i < end; i++)
		data[i] = _chunks[i].as_data();
	return data;
}

size_type	World::get_width() const
	{ return _width; }

size_type	World::get_height() const
	{ return _height; }

size_type	World::get_chunk_width() const
	{ return _chunks_width; }

size_type	World::get_chunk_height() const
	{ return _chunks_height; }
