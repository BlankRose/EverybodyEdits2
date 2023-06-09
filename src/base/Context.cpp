/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Context.cpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, July 4, 2023 8:51 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "base/Context.hpp"

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Context::Context():
	up(false), down(false), right(false), left(false),
	mouse_L(false), mouse_R(false), mouse_M(false),
	display(LOADING), fw(nullptr), game(nullptr) {}

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
	fw = other.fw;
	game = other.game;

	return *this;
}
