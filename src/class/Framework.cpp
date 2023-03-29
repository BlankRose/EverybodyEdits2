/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Framework.cpp               */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Wed Mar 29 15:32:45 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/Framework.hpp"
#include <stdexcept>

Framework::Framework():
	_window(nullptr)
{
	_window = new sf::RenderWindow(
		sf::VideoMode(
			sf::VideoMode::getDesktopMode().width >> 2,
			sf::VideoMode::getDesktopMode().height >> 2),
		"Everybody Edits 2");
}