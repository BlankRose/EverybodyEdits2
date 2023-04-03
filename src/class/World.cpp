/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - World.cpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Mon Apr  3 18:52:19 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/World.hpp"
#include "class/Framework.hpp"

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using size_type = World::size_type;
using chunks_type = World::chunks_type;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

World::World(const size_type &width, const size_type &height):
	_width(width), _height(height),
	_chunks_width((width / MapChunk::WIDTH) + (width % MapChunk::WIDTH ? 1 : 0)),
	_chunks_height((height / MapChunk::HEIGHT) + (height % MapChunk::HEIGHT ? 1 : 0)),
	_chunks(_chunks_width * _chunks_height)
{
	for (size_type x = 0; x < _chunks_width; x++)
		for (size_type y = 0; y < _chunks_height; y++)
			_chunks[y * _chunks_width + x] = MapChunk(x * MapChunk::WIDTH, y * MapChunk::HEIGHT);
}

World::~World()
	{ _chunks.clear(); }

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

bool		World::has_chunk(const sf::Vector2u &pos) const
{
	return pos.x >= 0 && pos.x / MapChunk::WIDTH < _chunks_width
		&& pos.y >= 0 && pos.y / MapChunk::HEIGHT < _chunks_height;
}

bool		World::has_chunk(const size_type &x, const size_type &y) const
{
	return x >= 0 && x / MapChunk::WIDTH < _chunks_width
		&& y >= 0 && y / MapChunk::HEIGHT < _chunks_height;
}

MapChunk	&World::get_chunk_at(const sf::Vector2u &pos)
	{ return _chunks[(pos.x / MapChunk::WIDTH) * _chunks_width + pos.y / MapChunk::HEIGHT]; }

MapChunk	&World::get_chunk_at(const size_type &x, const size_type &y)
	{ return _chunks[(x / MapChunk::WIDTH) * _chunks_width + y / MapChunk::HEIGHT]; }

void		World::render(Framework *&fw)
{
	size_type		tile_size = MapChunk::get_tilesize();
	sf::Vector2f	center = fw->get_view().getCenter();
	sf::Vector2f	size = fw->get_view().getSize();

	sf::FloatRect	view_bounds(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);
	for (chunks_type::iterator it = _chunks.begin(), end = _chunks.end(); it != end; it++)
	{
		sf::Vector2u	pos = it->get_position();
		sf::FloatRect	chunk_bounds(pos.x, pos.y, MapChunk::WIDTH * tile_size, MapChunk::HEIGHT * tile_size);
		if (view_bounds.intersects(chunk_bounds))
			fw->get_window().draw(*it);
	}

	// float			sx = (center.x - size.x / 2) / tile_size;
	// float			sy = (center.y - size.y / 2) / tile_size;
	// float			ex = (center.x + size.x / 2) / tile_size;
	// float			ey = (center.y + size.y / 2) / tile_size;

	// std::set<std::pair<uint32_t, uint32_t>>	rendered;
	// for (int64_t x = sx - 10; x < ex + 10; x++)
	// 	for (int64_t y = sy - 10; y < ey + 10; y++)
	// 	{
	// 		sf::FloatRect chunk_bounds(
	// 			x * MapChunk::WIDTH * tile_size, y * MapChunk::HEIGHT * tile_size,
	// 			MapChunk::WIDTH * tile_size, MapChunk::HEIGHT * tile_size);
	// 		if (chunk_bounds.intersects(view_bounds) && has_chunk(x, y))
	// 		{
	// 			MapChunk		&chunk = get_chunk_at(x, y);
	// 			sf::Vector2u	pos = chunk.get_position();
	// 			if (!rendered.count({pos.x, pos.y}))
	// 			{
	// 				rendered.insert({pos.x, pos.y});
	// 				fw->get_window().draw(chunk);
	// 			}
	// 		}
	// 	}
}

size_type	World::get_width() const
	{ return _width; }

size_type	World::get_height() const
	{ return _height; }

size_type	World::get_chunk_width() const
	{ return _chunks_width; }

size_type	World::get_chunk_height() const
	{ return _chunks_height; }
