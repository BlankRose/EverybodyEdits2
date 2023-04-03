/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - World.hpp                   */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Mon Apr  3 16:20:28 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef WORLD_HPP
# define WORLD_HPP

# include "MapChunk.hpp"
# include <vector>

class Framework;
class World
{
	World();

	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint32_t				size_type;
		typedef std::vector<MapChunk>	chunks_type;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		World(const size_type &width, const size_type &height);
		~World();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		size_type	get_width() const;
		size_type	get_height() const;
		size_type	get_chunk_width() const;
		size_type	get_chunk_height() const;

		bool		has_chunk(const sf::Vector2u &pos) const;
		bool		has_chunk(const size_type &x, const size_type &y) const;

		MapChunk	&get_chunk_at(const sf::Vector2u &pos);
		MapChunk	&get_chunk_at(const size_type &x, const size_type &y);

		void		render(Framework *&fw);

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