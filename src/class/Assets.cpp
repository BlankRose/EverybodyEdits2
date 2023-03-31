/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Assets.cpp                  */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Mar 31 17:31:30 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/Assets.hpp"

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using size_type = Assets::size_type;
using vector_type = Assets::vector_type;
using rect_type = Assets::rect_type;
using texture_type = Assets::texture_type;

vector_type		_tilesize(Assets::TILE_SIZE, Assets::TILE_SIZE);
vector_type		_mapsize(0, 0);
texture_type	_tilemap;

	/** ---------------------- **/
	/*          LOADERS         */
	/** ---------------------- **/

bool			Assets::load_tilemap(const std::string &path)
{
	if (!_tilemap.loadFromFile(path))
		return false;

	_mapsize = _tilemap.getSize();
	_mapsize.x /= _tilesize.x;
	_mapsize.y /= _tilesize.y;
	return true;
}

texture_type	&Assets::get_tilemap()
	{ return _tilemap; }

vector_type		Assets::get_size()
	{ return _mapsize; }

rect_type		Assets::get_tile_coords(const size_type &x, const size_type &y)
{
	return rect_type(
		vector_type(x * _tilesize.x, y * _tilesize.y),
		vector_type((x + 1) * _tilesize.x, (y + 1) * _tilesize.y)
	);
}
