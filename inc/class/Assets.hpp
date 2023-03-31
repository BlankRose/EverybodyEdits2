/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Assets.hpp                  */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Mar 31 17:31:24 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef ASSETS_HPP
# define ASSETS_HPP

# include <SFML/Graphics.hpp>

namespace Assets
{
			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint32_t					size_type;
		typedef sf::Vector2<size_type>		vector_type;
		typedef sf::Vector2<vector_type>	rect_type;
		typedef sf::Texture					texture_type;

		static const size_type				TILE_SIZE = 32;

			/** ---------------------- **/
			/*          LOADERS         */
			/** ---------------------- **/

		bool			load_tilemap(const std::string &path);

		texture_type	&get_tilemap();
		vector_type		get_size();
		rect_type		get_tile_coords(const size_type &x, const size_type &y);
}

#endif /* ASSETS_HPP */