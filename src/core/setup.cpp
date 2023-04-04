/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - setup.cpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Mon Apr  3 19:03:38 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * Free the memory of the given Framework and Map
 * and sets then to NULLPTR accordingly
 * 
 * @param	ctx: Target context to free
 * */
void		unload(Context *&ctx)
{
	if (ctx)
	{
		if (ctx->fw)
			delete ctx->fw;
		if (ctx->map)
			delete ctx->map;
		if (ctx->ui)
			delete ctx->ui;
		delete ctx;
	}
	ctx = nullptr;
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
 * @param	ctx: Memory to store in the new Contex
 * 
 * @return	True or False if it was successful or not
 * */
bool		get_ready(Context *&ctx)
{
	/** ---------------------- **/
	/*      LOADING ASSETS      */
	/** ---------------------- **/

	Logging::debug("Loading the assets...");
	if (!Assets::load_tilemap("configs/tileset.png"))
	{
		Logging::fatal("Couldn't load the needed assets!");
		return false;
	}
	Logging::debug("Successfully loaded the needed assets!");

	/** ---------------------- **/
	/*     ALLOCATING MEMORY    */
	/** ---------------------- **/

	Logging::debug("Preparing the memory...");
	ctx = new Context();
	if (!ctx)
	{
		unload(ctx);
		Logging::fatal("Couldn't allocate the requiered memory!");
		return false;
	}

	ctx->fw = new Framework();
	ctx->map = new World(400, 400);
	ctx->ui = new Interface();
	if (!ctx->fw || !ctx->fw->is_ready() || !ctx->map || !ctx->ui)
	{
		unload(ctx);
		Logging::fatal("Couldn't allocate the requiered memory!");
		return false;
	}
	Logging::debug("Successfully allocated the requiered memory!");

	/** ---------------------- **/
	/*     POST MEMORY SETUP    */
	/** ---------------------- **/

	Logging::debug("Configuring the game...");
	ctx->fw->set_framelimit(Configs::graphics::framerate);
	Logging::debug("Successfully configured the game!");
	return true;
}
