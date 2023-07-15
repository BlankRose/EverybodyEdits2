/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - GameController.hpp                 */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Saturday, July 15, 2023 7:19 PM        */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include "utils/NonCopyable.hpp"
#include "Tile.hpp"

#include <SFML/Graphics.hpp>

class World;
class Camera;
class TileSelector;
class Player;

/**
 * GameController
 * << MVC (Game's Controller) >>
 * 
 * Serves as the game's internal controller.
 * Handles the savestates, and its display.
 * */
class GameController:
	public NonCopyable,
	public sf::Drawable
{
	public:

		GameController();
		GameController(World *world, Camera *camera);
		~GameController();

		inline bool isReady() const;
		inline operator bool() const;
		inline bool operator!() const;

		bool newWorld(const uint32_t &width, const uint32_t &height);
		bool loadWorld(const std::string &path);
		bool saveWorld(const std::string &path);
		bool destroyWorld();
		World *getWorld() const;

		bool newCamera(const sf::View &view);
		bool moveCamera(const sf::View &view);
		bool resetCamera(const sf::View &view);
		bool destroyCamera();

		Player *getPlayer() const;

		const Tile &getSelected() const;
		void setSelected(const Tile &tile);

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:

		World *_world;
		Camera *_camera;
		TileSelector *_selector;
		Player *_player;
};
