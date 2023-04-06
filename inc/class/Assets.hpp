/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Assets.hpp                  */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Apr  6 15:43:00 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef ASSETS_HPP
# define ASSETS_HPP

# include <SFML/Graphics.hpp>
# include <map>

namespace Assets
{
			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef std::string						path_type;

		typedef std::string						group_type;
		typedef uint32_t						id_type;
		typedef std::pair<id_type, id_type>		id_region;
		typedef std::map<group_type, id_region>	texture_map;

		typedef uint32_t						size_type;
		typedef sf::Vector2<size_type>			vector_type;
		typedef sf::Vector2<vector_type>		rect_type;
		typedef sf::Texture						texture_type;

			/** ---------------------- **/
			/*          LOADERS         */
			/** ---------------------- **/

		bool			load_tilemap(const path_type &base_dir);

		void			set_size(const vector_type &size);
		void			set_size(const size_type &x, const size_type &y);

		texture_type	&get_tilemap(const bool &bg = false);
		vector_type		get_size(const bool &bg = false);

		rect_type		get_tile_coords(const group_type &group, const id_type &id, const bool &bg = false);
		rect_type		get_tile_coords(const size_type &x, const size_type &y);
}

#endif /* ASSETS_HPP */