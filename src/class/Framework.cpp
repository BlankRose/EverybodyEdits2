/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Framework.cpp               */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Mar 31 21:57:29 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/Framework.hpp"
#include <stdexcept>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using size_type = Framework::size_type;
using window_type = Framework::window_type;
using view_type = Framework::view_type;
using context_type = Framework::context_type;

const std::string	Framework::TITLE = "Everybody Edits 2";

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Framework::Framework():
	_context(nullptr),
	_width(sf::VideoMode::getDesktopMode().width >> 1),
	_height(sf::VideoMode::getDesktopMode().height >> 1)
{
	_window = new sf::RenderWindow(sf::VideoMode(_width, _height), TITLE);
	set_view(view_type(sf::Vector2f(_width >> 1, _height >> 1), sf::Vector2f(_width, _height)));
	set_framelimit(60);
}

Framework::Framework(const size_type &width, const size_type &height):
	_context(nullptr), _width(width), _height(height)
{
	_window = new sf::RenderWindow(sf::VideoMode(width, height), TITLE);
	set_view(view_type(sf::Vector2f(_width >> 1, _height >> 1), sf::Vector2f(_width, _height)));
	set_framelimit(60);
}

Framework::~Framework()
	{ if (_window) delete _window; }

	/** ---------------------- **/
	/*         OVERLOADS        */
	/** ---------------------- **/

Framework::operator bool() const
	{ return is_ready(); }

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

bool				Framework::is_ready() const
	{ return _window; }

bool				Framework::is_open() const
	{ return _window ? _window->isOpen() : false; }

bool				Framework::is_focus() const
	{ return _window ? _window->hasFocus() : false; }

context_type		Framework::get_context() const
	{ return _context; }

window_type			&Framework::get_window() const
	{ return *_window; }

const view_type		Framework::get_view() const
	{ return _window ? _window->getView() : sf::View(); }

size_type			Framework::get_width() const
	{ return _width; }

size_type			Framework::get_height() const
	{ return _height; }

void				Framework::set_view(const view_type &view)
	{ if (_window) _window->setView(view); }

void				Framework::set_context(context_type &context)
	{ _context = context; }

void				Framework::set_framelimit(const size_type &limit)
	{ if (_window) _window->setFramerateLimit(limit); }
