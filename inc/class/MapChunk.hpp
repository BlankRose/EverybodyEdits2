/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - MapChunk.hpp                */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Apr  7 19:13:29 CEST 2023     */
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
		MapChunk(const char *data);
		~MapChunk();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		static void			set_tilesize(const size_type &size);
		static size_type	&get_tilesize();

		Tile				&get_tile_at(const coord_type &x, const coord_type &y, const bool &bg = false);
		const Tile			&get_tile_at(const coord_type &x, const coord_type &y, const bool &bg = false) const;

		sf::Vertex *		get_tilevertex(const coord_type &x, const coord_type &y, const bool &bg = false);
		const sf::Vertex *	get_tilevertex(const coord_type &x, const coord_type &y, const bool &bg = false) const;

		position_type		&get_position();
		const position_type	&get_position() const;
		void				set_position(const position_type &pos);

		void				update_tile(const Tile &tile, const bool &bg = false);
		std::string			as_data() const;

	private:

		virtual void		draw(sf::RenderTarget &target, sf::RenderStates states) const;

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		position_type		_position;
		static size_type	_tile_size;

		tiles_type			_fg_tiles;
		vertex_type			_fg_vertices;

		tiles_type			_bg_tiles;
		vertex_type			_bg_vertices;
};

#endif /* MAPCHUNK_HPP */