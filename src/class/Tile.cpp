/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Tile.cpp                           */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, June 27, 2023 10:02 PM        */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/Tile.hpp"

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using id_type = Tile::id_type;
using meta_type = Tile::meta_type;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Tile::Tile():
	_id(0), _collision(false), _meta(nullptr) {}

Tile::Tile(const id_type &id, const bool &collision, const meta_type &meta):
	_id(id), _collision(collision), _meta(meta) {}

Tile::Tile(const Tile &tile):
	_id(tile._id), _collision(tile._collision), _meta(tile._meta) {}

Tile::Tile(Tile &&tile):
	_id(std::move(tile._id)), _collision(std::move(tile._collision)), _meta(std::move(tile._meta)) {}

Tile::~Tile() {}

	/** ---------------------- **/
	/*         OVERLOADS        */
	/** ---------------------- **/

Tile			&Tile::operator=(const Tile &tile)
{
	_id = tile._id;
	_collision = tile._collision;
	_meta = tile._meta;
	return *this;
}

Tile			&Tile::operator=(Tile &&tile)
{
	_id = std::move(tile._id);
	_collision = std::move(tile._collision);
	_meta = std::move(tile._meta);
	return *this;
}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

id_type			Tile::get_id() const { return _id; }
bool			Tile::get_collision() const { return _collision; }
meta_type		Tile::get_meta() const { return _meta; }

void			Tile::set_id(const id_type &id) { _id = id; }
void			Tile::set_collision(const bool &collision) { _collision = collision; }
void			Tile::set_meta(const meta_type &meta) { _meta = meta; }

std::string		Tile::rawData() const
	{ return std::string((char *) &_id, sizeof(_id)); }
