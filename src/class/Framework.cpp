/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Framework.cpp               */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Mar 30 20:04:04 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/Framework.hpp"
#include <stdexcept>

	/** ---------------------- **/
	/*     TYPE DEFINITIONS     */
	/** ---------------------- **/

using size_type = Framework::size_type;

const std::string	Framework::TITLE = "Everybody Edits 2";

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Framework::Framework():
	_width(sf::VideoMode::getDesktopMode().width >> 2),
	_height(sf::VideoMode::getDesktopMode().height >> 2)
{
	_window = new sf::RenderWindow(sf::VideoMode(_width, _height), TITLE);
	_view = new sf::View(sf::Vector2f(_width >> 2, _height >> 2), sf::Vector2f(_width, _height));
}

Framework::Framework(const size_type &width, const size_type &height):
	_width(width), _height(height)
{
	_window = new sf::RenderWindow(sf::VideoMode(width, height), TITLE);
	_view = new sf::View(sf::Vector2f(width >> 2, height >> 2), sf::Vector2f(width, height));
}

Framework::~Framework()
{
	if (_window) delete _window;
	if (_view) delete _view;
}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

bool				Framework::is_ready() const
	{ return _window && _view; }

bool				Framework::is_open() const
	{ return _window->isOpen(); }

bool				Framework::is_focus() const
	{ return _window->hasFocus(); }

sf::RenderWindow	&Framework::get_window() const
	{ return *_window; }

sf::View			&Framework::get_view() const
	{ return *_view; }

size_type			Framework::get_width() const
	{ return _width; }

size_type			Framework::get_height() const
	{ return _height; }

void				Framework::set_view(const sf::View &view)
	{ *_view = view; }
