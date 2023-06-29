/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - World.cpp                          */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Thursday, June 29, 2023 12:23 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/World.hpp"
#include <fstream>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using size_type = World::size_type;
using position_type = World::position_type;

#define TILES_PER_BUFFER 100000
#define TILES_BASE_SIZE sizeof(Tile::raw_type) * 2
#define BUFFER_SIZE TILES_BASE_SIZE * TILES_PER_BUFFER

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

World::World(): World(0, 0) {}

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
		_fg_tiles[x] = Tile(1);
		_fg_tiles[x + limit_y * width] = Tile(1);
	}

	// Set left and right columns (corner tiles already set)
	for (size_type y = 1; y < limit_y; ++y)
	{
		_fg_tiles[y * width] = Tile(1);
		_fg_tiles[limit_x + y * width] = Tile(1);
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
	Tile::size_type	raw_size = Tile::raw_size;

	// Assign tiles from data
	data = &data[sizeof(size_type) * 2]; // Skip size data
	for (; fg != _fg_tiles.end(); ++fg, ++bg)
	{
		*fg = Tile(data);
		*bg = Tile(&data[raw_size]);
		data += raw_size * 2;
	}
}

// Generates new world from a file
// Data are stored in binary format, with the first 4 bytes being the world's size
World::World(std::ifstream &file)
{
	// Prepare buffer (10000 tiles at once)
	uint32_t buffer_size = BUFFER_SIZE;
	char buffer[BUFFER_SIZE + 1];

	// Retrieve basic details
	file.read(buffer, sizeof(size_type) * 2);
	_size = position_type(*reinterpret_cast<size_type *>(buffer),
		*reinterpret_cast<size_type *>(&buffer[sizeof(size_type)]));
	_fg_tiles.resize(_size.x * _size.y);
	_bg_tiles.resize(_size.x * _size.y);

	// Prepare iterators
	tiles_array::iterator fg = _fg_tiles.begin();
	tiles_array::iterator bg = _bg_tiles.begin();
	Tile::size_type	raw_size = Tile::raw_size;

	while (true)
	{
		// Multiple tile reads at once
		file.read(buffer, buffer_size);
		if (file.gcount() == 0
			|| fg == _fg_tiles.end())
			break;

		// Assign tiles from buffer
		for (size_type i = 0;
			i < buffer_size && fg != _fg_tiles.end();
			i += raw_size * 2, ++fg, ++bg)
		{
			*fg = Tile(&buffer[i]);
			*bg = Tile(&buffer[i + raw_size]);
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

size_type		World::get_width() const { return _size.x; }
size_type		World::get_height() const { return _size.y; }

Tile			&World::get_fg_tile(const size_type &x, const size_type &y)
	{ return _fg_tiles[x + y * _size.x]; }

Tile			&World::get_bg_tile(const size_type &x, const size_type &y)
	{ return _bg_tiles[x + y * _size.x]; }

const Tile		&World::get_fg_tile(const size_type &x, const size_type &y) const
	{ return _fg_tiles[x + y * _size.x]; }

const Tile		&World::get_bg_tile(const size_type &x, const size_type &y) const
	{ return _bg_tiles[x + y * _size.x]; }

void			World::set_width(const size_type &width)
{
	_size.x = width;
	_fg_tiles.resize(width * _size.y);
	_bg_tiles.resize(width * _size.y);
}

void			World::set_height(const size_type &height)
{
	_size.y = height;
	_fg_tiles.resize(_size.x * height);
	_bg_tiles.resize(_size.x * height);
}

void			World::set_fg_tile(const size_type &x, const size_type &y, const Tile &tile)
	{ _fg_tiles[x + y * _size.x] = tile; }

void			World::set_bg_tile(const size_type &x, const size_type &y, const Tile &tile)
	{ _bg_tiles[x + y * _size.x] = tile; }

// Retrieves world's data in binary format, with the given format:
std::string		World::raw_data() const
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
		uint32_t raw[2] = { fg->get_raw(), bg->get_raw() };
		data.append((char *) raw, sizeof(uint32_t) * 2);
	}

	// Return final data
	return data;
}

// Save world's data in binary format, straight to the given file
// (Time saved by not using std::string: half time compared to raw_data())
void			World::save(std::ofstream &file) const
{
	// Store world's size
	size_type size[] = { _size.x, _size.y };
	file.write(reinterpret_cast<const char *>(&size), sizeof(size));

	// Store tiles' data
	tiles_array::const_iterator fg = _fg_tiles.begin();
	tiles_array::const_iterator bg = _bg_tiles.begin();

	for (; fg != _fg_tiles.end(); ++fg, ++bg)
	{
		uint32_t raw[] = { fg->get_raw(), bg->get_raw() };
		file.write((char *) raw, sizeof(raw));
	}
}