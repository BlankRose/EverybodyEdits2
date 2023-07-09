/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - GameController.cpp                 */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Sunday, July 9, 2023 4:23 PM           */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/GameController.hpp"

#include <fstream>
#include "base/Logging.hpp"
#include "game/World.hpp"
#include "game/Camera.hpp"
#include "base/Framework.hpp"

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

/**
 * Default Constructor: Initializes the world and camera to nullptr
 * */
GameController::GameController():
	world(nullptr), camera(nullptr) {}

/**
 * Defined Constructor: Initializes the world and camera to the given ones
 * 
 * @param	world: The world to use
 * @param	camera: The camera to use
 * */
GameController::GameController(World *world, Camera *camera):
	world(world), camera(camera) {}

/**
 * Destructor: Destroys the world and camera along with the controller
 * */
GameController::~GameController()
{
	if (world)
		delete world;
	if (camera)
		delete camera;
}

	/** ---------------------- **/
	/*         OVERLOADS        */
	/** ---------------------- **/

/**
 * Returns wether or not a world exists and is loaded
 * 
 * @return	True or False upon existing or not
 * */
inline bool GameController::hasWorld() const
	{ return world; }

/**
 * Returns wether or not a camera exists and is loaded
 * 
 * @return	True or False upon existing or not
 * */
inline bool GameController::hasCamera() const
	{ return camera; }

/**
 * Returns the state of the controller as a boolean, indicating if it is ready
 * or not to be used (if it has a world and a camera)
 * 
 * @return	True or False upon ready or not
 * */
inline bool GameController::isReady() const
	{ return (world && camera); }

/**
 * Casts the controller to a boolean, indicating if it is ready or not to be
 * used (if it has a world and a camera)
 * 
 * @return	True or False upon ready or not
 * */
inline GameController::operator bool() const
	{ return isReady(); }

/**
 * Casts the controller to a boolean and negates it, indicating if it is not
 * ready or cannot be used yet (if it has no world or no camera)
 * */
inline bool GameController::operator!() const
	{ return !isReady(); }

	/** ---------------------- **/
	/*      WORLD HANDLING      */
	/** ---------------------- **/

/**
 * Creates a brand new empty world, ready to go
 * 
 * @param	width: Width of the world
 * @param	height: Height of the world
 * 
 * @return	True or False upon Success or Failure
 * */
bool GameController::newWorld(const uint32_t &width, const uint32_t &height)
{
	if (world)
		delete world;
	Logging::info("Generating new world... Size: " + std::to_string(width) + "x" + std::to_string(height) + "!");
	world = new World(width, height);

	if (!world)
		return (Logging::fatal("Couldn't generate a new World!"), false);
	Logging::info("Generated new world!");
	return true;
}

/**
 * Loads from a file, the data of a world
 * 
 * @param	path: Path to the target file
 * 
 * @return	True or False upon Success or Failure
 * */
bool GameController::loadWorld(const std::string &path)
{
	if (world)
		delete world;
	if (path.empty() || path.find_first_not_of("\t\n\v\f\r ") == path.npos)
		return (Logging::error("Tried to load the world but the provided path is empty!"), false);

	std::ifstream	ifile(path, std::ios::binary);
	if (!ifile.is_open())
		return (Logging::error("Cannot open the target file: " + path + "!"), false);
	Logging::info("Loading data save...");

	world = new World(ifile);
	ifile.close();

	if (!world)
		return (Logging::fatal("Couldn't allocate the sufficient memory for the world to load in!"), false);
	Logging::info("Map loaded!");
	return true;
}

/**
 * Saves the data of the world into a file
 * 
 * @param	path: Path to the target file
 * 
 * @return	True or False upon Success or Failure
 * */
bool GameController::saveWorld(const std::string &path)
{
	if (!world)
		return (Logging::error("Tried to save the world but the provided world is not defined!"), false);
	if (path.empty() || path.find_first_not_of("\t\n\v\f\r ") == path.npos)
		return (Logging::error("Tried to save the world but the provided path is empty!"), false);

	std::ofstream	ofile(path, std::ios::binary);
	if (!ofile.is_open())
		return (Logging::error("Cannot open the target file: " + path + "!"), false);

	// Closing and Saving takes about same time
	// (3.5s each for 10k x 10k or 7s for both)
	world->save(ofile);
	ofile.close();
	return true;
}

/**
 * Destroys the world, freeing the memory, if it exists
 * 
 * @return	True or False upon Success or Failure
 * */
bool GameController::destroyWorld()
{
	if (!world)
		return (Logging::error("Tried to destroy the world but the internal world is not defined!"), false);

	delete world;
	world = nullptr;

	return true;
}

	/** ---------------------- **/
	/*      CAMERA HANDLING     */
	/** ---------------------- **/

/**
 * Creates a brand new empty camera, ready to go (or reinitializes it if already
 * existing) at given viewport
 * 
 * @param	view: Viewport of the camera
 * 
 * @return	True or False upon Success or Failure
 * */
bool GameController::newCamera(const sf::View &view)
{
	if (camera)
		delete camera;

	Logging::info("Generating new camera...");
	camera = new Camera(view);

	if (!camera)
		return (Logging::fatal("Couldn't allocate the sufficient memory for the camera to load in!"), false);
	Logging::info("Generated new camera!");
	return true;
}

/**
 * Moves the camera to the given viewport
 * 
 * @param	view: Viewport of the camera
 * 
 * @return	True or False upon Success or Failure
 * */
bool GameController::moveCamera(const sf::View &view)
{
	if (!camera)
		return (Logging::error("Tried to move the camera but the internal camera is not defined!"), false);

	camera->move(view);
	return true;
}

/**
 * Destroys the camera, freeing the memory, if it exists
 * 
 * @return	True or False upon Success or Failure
 * */
bool GameController::destroyCamera()
{
	if (!camera)
		return (Logging::error("Tried to destroy the camera but the internal camera is not defined!"), false);

	delete camera;
	camera = nullptr;
	return true;
}

/**
 * Draws the world and its entities on the screen, using the camera which is
 * specialized in rendering the world
 * 
 * @param	framework: Framework to use for rendering
 * */
void GameController::render(Framework *framework)
{
	if (!world || !camera)
		return;

	camera->setReference(world);
	framework->get_window().draw(*camera);
}

/**
 * Retrieves the internal world
 * 
 * @return	Internal world
 * */
World *GameController::getWorld() const
	{ return world; }

/**
 * Retrieves the internal camera
 * 
 * @return	Internal camera
 * */
Camera *GameController::getCamera() const
	{ return camera; }
