/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - setup.cpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Mar 31 21:09:52 CEST 2023     */
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
void		unload(Framework *&fw, TileMap *&map)
{
	if (fw)
		delete fw;
	if (map)
		delete map;

	fw = nullptr;
	map = nullptr;
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
bool		get_ready(Framework *&fw, TileMap *&map)
{

	/** ---------------------- **/
	/*      PREPARING LOGS      */
	/** ---------------------- **/

#ifdef LOG_DEBUG
	Logging::init("logs/current.log", Logging::DEBUG);
	Logging::debug("Logging module init!");
#else
	Logging::init("logs/current.log", Logging::INFO);
#endif
	Logging::info("Software started!");

	/** ---------------------- **/
	/*     ALLOCATING MEMORY    */
	/** ---------------------- **/

	Logging::debug("Preparing the memory...");

	fw = new Framework();
	map = new TileMap(50, 10, 10);

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
	if (!Assets::load_tilemap("tileset.png"))
	{
		unload(fw, map);
		Logging::fatal("Couldn't load the needed assets!");
		return false;
	}
	Logging::debug("Successfully loaded the needed assets!");
	return true;
}
