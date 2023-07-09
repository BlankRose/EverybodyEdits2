/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - World.hpp                          */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Sunday, July 9, 2023 10:32 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include "Tile.hpp"
#include "utils/NonCopyable.hpp"

#include <SFML/System.hpp>

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
 * << MVC (Game's Model) >>
 * 
 * Represents a world loaded within the game. Contains all the tiles and
 * information about the world.
 * */
class World:
	public NonCopyable
{
	World();
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint16_t				size_type;
		typedef sf::Vector2<size_type>	scale_type;
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

		scale_type	get_size() const;
		size_type	get_width() const;
		size_type	get_height() const;

		Tile		&get_fg_tile(const size_type &x, const size_type &y);
		Tile		&get_bg_tile(const size_type &x, const size_type &y);
		const Tile	&get_fg_tile(const size_type &x, const size_type &y) const;
		const Tile	&get_bg_tile(const size_type &x, const size_type &y) const;

		void		set_fg_tile(const size_type &x, const size_type &y, const Tile &tile);
		void		set_bg_tile(const size_type &x, const size_type &y, const Tile &tile);
		void 		set_fg_tile(const size_type &x, const size_type &y, Tile &&tile);
		void		set_bg_tile(const size_type &x, const size_type &y, Tile &&tile);

		bool		has_tile(const int32_t &x, const int32_t &y) const;

		std::string	raw_data() const;
		void		save(std::ofstream &file) const;

	private:

			/** ---------------------- **/
			/*           FIELDS         */
			/** ---------------------- **/

		scale_type			_size;
		std::vector<Tile>	_fg_tiles;
		std::vector<Tile>	_bg_tiles;
};
