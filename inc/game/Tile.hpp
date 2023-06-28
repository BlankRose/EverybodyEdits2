/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Tile.hpp                           */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, June 28, 2023 5:54 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once
#include <cstdint>

// Raw data format:
//
// 0 >> 10: Meta first part
// 1 >> 10: Meta second part
// 1 >> 20: Begin ID
// MAX UINT32: End ID

/**
 * Tile
 * 
 * Represents a single tile in the world. Mostly serves as storage for the
 * tile's datas, such as its ID, collisions and additional metadata.
 * */
class Tile
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint16_t		id_type;
		typedef uint32_t		raw_type;
		typedef uint32_t		size_type;

		const static size_type	raw_size = sizeof(raw_type);

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		Tile(const id_type &id = 0);
		Tile(const char *data);
		Tile(const Tile &tile);
		Tile(Tile &&tile);
		~Tile();

			/** ---------------------- **/
			/*         OVERLOADS        */
			/** ---------------------- **/

		Tile				&operator=(const Tile &tile);
		Tile				&operator=(Tile &&tile);

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		id_type				get_id() const;
		raw_type			get_raw() const;
		raw_type			get_meta() const;

		void				set_id(const id_type &id);
		void				set_raw(const raw_type &raw);
		void				set_meta(const raw_type &meta);

	private:

			/** ---------------------- **/
			/*           FIELDS         */
			/** ---------------------- **/

		raw_type		_raw;
};
