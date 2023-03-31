/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - TileMap.hpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Mar 31 18:22:05 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef TILEMAP_HPP
# define TILEMAP_HPP

# include "MapChunk.hpp"

class TileMap:
	public sf::Drawable,
	public sf::Transformable
{
	TileMap();

	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint32_t			size_type;
		typedef sf::VertexArray		vertex_type;
		typedef sf::Texture			texture_type;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		TileMap(const size_type &tile_size, const size_type &width, const size_type &height);
		~TileMap();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

	private:

		virtual void	draw(sf::RenderTarget &target, sf::RenderStates states) const;

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		size_type		_tile_size;
		size_type		_width;
		size_type		_height;
		vertex_type		_vertices;
};

#endif /* TILEMAP_HPP */