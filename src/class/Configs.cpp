/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Configs.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Sun Apr  2 21:05:04 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/Configs.hpp"

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "class/Logging.hpp"

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using json_type = Configs::json_type;
using key_type = Configs::key_type;

const std::string	DEFAULT_TARGET = "DEFAULT";
const json_type		_default =

	json_type {
		{
			"graphics",
			{
				{ "textures", "configs/tileset.png" }
			}
		},
		{
			"audio",
			{
				{ "music", 100.f },
				{ "sound", 100.f }
			}
		},
		{
			"keybinds",
			{
				{ "move_left", sf::Keyboard::Left },
				{ "move_right", sf::Keyboard::Right },
				{ "move_up", sf::Keyboard::Up },
				{ "move_down", sf::Keyboard::Down },
				{ "exit", sf::Keyboard::Escape }
			}
		},
		{
			"miscellaneous",
			{
				{ "log_file", "configs/latest.log" },
				{ "log_level", Logging::DEBUG }
			}
		}
	};

bool			_ready = false;
std::string		_from = DEFAULT_TARGET;
json_type		_loaded = _default;

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

bool			Configs::load_default()
{
	_from = DEFAULT_TARGET;
	return load_configs(_default);
}

bool			Configs::load_configs(const std::string &path)
{
	if (path == DEFAULT_TARGET)
		return load_default();
	else
	{
		std::ifstream	file(path);
		if (!file.is_open())
			return false;

		json_type		json;
		try
			{ file >> json; }
		catch (const std::exception &error)
		{
			std::cout << "There's an error in the configuration: "
				<< std::endl << error.what() << std::endl;
			return (_ready = false);
		}
		if (!load_configs(json))
			return false;
		_from = path;
		return true;
	}
}

bool			Configs::load_configs(const json_type &json)
{
	try
	{
		// GRAPHICS
		Configs::graphics::textures = json.at("graphics").at("textures");

		// AUDIO
		Configs::audio::music = json.at("audio").at("music");
		Configs::audio::sound = json.at("audio").at("sound");

		// KEY BINDING
		Configs::keybinds::move_left = json.at("keybinds").at("move_left");
		Configs::keybinds::move_right = json.at("keybinds").at("move_right");
		Configs::keybinds::move_up = json.at("keybinds").at("move_up");
		Configs::keybinds::move_down = json.at("keybinds").at("move_down");
		Configs::keybinds::exit = json.at("keybinds").at("exit");

		// MISCELLANEOUS
		Configs::misc::log_file = json.at("miscellaneous").at("log_file");
		Configs::misc::log_level = json.at("miscellaneous").at("log_level");

		return (_ready = true);
	}
	catch (const std::exception &error)
	{
		std::cout << "There's an error in the configuration: "
			<< std::endl << error.what() << std::endl;
		return (_ready = false);
	}
}

bool			Configs::save_configs(const std::string &path, const json_type &json)
{
	std::string		p = path;
	if (path == DEFAULT_TARGET)
		p = "configs/settings.json";

	std::ofstream	file(p);
	if (!file.is_open())
		return false;

	file << json.dump(4);
	return true;
}

bool			Configs::save_configs(const std::string &path)
	{ return save_configs(path, _loaded); }

bool			Configs::save_configs(const json_type &json)
	{ return save_configs(_from, json); }

bool			Configs::save_configs()
	{ return save_configs(_from, _loaded); }

bool			Configs::is_ready()
	{ return _ready; }

json_type		&Configs::get_configs()
	{ return _loaded; }

json_type		Configs::get_default()
	{ return _default; }
