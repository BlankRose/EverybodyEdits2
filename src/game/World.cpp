/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - World.cpp                          */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, July 12, 2023 11:15 PM      */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/World.hpp"

#include "utils/CommonTiles.hpp"
#include "utils/Settings.hpp"

#include <fstream>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using size_type = World::size_type;
using scale_type = World::scale_type;

#define TILES_BASE_SIZE sizeof(Tile::raw_type) * 2
#define BUFFER_SIZE TILES_BASE_SIZE * TILES_PER_BUFFER

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

// Generates new world with given width and height
World::World(const size_type &width, const size_type &height):
	_size(width, height), _fg_tiles(width * height), _bg_tiles(width * height)
{
	// Pre-calculate boundaries
	size_type limit_x = width - 1;
	size_type limit_y = height - 1;

	// Set top and bottom rows
	for (size_type x = 0; x < width; ++x)
	{
		_fg_tiles[x] = Tile(_TILEID_DEFAULT);
		_fg_tiles[x + limit_y * width] = Tile(_TILEID_DEFAULT);
	}

	// Set left and right columns (corner tiles already set)
	for (size_type y = 1; y < limit_y; ++y)
	{
		_fg_tiles[y * width] = Tile(_TILEID_DEFAULT);
		_fg_tiles[limit_x + y * width] = Tile(_TILEID_DEFAULT);
	}
}

// Generates new world from given data
// Data are stored in binary format, with the first 4 bytes being the world's size
World::World(const char *data):
	_size(*reinterpret_cast<const size_type *>(data),
		*reinterpret_cast<const size_type *>(data + sizeof(size_type))),
	_fg_tiles(_size.x * _size.y), _bg_tiles(_size.x * _size.y)
{
	// Prepare iterators
	tiles_array::iterator fg = _fg_tiles.begin();
	tiles_array::iterator bg = _bg_tiles.begin();

	// Assign tiles from data
	data = &data[sizeof(size_type) * 2]; // Skip size data
	for (; fg != _fg_tiles.end(); ++fg, ++bg)
	{
		*fg = Tile(data);
		*bg = Tile(&data[sizeof(Tile::raw_type)]);
		data += sizeof(Tile::raw_type) * 2;

		if (fg->get_id() == _TILEID_SPAWN)
		{
			size_type pos = fg - _fg_tiles.begin();
			_spawns.push_back(scale_type(pos % _size.x, pos / _size.x));
		}
	}
}

// Generates new world from a file
// Data are stored in binary format, with the first 4 bytes being the world's size
World::World(std::ifstream &file)
{
	// Prepare buffer
	char buffer[BUFFER_SIZE + 1];

	// Retrieve basic details
	file.read(buffer, sizeof(size_type) * 2);
	_size = scale_type(*reinterpret_cast<size_type *>(buffer),
		*reinterpret_cast<size_type *>(&buffer[sizeof(size_type)]));
	_fg_tiles.resize(_size.x * _size.y);
	_bg_tiles.resize(_size.x * _size.y);

	// Prepare iterators
	tiles_array::iterator fg = _fg_tiles.begin();
	tiles_array::iterator bg = _bg_tiles.begin();

	while (true)
	{
		// Multiple tile reads at once
		file.read(buffer, BUFFER_SIZE);
		if (file.gcount() == 0
			|| fg == _fg_tiles.end())
			break;

		// Assign tiles from buffer
		for (uint32_t i = 0;
			i < BUFFER_SIZE && fg != _fg_tiles.end();
			i += sizeof(Tile::raw_type) * 2, ++fg, ++bg)
		{
			*fg = Tile(&buffer[i]);
			*bg = Tile(&buffer[i + sizeof(Tile::raw_type)]);

			if (fg->get_id() == _TILEID_SPAWN)
			{
				size_type pos = fg - _fg_tiles.begin();
				_spawns.push_back(scale_type(pos % _size.x, pos / _size.x));
			}
		}
	}
}

// Destroys the world
World::~World()
{
	_fg_tiles.clear();
	_bg_tiles.clear();
}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

