/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - drawing.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Sun Apr  2 13:05:49 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * Stores if key is currently being held or not
 * 
 * @note	Changed by input_handle function
 * */
bool	up = false, down = false, right = false, left = false;

/**
 * Handles the keyboard inputs
 * 
 * @note	This was handled this way rather than using IsKeyPressed since on OSX,
 * 			it tends to be super annoying with permissions requests
 * 
 * @param	win: Window which handle the current input event
 * @param	event: Event handle which has the information stored
 * */
void	input_handle(sf::RenderWindow &win, sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
		switch (event.key.code)
		{
			case sf::Keyboard::Left:
				left = true;
				break;
			case sf::Keyboard::Right:
				right = true;
				break;
			case sf::Keyboard::Up:
				up = true;
				break;
			case sf::Keyboard::Down:
				down = true;
				break;
			case sf::Keyboard::Escape:
				win.close();
			default: break;
		}
	else if (event.type == sf::Event::KeyReleased)
		switch(event.key.code)
		{
			case sf::Keyboard::Left:
				left = false;
				break;
			case sf::Keyboard::Right:
				right = false;
				break;
			case sf::Keyboard::Up:
				up = false;
				break;
			case sf::Keyboard::Down:
				down = false;
				break;
			default: break;
		}
}

/**
 * Drawing loop, which handles all of the
 * SFML drawings elements onto the target window
 * 
 * @param	fw: Base framework
 * @param	map: Map to display
 * */
void	draw_loop(Framework *&fw, TileMap *&map)
{
	sf::RenderWindow	&win = fw->get_window();
	sf::View			view = win.getView();
	sf::Event			event;

	while (win.isOpen())
	{
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				win.close();
			input_handle(win, event);
		}

		if (up || down || right || left)
		{
			view.move((-left + right) * 10.f, (-up + down) * 10.f);
			win.setView(view);
		}

		win.clear();
		win.draw(*map);
		win.display();
	}
}
