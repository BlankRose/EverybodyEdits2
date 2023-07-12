/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Tile.cpp                           */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, July 12, 2023 10:59 PM      */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/Tile.hpp"
#include <utility>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using id_type = Tile::id_type;
using raw_type = Tile::raw_type;
using size_type = Tile::size_type;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

// Create a tile with given id
Tile::Tile(const id_type &id):
	_raw(id << 20) {}

// Create a tile from raw data
Tile::Tile(const char *data):
	_raw(*reinterpret_cast<const raw_type *>(data)) {}

// Create a copy of the target tile
Tile::Tile(const Tile &tile)
	{ operator=(tile); }

// Move the target tile into a new tile
Tile::Tile(Tile &&tile)
	{ operator=(std::move(tile)); }

// Destroy the tile
Tile::~Tile() {}

	/** ---------------------- **/
	/*         OVERLOADS        */
	/** ---------------------- **/

// Copy the target tile
Tile			&Tile::operator=(const Tile &tile)
{
	_raw = tile._raw;
	return *this;
}

// Move the target tile
Tile			&Tile::operator=(Tile &&tile)
{
	_raw = std::move(tile._raw);
	return *this;
}

// Compare the target tile with another tile
bool			Tile::operator==(const Tile &tile) const
	{ return _raw == tile._raw; }

// Compare the target tile with another tile (not equal)
bool			Tile::operator!=(const Tile &tile) const
	{ return _raw != tile._raw; }

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

// Returns the tile id, without metadata
// (located in the last 12 bits of the raw data)
id_type			Tile::get_id() const
	{ return _raw >> 20; }

// Define the tile id, without modifying the metadata
// (located in the last 12 bits of the raw data)
void			Tile::set_id(const id_type &id)
	{ _raw += (id >> 20); }

// Returns the metadata, without tile id
// (located in the first 20 bits of the raw data)
raw_type		Tile::get_meta() const
	{ return _raw & ((1 << 20) - 1); }

// Define the metadata, without modifying the tile id
// (located in the first 20 bits of the raw data)
void			Tile::set_meta(const raw_type &meta)
	{ _raw = (_raw & ~((1 << 20) - 1)) + meta; }

// Returns the whole raw data
raw_type		Tile::get_raw() const
	{ return _raw; }

// Define the whole raw data
void			Tile::set_raw(const raw_type &raw)
	{ _raw = raw; }
