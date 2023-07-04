/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Assets.hpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, July 4, 2023 7:01 PM          */
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

		typedef std::string						path_type;

		typedef uint16_t						id_type;
		typedef sf::Vector2u					size_type;
		typedef sf::Texture						texture_type;
		typedef std::map<id_type, sf::Texture>	texture_map;
		typedef sf::Font						font_type;

			/** ---------------------- **/
			/*          LOADERS         */
			/** ---------------------- **/

		bool			load_ressources(const path_type &base_dir);
		void			set_size(const size_type &size);
		void			set_size(const unsigned int &x, const unsigned int &y);

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		font_type		&get_font();
		texture_type	&get_loadscreen();
		texture_type	&get_texture(const id_type &id, const bool &bg = false);
		size_type		get_size();
}
