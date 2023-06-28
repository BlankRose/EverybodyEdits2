/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - saving.cpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, June 28, 2023 7:47 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

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

	World *&map = ctx->map;
	ofile << map->raw_data() << std::endl;
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
	Logging::info("Loading data save...");

		/** ---------------------- **/
		/*        FETCH DATA        */
		/** ---------------------- **/

	ctx->map = new World(ifile);
	ifile.close();

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
	Logging::info("Generating new world... Size: " + std::to_string(Configs::misc::test_width) + "x" + std::to_string(Configs::misc::test_height) + "!");
	ctx->map = new World(Configs::misc::test_width, Configs::misc::test_height);
	if (!ctx->map)
	{
		Logging::fatal("Couldn't generate a new World!");
		return false;
	}
	Logging::info("Generated new world!");
	return true;
}