scale_type	World::get_size() const
	{ return _size; }

size_type	World::get_width() const
	{ return _size.x; }

size_type	World::get_height() const
	{ return _size.y; }

Tile		&World::get_fg_tile(const size_type &x, const size_type &y)
	{ return _fg_tiles[x + y * _size.x]; }

Tile		&World::get_bg_tile(const size_type &x, const size_type &y)
	{ return _bg_tiles[x + y * _size.x]; }

const Tile	&World::get_fg_tile(const size_type &x, const size_type &y) const
	{ return _fg_tiles[x + y * _size.x]; }

const Tile	&World::get_bg_tile(const size_type &x, const size_type &y) const
	{ return _bg_tiles[x + y * _size.x]; }

void		World::set_fg_tile(const size_type &x, const size_type &y, const Tile &tile)
	{ _fg_tiles[x + y * _size.x] = tile; }

void		World::set_bg_tile(const size_type &x, const size_type &y, const Tile &tile)
	{ _bg_tiles[x + y * _size.x] = tile; }

void		World::set_fg_tile(const size_type &x, const size_type &y, Tile &&tile)
	{ _fg_tiles[x + y * _size.x] = std::move(tile); }

void		World::set_bg_tile(const size_type &x, const size_type &y, Tile &&tile)
	{ _bg_tiles[x + y * _size.x] = std::move(tile); }

/**
 * Indicates whether the world has a tile at the given position
 * (Mostly used for detecting out-of-bounds positions)
 * 
 * @param	x: The tile's x position
 * @param	y: The tile's y position
 * 
 * @return	True if the world has a tile at the given position, false otherwise
 * */
bool World::has_tile(const int32_t &x, const int32_t &y) const
{
	return x >= 0 && x < _size.x
		&& y >= 0 && y < _size.y;
}

// Adds a new spawn point to the world
void	World::add_spawn(const scale_type &pos)
	{ _spawns.push_back(pos); }

// Deletes a spawn point from the world
void	World::remove_spawn(const scale_type &pos)
{
	// Find spawn point
	std::vector<scale_type>::iterator it = std::find(_spawns.begin(), _spawns.end(), pos);
	if (it != _spawns.end())
		_spawns.erase(it);
}

// Retrieves the spawn point. If multiple are present, a random one is returned,
// or if none are present, the default spawn point (at 1;1) is returned
scale_type	World::get_spawn() const
{
	if (_spawns.size() == 0)
		return scale_type(1, 1);
	return _spawns[rand() % _spawns.size()];
}

// Retrieves world's data in binary format, as a string
std::string	World::raw_data() const
{
	// Store world's size
	std::string data;
	data += std::string(reinterpret_cast<const char *>(&_size.x), sizeof(size_type))
	      + std::string(reinterpret_cast<const char *>(&_size.y), sizeof(size_type));

	// Store tiles' data
	tiles_array::const_iterator fg = _fg_tiles.begin();
	tiles_array::const_iterator bg = _bg_tiles.begin();
	for (; fg != _fg_tiles.end(); ++fg, ++bg)
	{
		Tile::raw_type raw[2] = { fg->get_raw(), bg->get_raw() };
		data.append((char *) raw, sizeof(raw));
	}

	// Return final data
	return data;
}

// Save world's data in binary format, straight to the given file
// (Time saved by not using std::string: almost half time compared to raw_data())
void		World::save(std::ofstream &file) const
{
	// Store world's size
	size_type size[] = { _size.x, _size.y };
	file.write(reinterpret_cast<const char *>(&size), sizeof(size));

	// Store tiles' data
	tiles_array::const_iterator fg = _fg_tiles.begin();
	tiles_array::const_iterator bg = _bg_tiles.begin();

	for (; fg != _fg_tiles.end(); ++fg, ++bg)
	{
		Tile::raw_type raw[] = { fg->get_raw(), bg->get_raw() };
		file.write((char *) raw, sizeof(raw));
	}
}
