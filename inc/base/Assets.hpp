/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Assets.hpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Thursday, June 29, 2023 1:46 PM        */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include <SFML/Graphics.hpp>
#include <map>

namespace Assets
{
			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		enum Packs
		{
			SPECIAL = 0,
			BASIC,
			BRICKS,
			BETA,
			STATIC
		};

		typedef std::string						path_type;

		typedef Packs							group_type;
		typedef uint8_t							id_type;
		typedef std::pair<id_type, id_type>		id_region;
		typedef std::map<group_type, id_region>	texture_map;

		typedef uint32_t						size_type;
		typedef sf::Vector2<size_type>			vector_type;
		typedef sf::Vector2<vector_type>		rect_type;
		typedef sf::Texture						texture_type;
		typedef sf::Font						font_type;

			/** ---------------------- **/
			/*          LOADERS         */
			/** ---------------------- **/

		bool			load_ressources(const path_type &base_dir);

		void			set_size(const vector_type &size);
		void			set_size(const size_type &x, const size_type &y);

		font_type		&get_font();
		texture_type	&get_loadscreen();
		texture_type	&get_tilemap(const bool &bg = false);
		vector_type		get_size(const bool &bg = false);

		rect_type		get_tile_coords(const group_type &group, const id_type &id, const bool &bg = false);
		rect_type		get_tile_coords(const size_type &x, const size_type &y);
}
