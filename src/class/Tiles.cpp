/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Tiles.cpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Wed Apr  5 18:09:03 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/Tiles.hpp"

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using id_type = Tile::id_type;
using group_type = Tile::group_type;

using vertex_type = Tile::vertex_type;
using coord_type = Tile::coord_type;
using position_type = Tile::position_type;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Tile::Tile():
	_vertex(nullptr), _coords(0, 0), _group("special"), _id(0), _collision(true) {}

Tile::Tile(const position_type &pos, vertex_type *&vertex, const id_type &id, const group_type &group):
	_vertex(vertex), _coords(pos), _collision(true) { set_id(id, group); }

Tile::Tile(const Tile &other):
	_vertex(other._vertex) { operator=(other); }

Tile::~Tile() {}

	/** ---------------------- **/
	/*        OVERLOADS         */
	/** ---------------------- **/

Tile				&Tile::operator=(const Tile &other)
{
	_vertex = other._vertex;
	_coords = other._coords;
	_collision = other._collision;
	set_id(other._id, other._group);

	return *this;
}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

vertex_type *		Tile::get_vertex() const
	{ return _vertex; }

position_type		Tile::get_position() const
	{ return _coords; }

group_type			Tile::get_group() const
	{ return _group; }

id_type				Tile::get_id() const
	{ return _id; }

void				Tile::set_position(const position_type &pos)
	{ _coords = pos; }

void				Tile::set_id(const id_type &id, const group_type &group)
{
	if (!_vertex)
		return;

	_id = id;
	_group = group;

	Assets::rect_type	coords = Assets::get_tile_coords(group, id);
	_vertex[0].texCoords = sf::Vector2f(coords.x.x, coords.x.y);
	_vertex[1].texCoords = sf::Vector2f(coords.y.x, coords.x.y);
	_vertex[2].texCoords = sf::Vector2f(coords.y.x, coords.y.y);
	_vertex[3].texCoords = sf::Vector2f(coords.x.x, coords.y.y);
}
