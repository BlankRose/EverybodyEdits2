/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - saving.cpp                  */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Apr  7 16:23:12 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

#include <fstream>
#include <cstring>

/**
 * Saves the data of the world into a file
 * 
 * @param	ctx: Context of the World
 * @param	path: Path to the target file
 * 
 * @return	True or False upon Success or Failure
 * */
bool	save_world(Context *&ctx, const std::string &path)
{
		/** ---------------------- **/
		/*       VERIFICATION       */
		/** ---------------------- **/

	if (!ctx->map)
		return (Logging::error("Tried to save the world but the provided world is not defined!"), false);
	if (path.empty() || path.find_first_not_of("\t\n\v\f\r ") == path.npos)
		return (Logging::error("Tried to save the world but the provided path is empty!"), false);

	std::ofstream	ofile(path, std::ios::binary);
	if (!ofile.is_open())
		return (Logging::error("Cannot open the target file: " + path + "!"), false);

		/** ---------------------- **/
		/*        WORLD DATA        */
		/** ---------------------- **/

	World	*&map = ctx->map;
	ofile << char(VERSION_SAVES) << map->get_width() << SAVES_SEP << map->get_height() << std::endl;

	World::data_type	data = map->as_data(SAVES_SEP);
	for (World::data_type::iterator it = data.begin(), end = data.end(); it != end; it++)
		ofile << *it << std::endl;
	return true;
}

/**
 * Loads from a file, the data of a world
 * 
 * @param	ctx: Context of the World
 * @param	path: Path to the target file
 * 
 * @return	True or False upon Success or Failure
 * */
bool	load_world(Context *&ctx, const std::string &path)
{
		/** ---------------------- **/
		/*       VERIFICATION       */
		/** ---------------------- **/

	if (path.empty() || path.find_first_not_of("\t\n\v\f\r ") == path.npos)
		return (Logging::error("Tried to load the world but the provided path is empty!"), false);

	std::ifstream	ifile(path, std::ios::binary);
	if (!ifile.is_open())
		return (Logging::error("Cannot open the target file: " + path + "!"), false);

		/** ---------------------- **/
		/*        BASIC DATA        */
		/** ---------------------- **/

	std::string		str;
	std::getline(ifile, str);

	uint32_t		ver = str[0];
	sf::Vector2u	size(
		std::atoi(str.substr(1, str.find_first_of(SAVES_SEP)).c_str()),
		std::atoi(str.substr(str.find_first_of(SAVES_SEP) + 1).c_str()));

	if (ver < VERSION_SAVES)
		Logging::warn("The target save file is from an older version of the game!");
	Logging::info("Loading data save...");

		/** ---------------------- **/
		/*        FETCH DATA        */
		/** ---------------------- **/

	uint32_t			i = 0;
	World::data_type	arr(size.x / MapChunk::WIDTH * size.y / MapChunk::HEIGHT);
	while (std::getline(ifile, str))
	{
		if (str.empty())
			break;
		if (i >= arr.size())
		{
			Logging::warn("The content of the data is larger than expected! The additional data will be ignored..");
			break;
		}
		arr[i++] = str;
	}
	if (i < arr.size())
		return (Logging::error(
			std::string("The target save file has incomplete world saved (Expected: ") +
			std::to_string(arr.size()) + " but got " + std::to_string(i) + ")!"), false);

		/** ---------------------- **/
		/*        APPLY DATA        */
		/** ---------------------- **/

	ctx->map = new World(size.x, size.y, arr, SAVES_SEP);
	if (!ctx->map)
		return (Logging::fatal("Couldn't allocate the sufficient memory for the world to load in!"), false);
	Logging::info("Map loaded!");

	return true;
}

/**
 * Creates a brand new empty world, ready to go
 * 
 * @param	ctx: Context of the World
 * 
 * @return	True or False upon Success or Failure
 * */
bool	new_world(Context *&ctx)
{
	Logging::info("Generating new world...");
	ctx->map = new World(Configs::misc::test_width, Configs::misc::test_height);
	if (!ctx->map)
	{
		Logging::fatal("Couldn't generate a new World!");
		return false;
	}
	Logging::info("Generated new world!");
	return true;
}
