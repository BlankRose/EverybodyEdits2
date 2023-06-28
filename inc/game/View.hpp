/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - View.hpp                           */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, June 28, 2023 2:06 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once
#include "World.hpp"

/**
 * View
 * 
 * Represents a rendered portion of the world. It will be adjusted to the
 * player's position and will be used to render the world.
 * */
class View:
	sf::Drawable, sf::Transformable
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef sf::Vector2u		pos_type;
		typedef sf::VertexArray		vertex_array;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

	private:
		View();

	public:
		View(World *world, const pos_type &position = pos_type(0, 0));
		~View();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		World			*get_world() const;
		const pos_type	&get_position() const;
		pos_type		&get_position();

		void			set_world(World *world);
		void			set_position(const pos_type &position);

		void			update();
		void			draw(sf::RenderTarget &target, sf::RenderStates states) const;

			/** ---------------------- **/
			/*          DELETED         */
			/** ---------------------- **/

		View(const View &other) = delete;
		View(View &&other) = delete;

		View &operator=(const View &other) = delete;
		View &operator=(View &&other) = delete;

	private:

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		World			*_world;
		pos_type		_position;
		vertex_array	_vertices;
};
