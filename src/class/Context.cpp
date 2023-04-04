/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Context.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Tue Apr  4 20:43:30 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Context::Context():
	up(false), down(false), right(false), left(false),
	mouse_L(false), mouse_R(false), mouse_M(false),
	fw(nullptr), map(nullptr), ui(nullptr) {}

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

	fw = other.fw;
	map = other.map;
	ui = other.ui;

	return *this;
}