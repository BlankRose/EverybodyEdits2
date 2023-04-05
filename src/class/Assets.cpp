/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Assets.cpp                  */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Wed Apr  5 20:44:23 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/Configs.hpp"
#include "class/Assets.hpp"

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using path_type = Assets::path_type;

using group_type = Assets::group_type;
using id_region = Assets::id_region;
using texture_type = Assets::texture_type;

using size_type = Assets::size_type;
using vector_type = Assets::vector_type;
using rect_type = Assets::rect_type;
using texture_map = Assets::texture_map;

vector_type		_tilesize(Configs::graphics::tilesize, Configs::graphics::tilesize);
vector_type		_mapsize(0, 0);
texture_type	_tilemap;

texture_map		_fg_regions = {
	// OOB-Colors - Empty - Invalid - Cursor
	{ "special", { 0, 4 } },

	// Regular Tile Packs (line, length)
	{ "basic", { 1, 10 } },
	{ "bricks", { 2, 10 } },
	{ "beta", { 3, 10 } },
	{ "static", { 4, 10 } }
};

texture_map		_bg_regions = {
	{ "special", { 0, 1 } }
};

	/** ---------------------- **/
	/*          LOADERS         */
	/** ---------------------- **/

bool			Assets::load_tilemap(const path_type &path)
{
	if (!_tilemap.loadFromFile(path))
		return false;

	_mapsize = _tilemap.getSize();
	_mapsize.x /= _tilesize.x;
	_mapsize.y /= _tilesize.y;
	return true;
}

void			Assets::set_size(const vector_type &size)
	{ _tilesize = size; }

void			Assets::set_size(const size_type &x, const size_type &y)
	{ _tilesize = vector_type(x, y); }

texture_type	&Assets::get_tilemap()
	{ return _tilemap; }

vector_type		Assets::get_size()
	{ return _mapsize; }

rect_type		Assets::get_tile_coords(const group_type &group, const id_type &id)
{
	rect_type	invalid(
		vector_type(2 * _tilesize.x, 0),
		vector_type(3 * _tilesize.x, 0));

	if (_fg_regions.find(group) == _fg_regions.end())
		return invalid;
	id_region	ids = _fg_regions.at(group);
	if (id >= ids.second)
		return invalid;
	return get_tile_coords(id, ids.first);
}

rect_type		Assets::get_tile_coords(const size_type &x, const size_type &y)
{
	return rect_type(
		vector_type(x * _tilesize.x, y * _tilesize.y),
		vector_type((x + 1) * _tilesize.x, (y + 1) * _tilesize.y)
	);
}
