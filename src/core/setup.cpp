/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - setup.cpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Mon Apr  3 15:40:23 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * Free the memory of the given Framework and Map
 * and sets then to NULLPTR accordingly
 * 
 * @param	fw: Framework to clear
 * @param	map: Map to clear
 * */
void		unload(Framework *&fw, World *&map)
{
	if (fw)
		delete fw;
	if (map)
		delete map;

	fw = nullptr;
	map = nullptr;
}

/**
 * Configures the software accordingly to the
 * given configuration files
 * 
 * @param	path: Path to the configuration file
 * */
bool		configure(const std::string &path)
{
	/** ---------------------- **/
	/*  SETTING CONFIGURATIONS  */
	/** ---------------------- **/

	if (!Configs::load_configs(path)
		&& !Configs::load_default())
	{
		std::cout << "Failed to configure!" << std::endl;
		return false;
	}

	/** ---------------------- **/
	/*      PREPARING LOGS      */
	/** ---------------------- **/

	Logging::init(Configs::misc::log_file, Configs::misc::log_level);
	Logging::debug("Logging module init!");
	Logging::info("Software started!");

	return true;
}

/**
 * Allocate and prepare the memory and store it within
 * the given pointers passed into arguments and prepares
 * the logging module aswell
 * 
 * @param	fw: Framework pointer to store into
 * @param	map: Map pointer to store into
 * 
 * @return	True or False if it was successful or not
 * */
bool		get_ready(Framework *&fw, World *&map)
{
	/** ---------------------- **/
	/*     ALLOCATING MEMORY    */
	/** ---------------------- **/

	Logging::debug("Preparing the memory...");

	fw = new Framework();
	map = new World(10, 10);

	if (!fw || !fw->is_ready() || !map)
	{
		unload(fw, map);
		Logging::fatal("Couldn't allocate the requiered memory!");
		return false;
	}
	Logging::debug("Successfully allocated the requiered memory!");

	/** ---------------------- **/
	/*      LOADING ASSETS      */
	/** ---------------------- **/

	Logging::debug("Loading the assets...");
	if (!Assets::load_tilemap("configs/tileset.png"))
	{
		unload(fw, map);
		Logging::fatal("Couldn't load the needed assets!");
		return false;
	}
	Logging::debug("Successfully loaded the needed assets!");
	return true;
}
