/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Context.cpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, June 27, 2023 8:09 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "class/Context.hpp"

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Context::Context():
	up(false), down(false), right(false), left(false),
	mouse_L(false), mouse_R(false), mouse_M(false),
	display(LOADING) {}

Context::Context(const Context &other)
	{ operator=(other); }

Context::~Context() {}

	/** ---------------------- **/
	/*         OVERLOADS        */
	/** ---------------------- **/

Context		&Context::operator=(const Context &other)
{
	up = other.up;
	down = other.down;
	right = other.right;
	left = other.right;

	mouse_L = other.mouse_L;
	mouse_R = other.mouse_R;
	mouse_M = other.mouse_M;

	display = other.display;

	return *this;
}
