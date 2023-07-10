/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Assets.cpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 10, 2023 8:42 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "base/Configs.hpp"
#include "base/Assets.hpp"

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using path_type = Assets::path_type;
using id_type = Assets::id_type;
using size_type = Assets::size_type;
using texture_type = Assets::texture_type;
using texture_map = Assets::texture_map;
using font_type = Assets::font_type;

size_type		_tilesize;
texture_map		_fg_texmap;
texture_map		_bg_texmap;

font_type		_font;
texture_type	_loadscreen;
texture_type	_player;

const char *id_paths[] = {
	"empty",
	"basic_0", "basic_1", "basic_2", "basic_3", "basic_4", "basic_5", "basic_6", "basic_7", "basic_8", "basic_9",
	"brick_0", "brick_1", "brick_2", "brick_3", "brick_4", "brick_5", "brick_6", "brick_7", "brick_8", "brick_9",
	"beta_0", "beta_1", "beta_2", "beta_3", "beta_4", "beta_5", "beta_6", "beta_7", "beta_8", "beta_9",
	"static_0", "static_1", "static_2", "static_3", "static_4", "static_5", "static_6", "static_7", "static_8", "static_9",
	nullptr
};

	/** ---------------------- **/
	/*          LOADERS         */
	/** ---------------------- **/

bool Assets::load_ressources(const path_type &base_dir)
{
	path_type	dir = base_dir;
	if (*base_dir.rbegin() != '/')
		dir += '/';

	texture_type fg_tex, bg_tex;
	_tilesize = size_type(Configs::graphics::tilesize, Configs::graphics::tilesize);

	// Load all tile textures
	for (id_type i = 0; id_paths[i]; ++i)
	{
		if (!fg_tex.loadFromFile(dir + "foreground/" + id_paths[i] + ".png")
			|| !bg_tex.loadFromFile(dir + "background/" + id_paths[i] + ".png"))
			return false;
		_fg_texmap.insert(std::make_pair(i, fg_tex));
		_bg_texmap.insert(std::make_pair(i, bg_tex));
	}

	// Load additional "unknown" tile textures
	// (Will be used when a tile is not found in the map)
	if (!fg_tex.loadFromFile(dir + "foreground/unknown.png")
		|| !bg_tex.loadFromFile(dir + "background/unknown.png"))
		return false;
	_fg_texmap.insert(std::make_pair(-1, fg_tex));
	_bg_texmap.insert(std::make_pair(-1, bg_tex));

	// Load player texture
	if (!_player.loadFromFile(dir + "player.png"))
		return false;

	// Load font
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
