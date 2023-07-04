/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - GameController.hpp                 */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, July 4, 2023 7:36 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include "utils/NonCopyable.hpp"
#include <SFML/Graphics.hpp>

class World;
class Camera;
class Framework;

/**
 * GameController
 * << MVC (Game's Controller) >>
 * 
 * Serves as the game's internal controller.
 * Handles the savestates, and its display.
 * */
class GameController:
	public NonCopyable
{

	public:

		GameController();
		GameController(World *world, Camera *camera);
		~GameController();

		inline bool hasWorld() const;
		inline bool hasCamera() const;
		inline bool isReady() const;
		inline operator bool() const;
		inline bool operator!() const;

		bool newWorld(const uint32_t &width, const uint32_t &height);
		bool loadWorld(const std::string &path);
		bool saveWorld(const std::string &path);
		bool destroyWorld();

		bool newCamera(const sf::View &view);
		bool resizeCamera(const sf::View &size);
		bool destroyCamera();

		void update();
		void render(Framework *framework);

		World *getWorld() const;
		Camera *getCamera() const;

	private:

		World *world;
		Camera *camera;

};
