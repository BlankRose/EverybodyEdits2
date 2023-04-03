/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - MapChunk.hpp                */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Mon Apr  3 17:33:42 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef MAPCHUNK_HPP
# define MAPCHUNK_HPP

# include "Assets.hpp"

class MapChunk:
	public sf::Drawable,
	public sf::Transformable
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint8_t				size_type;
		typedef sf::VertexArray		vertex_type;
		typedef sf::Texture			texture_type;
		typedef sf::Vector2u		position_type;

		static const size_type		WIDTH;
		static const size_type		HEIGHT;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		MapChunk();
		MapChunk(const size_type &x, const size_type &y);
		~MapChunk();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		static void			set_tilesize(const size_type &size);
		static size_type	&get_tilesize();

		sf::Vertex			&get_tilevertex(const size_type &x, const size_type &y);
		const sf::Vertex	&get_tilevertex(const size_type &x, const size_type &y) const;

		position_type		&get_position();
		const position_type	&get_position() const;
		void				set_position(const position_type &pos);

	private:

		virtual void		draw(sf::RenderTarget &target, sf::RenderStates states) const;

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		position_type		_position;
		static size_type	_tile_size;
		vertex_type			_vertices;
};

#endif /* MAPCHUNK_HPP */