/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - saving.cpp                  */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Apr  7 21:12:59 CEST 2023     */
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

	World				*&map = ctx->map;
	World::data_type	data = map->as_data();
	uint32_t			size[2] = { map->get_width(), map->get_height() };

	ofile << char(VERSION_SAVES);
	ofile.write((char *) size, 2 * sizeof(uint32_t));
	for (World::data_type::iterator it = data.begin(), end = data.end(); it != end; it++)
		ofile << std::endl << *it;
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

	uint32_t *		data = (uint32_t *) (str.c_str() + 1);
	uint32_t		ver = str[0];
	sf::Vector2u	size(data[0], data[1]);

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

	ctx->map = new World(size.x, size.y, arr);
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
