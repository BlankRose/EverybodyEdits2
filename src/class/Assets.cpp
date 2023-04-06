/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Assets.cpp                  */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Apr  6 21:09:14 CEST 2023     */
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
using font_type = Assets::font_type;

vector_type		_tilesize(Configs::graphics::tilesize, Configs::graphics::tilesize);

vector_type		_fg_mapsize(0, 0);
texture_type	_fg_tilemap;
texture_map		_fg_regions = {
	// OOB-Colors - Empty - Invalid - Cursor
	{ "special", { 0, 4 } },

	// Regular Tile Packs (line, length)
	{ "basic", { 1, 10 } },
	{ "bricks", { 2, 10 } },
	{ "beta", { 3, 10 } },
	{ "static", { 4, 10 } }
};

vector_type		_bg_mapsize(0, 0);
texture_type	_bg_tilemap;
texture_map		_bg_regions = {
	// OOB-Colors - Empty - Invalid - Cursor
	{ "special", { 0, 1 } },

	// Regular Tile Packs (line, length)
	{ "basic", { 1, 10 } },
	{ "bricks", { 2, 10 } },
	{ "beta", { 3, 10 } },
	{ "static", { 4, 10 } }
};

font_type		_font;
texture_type	_loadscreen;

	/** ---------------------- **/
	/*          LOADERS         */
	/** ---------------------- **/

bool			Assets::load_ressources(const path_type &base_dir)
{
	path_type	dir = base_dir;
	if (*base_dir.rbegin() != '/')
		dir += '/';

	if (!_bg_tilemap.loadFromFile(dir + "background.png")
		|| !_fg_tilemap.loadFromFile(dir + "foreground.png")
		|| !_loadscreen.loadFromFile(dir + "loadscreen.png")
		|| !_font.loadFromFile(dir + "font.ttf"))
		return false;

	_fg_mapsize = _fg_tilemap.getSize();
	_fg_mapsize.x /= _tilesize.x;
	_fg_mapsize.y /= _tilesize.y;

	_bg_mapsize = _bg_tilemap.getSize();
	_bg_mapsize.x /= _tilesize.x;
	_bg_mapsize.y /= _tilesize.y;
	return true;
}

void			Assets::set_size(const vector_type &size)
	{ _tilesize = size; }

void			Assets::set_size(const size_type &x, const size_type &y)
	{ _tilesize = vector_type(x, y); }

font_type		&Assets::get_font()
	{ return _font; }

texture_type	&Assets::get_loadscreen()
	{ return _loadscreen; }

texture_type	&Assets::get_tilemap(const bool &bg)
{
	if (bg) return _bg_tilemap;
	return _fg_tilemap;
}

vector_type		Assets::get_size(const bool &bg)
{
	if (bg) return _bg_mapsize;
	return _fg_mapsize;
}

rect_type		Assets::get_tile_coords(const group_type &group, const id_type &id, const bool &bg)
{
	rect_type	invalid(
		vector_type(2 * _tilesize.x, 0),
		vector_type(3 * _tilesize.x, 0));

	texture_map		target = bg ? _bg_regions : _fg_regions;
	if (target.find(group) == target.end())
		return invalid;
	id_region	ids = target.at(group);
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
