/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Assets.cpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, July 12, 2023 10:27 PM      */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "base/Configs.hpp"
#include "base/Assets.hpp"

#include <map>
#include <vector>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using path_type = Assets::path_type;
using id_type = Assets::id_type;
using size_type = Assets::size_type;
using texture_type = Assets::texture_type;
using font_type = Assets::font_type;

using AssetsPack = Assets::AssetsPack;

typedef std::map<id_type, sf::Texture>	texture_map;
typedef std::vector<AssetsPack>	packs_type;

size_type		_tilesize;
texture_map		_fg_texmap;
texture_map		_bg_texmap;

font_type		_font;
texture_type	_loadscreen;
texture_type	_player;

	/** ---------------------- **/
	/*     PACKS DEFINTIONS     */
	/** ---------------------- **/

packs_type fg_packs = {
	AssetsPack(0, 2, "special/"),
	AssetsPack(10, 10, "basic/"),
	AssetsPack(20, 10, "bricks/"),
	AssetsPack(30, 10, "beta/"),
	AssetsPack(40, 10, "static/"),
};

packs_type bg_packs = {
	AssetsPack(0, 1, "special/"),
	AssetsPack(10, 10, "basic/"),
	AssetsPack(20, 10, "bricks/"),
	AssetsPack(30, 10, "beta/"),
	AssetsPack(50, 10, "static/"),
};

	/** ---------------------- **/
	/*          LOADERS         */
	/** ---------------------- **/

static bool _load_pack(const path_type &dir, const AssetsPack &pack, texture_map &map)
{
	texture_type texture;
	for (id_type i = pack.begin; i < pack.begin + pack.range; ++i)
	{
		if (!texture.loadFromFile(dir + pack.path + std::to_string(i - pack.begin) + ".png"))
			return false;
		map.insert(std::make_pair(i, texture));
	}
	return true;
}

bool Assets::load_ressources(const path_type &base_dir)
{
	// Defines the directory path and tile size
	path_type	dir = base_dir;
	if (*base_dir.rbegin() != '/')
		dir += '/';
	_tilesize = size_type(
		Configs::graphics::tilesize,
		Configs::graphics::tilesize
	);

	// Load all tile textures
	for (auto &pack : fg_packs)
		if (!_load_pack(dir + "foreground/", pack, _fg_texmap))
			return false;
	for (auto &pack : bg_packs)
		if (!_load_pack(dir + "background/", pack, _bg_texmap))
			return false;

	// Load additional "unknown" tile textures
	// (Will be used when a tile is not found in the map)
	texture_type texture;
	if (!texture.loadFromFile(dir + "foreground/unknown.png"))
		return false;
	_fg_texmap.insert(std::make_pair(-1, texture));
	if (!texture.loadFromFile(dir + "background/unknown.png"))
		return false;
	_bg_texmap.insert(std::make_pair(-1, texture));

	// Load player texture and font
	if (!_player.loadFromFile(dir + "player.png"))
		return false;
	if (!_font.loadFromFile(dir + "font.ttf"))
		return false;
	return true;
}

void Assets::set_size(const size_type &size)
	{ _tilesize = size; }

void Assets::set_size(const unsigned int &x, const unsigned int &y)
	{ _tilesize = size_type(x, y); }

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

font_type &Assets::get_font()
	{ return _font; }

texture_type &Assets::get_loadscreen()
	{ return _loadscreen; }

texture_type &Assets::get_player()
	{ return _player; }

texture_type &Assets::get_texture(const id_type &id, const bool &bg)
{
	if (bg)
	{
		if (_bg_texmap.find(id) == _bg_texmap.end())
			return _bg_texmap.at(-1);
		return _bg_texmap.at(id);
	}

	if (_fg_texmap.find(id) == _fg_texmap.end())
		return _fg_texmap.at(-1);
	return _fg_texmap.at(id);
}

size_type Assets::get_size()
	{ return _tilesize; }
