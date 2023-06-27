/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Tile.hpp                           */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, June 27, 2023 10:02 PM        */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

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

		typedef uint32_t		id_type;
		typedef void *			meta_type;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		Tile();
		Tile(const id_type &id, const bool &collision = false, const meta_type &meta = nullptr);
		Tile(const Tile &tile);
		Tile(Tile &&tile);
		~Tile();

			/** ---------------------- **/
			/*         OVERLOADS        */
			/** ---------------------- **/

		Tile			&operator=(const Tile &tile);
		Tile			&operator=(Tile &&tile);

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		id_type			get_id() const;
		bool			get_collision() const;
		meta_type		get_meta() const;

		void			set_id(const id_type &id);
		void			set_collision(const bool &collision);
		void			set_meta(const meta_type &meta);

		std::string		rawData() const;

	private:

			/** ---------------------- **/
			/*           FIELDS         */
			/** ---------------------- **/

		id_type			_id;
		bool			_collision;
		meta_type		_meta;

};
