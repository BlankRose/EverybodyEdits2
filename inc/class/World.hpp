/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - World.hpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Apr  7 18:55:17 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef WORLD_HPP
# define WORLD_HPP

# include "MapChunk.hpp"
# include <vector>

using Tile = MapChunk::Tile;

class Framework;
class Context;

class World
{
	World();

	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint32_t					size_type;
		typedef std::vector<MapChunk>		chunks_type;
		typedef std::vector<std::string>	data_type;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		World(const size_type &width, const size_type &height);
		World(const size_type &width, const size_type &height, const data_type &data);
		~World();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		size_type	get_width() const;
		size_type	get_height() const;
		size_type	get_chunk_width() const;
		size_type	get_chunk_height() const;

		bool		has_chunk(const sf::Vector2u &pos) const;
		bool		has_tile(const sf::Vector2u &pos) const;
		bool		has_chunk(const size_type &x, const size_type &y) const;
		bool		has_tile(const size_type &x, const size_type &y) const;

		MapChunk	&get_chunk_at(const sf::Vector2u &pos);
		Tile		&get_tile_at(const sf::Vector2u &pos);
		MapChunk	&get_chunk_at(const size_type &x, const size_type &y);
		Tile		&get_tile_at(const size_type &x, const size_type &y);

		void		render(Framework *&fw);
		data_type	as_data() const;

	private:

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

			size_type				_width;
			size_type				_height;

			size_type				_chunks_width;
			size_type				_chunks_height;
			chunks_type				_chunks;
};

#endif /* WORLD_HPP */