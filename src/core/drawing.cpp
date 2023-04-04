/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - drawing.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Tue Apr  4 15:10:37 CEST 2023     */
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
 * Handles the mouse inputs
 * 
 * @param	win: Window which handle the current input event
 * @param	event: Event handle which has the information stored
 * */
void	mouse_handle(sf::RenderWindow &win, sf::Event event, World *&map)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f	pos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
		sf::Vector2u	tile_pos(pos.x / MapChunk::get_tilesize(), pos.y / MapChunk::get_tilesize());

		if (!map->has_tile(tile_pos)) return;
		Tile			&tile = map->get_tile_at(tile_pos);

		if (event.mouseButton.button == sf::Mouse::Left)
			tile.set_id(0);
		if (event.mouseButton.button == sf::Mouse::Right)
			tile.set_id(1);
		if (event.mouseButton.button == sf::Mouse::Middle)
			tile.set_id(2);

		map->get_chunk_at(tile_pos).update_tile(tile);
	}
}

/**
 * Drawing loop, which handles all of the
 * SFML drawings elements onto the target window
 * 
 * @param	fw: Base framework
 * @param	map: Map to display
 * */
void	draw_loop(Framework *&fw, World *&map)
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
			mouse_handle(win, event, map);
		}

		if (up || down || right || left)
		{
			view.move((-left + right) * 10.f, (-up + down) * 10.f);
			win.setView(view);
		}

		win.clear();
		map->render(fw);
		win.display();
	}
}
