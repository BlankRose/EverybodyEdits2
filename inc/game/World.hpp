/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - World.hpp                          */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, June 28, 2023 5:24 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once
#include "Tile.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iosfwd>

// World's data format:
//
// 2 bytes: world's width
// 2 bytes: world's height
// Every tile's data, in the following order:
//  - 4 bytes: Foreground tile's data
//  - 4 bytes: Background tile's data
// Every additional metadata linked to tiles:
//  - 2 bytes: Metadata identifier
//  - 2 bytes: Metadata size
//  - X bytes: Metadata data

/**
 * World
 * 
 * Represents a world loaded within the game. Contains all the tiles and
 * information about the world.
 * */
class World
{
	World();
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint16_t				size_type;
		typedef sf::Vector2<size_type>	position_type;
		typedef std::vector<Tile>		tiles_array;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		World(const size_type &width, const size_type &height);
		World(const char *data);
		World(std::ifstream &file);
		~World();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		size_type		get_width() const;
		size_type		get_height() const;

		Tile			&get_fg_tile(const size_type &x, const size_type &y);
		Tile			&get_bg_tile(const size_type &x, const size_type &y);
		const Tile		&get_fg_tile(const size_type &x, const size_type &y) const;
		const Tile		&get_bg_tile(const size_type &x, const size_type &y) const;

		void			set_width(const size_type &width);
		void			set_height(const size_type &height);

		void			set_fg_tile(const size_type &x, const size_type &y, const Tile &tile);
		void			set_bg_tile(const size_type &x, const size_type &y, const Tile &tile);

		std::string		raw_data() const;

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
