/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - World.hpp                          */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, June 27, 2023 10:15 PM        */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once
#include "Tile.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * World
 * 
 * Represents a world loaded within the game. Contains all the tiles and
 * information about the world.
 * */
class World
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint32_t			size_type;
		typedef sf::Vector2u		position_type;
		typedef std::vector<Tile>	tiles_array;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

	private:
		World();

	public:
		World(const size_type &width, const size_type &height);
		World(const std::string &data);
		~World();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		size_type		get_width() const;
		size_type		get_height() const;

		Tile			&get_tile(const size_type &x, const size_type &y);
		const Tile		&get_tile(const size_type &x, const size_type &y) const;

		void			set_width(const size_type &width);
		void			set_height(const size_type &height);
		void			set_tile(const size_type &x, const size_type &y, const Tile &tile);

			/** ---------------------- **/
			/*          DELETED         */
			/** ---------------------- **/

		World(const World &world) = delete;
		World(World &&world) = delete;

		World			&operator=(const World &world) = delete;
		World			&operator=(World &&world) = delete;

	private:

			/** ---------------------- **/
			/*           FIELDS         */
			/** ---------------------- **/

		position_type		_size;
		std::vector<Tile>	_fg_tiles;
		std::vector<Tile>	_bg_tiles;

};
