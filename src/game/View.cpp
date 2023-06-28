/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - View.cpp                           */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, June 28, 2023 5:56 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/View.hpp"

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using pos_type = View::pos_type;
using vertex_array = View::vertex_array;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

View::View(World *world, const pos_type &position):
	_world(world), _position(position),
	_vertices(sf::Quads, world->get_width() * world->get_height() * 4)
{
	// TODO: Implement
}

View::~View() {}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

World			*View::get_world() const { return _world; }
const pos_type	&View::get_position() const { return _position; }
pos_type		&View::get_position() { return _position; }

void			View::set_world(World *world) { _world = world; }
void			View::set_position(const pos_type &position) { _position = position; }

void			View::update()
{
	// TODO: Implement
}

void			View::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	(void) target;
	(void) states;
	// TODO: Implement
}
