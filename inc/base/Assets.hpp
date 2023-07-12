/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Assets.hpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, July 12, 2023 8:53 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include <SFML/Graphics.hpp>

namespace Assets
{
			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef std::string						path_type;

		typedef uint16_t						id_type;
		typedef sf::Vector2u					size_type;
		typedef sf::Texture						texture_type;
		typedef sf::Font						font_type;

			/** ---------------------- **/
			/*     PACKS DEFINTIONS     */
			/** ---------------------- **/

		struct AssetsPack
		{
			AssetsPack() = delete;
			AssetsPack(const id_type &begin, const id_type &range, const char *path):
				begin(begin), range(range), path(path) {}
			~AssetsPack() {}

			id_type begin;
			id_type range;
			const char *path;
		};

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
		texture_type	&get_player();
		texture_type	&get_texture(const id_type &id, const bool &bg = false);
		size_type		get_size();
}
