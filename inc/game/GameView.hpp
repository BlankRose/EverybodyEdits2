/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - GameView.hpp                       */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Friday, June 30, 2023 5:40 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include "World.hpp"
#include <SFML/Graphics.hpp>

// View structure:
// 
// - Contains 9 chunks of the world
// - Each chunk is 50x50 tiles
// - Each tile is 16x16 pixels
// - Center chunk is the chunk the player is in
// - When player goes into another chunk, the forward chunk is loaded, and the
//   backward chunk is unloaded (if it exists)

/**
 * GameView
 * 
 * Represents a rendered portion of the world. It will be adjusted to the
 * player's position and will be used to render the world.
 * */
class GameView:
	public sf::Drawable,
	public sf::Transformable,
	public NonCopyable
{
	GameView();
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef sf::Vector2u		pos_type;
		typedef sf::VertexArray		vertex_array;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		GameView(World *world, const pos_type &position = pos_type(0, 0));
		~GameView();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		World			*get_world() const;
		const pos_type	&get_position() const;
		pos_type		&get_position();

		void			set_world(World *world);
		void			set_position(const pos_type &position);

		void			update_position(const pos_type &position);
		void			update_tile(const pos_type &position);
		void			draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		struct Chunk:
			public sf::Drawable,
			public sf::Transformable
		{
			Chunk();
			~Chunk();

			void draw(sf::RenderTarget &target, sf::RenderStates states) const;
			sf::VertexArray	_fg_vertices;
			sf::VertexArray	_bg_vertices;
		};

		World			*_world;
		pos_type		_position;
		Chunk			_chunks[9];
};
