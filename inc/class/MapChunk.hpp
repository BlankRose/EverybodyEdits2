/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - MapChunk.hpp                */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Tue Apr  4 15:14:31 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef MAPCHUNK_HPP
# define MAPCHUNK_HPP

# include "Assets.hpp"
# include <vector>

class MapChunk:
	public sf::Drawable,
	public sf::Transformable
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		class Tile;

		typedef uint8_t				size_type;
		typedef uint32_t			id_type;
		typedef sf::VertexArray		vertex_type;
		typedef sf::Texture			texture_type;
		typedef sf::Vector2u		position_type;
		typedef std::vector<Tile>	tiles_type;

		static const size_type		WIDTH;
		static const size_type		HEIGHT;

			/** ---------------------- **/
			/*        SUB CLASSES       */
			/** ---------------------- **/

		class Tile
		{
			public:

				Tile();
				Tile(const position_type &pos, sf::Vertex *vertex, const id_type &id);
				Tile(const Tile &other);
				~Tile();

				Tile			&operator=(const Tile &other);

				sf::Vertex		*get_vertex() const;
				position_type	get_position() const;
				id_type			get_id() const;

				void			set_id(const id_type &id);

			private:

				sf::Vertex *	_vertex;
				position_type	_coords;
				id_type			_id;
		};

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

		Tile				&get_tile_at(const size_type &x, const size_type &y);
		const Tile			&get_tile_at(const size_type &x, const size_type &y) const;

		sf::Vertex *		get_tilevertex(const size_type &x, const size_type &y);
		const sf::Vertex *	get_tilevertex(const size_type &x, const size_type &y) const;

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