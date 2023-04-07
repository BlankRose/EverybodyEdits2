/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Tiles.hpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Apr  7 17:48:01 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef TILES_HPP
# define TILES_HPP

# include "Assets.hpp"

# include <string>
# include <map>

class Tile
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef Assets::group_type				group_type;
		typedef Assets::id_type					id_type;

		typedef sf::Vertex						vertex_type;
		typedef uint32_t						coord_type;
		typedef sf::Vector2<coord_type>			position_type;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		Tile();
		Tile(const position_type &pos, vertex_type *&vertex, const id_type &id, const group_type &group);
		Tile(const Tile &other);
		~Tile();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		Tile			&operator=(const Tile &other);

		vertex_type		*get_vertex() const;
		position_type	get_position() const;
		group_type		get_group() const;
		id_type			get_id() const;

		void			set_position(const position_type &pos);
		void			set_id(const id_type &id, const group_type &group);

	private:

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		vertex_type *	_vertex;
		position_type	_coords;

		group_type		_group;
		id_type			_id;

		bool			_collision;
};

#endif /* TILES_HPP */