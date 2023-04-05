/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - MapChunk.hpp                */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Wed Apr  5 21:10:53 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef MAPCHUNK_HPP
# define MAPCHUNK_HPP

# include "Tiles.hpp"
# include <vector>

class MapChunk:
	public sf::Drawable,
	public sf::Transformable
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		using Tile = Tile;

		using coord_type = Tile::coord_type;
		using position_type = Tile::position_type;

		typedef uint8_t				size_type;
		typedef sf::VertexArray		vertex_type;
		typedef sf::Texture			texture_type;
		typedef std::vector<Tile>	tiles_type;

		static const size_type		WIDTH;
		static const size_type		HEIGHT;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		MapChunk();
		MapChunk(const coord_type &x, const coord_type &y,
			const bool &top_edge = false, const bool &low_edge = false,
			const bool &left_edge = false, const bool &right_edge = false);
		~MapChunk();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		static void			set_tilesize(const size_type &size);
		static size_type	&get_tilesize();

		Tile				&get_tile_at(const coord_type &x, const coord_type &y);
		const Tile			&get_tile_at(const coord_type &x, const coord_type &y) const;

		sf::Vertex *		get_tilevertex(const coord_type &x, const coord_type &y);
		const sf::Vertex *	get_tilevertex(const coord_type &x, const coord_type &y) const;

		position_type		&get_position();
		const position_type	&get_position() const;
		void				set_position(const position_type &pos);

		void				update_tile(const Tile &tile);

	private:

		virtual void		draw(sf::RenderTarget &target, sf::RenderStates states) const;

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		tiles_type			_tiles;
		position_type		_position;
		static size_type	_tile_size;
		vertex_type			_vertices;
};

#endif /* MAPCHUNK_HPP */