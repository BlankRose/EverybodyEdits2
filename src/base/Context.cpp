/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Context.cpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Thursday, July 13, 2023 12:03 AM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "base/Context.hpp"
#include <utility>

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Context::Context():
	flags(0), display(LOADING), fw(nullptr), game(nullptr) {}

Context::Context(const Context &other)
	{ operator=(other); }

Context::Context(Context &&other)
	{ operator=(std::move(other)); }

Context::~Context() {}

	/** ---------------------- **/
	/*         OVERLOADS        */
	/** ---------------------- **/

Context		&Context::operator=(const Context &other)
{
	flags = other.flags;
	display = other.display;
	fw = other.fw;
	game = other.game;

	return *this;
}

Context &Context::operator=(Context &&other)
{
	flags = std::move(other.flags);
	display = std::move(other.display);
	fw = std::move(other.fw);
	game = std::move(other.game);

	return *this;
}
