/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - events.cpp                  */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Apr  7 20:50:33 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * Handles keyboard's key presses (Event::KeyPressed)
 * 
 * @note	This was handled this way rather than using IsKeyPressed since on OSX,
 * 			it tends to be super annoying with permissions requests
 * 
 * @param	event: Event handle which has the information stored
 * @param	ctx: Context of the current target window
 * */
void key_press(const sf::Event &event, Context *&ctx)
{
	Tile::id_type id = ctx->game->getSelected().get_id();
	if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9 && id)
		ctx->game->setSelected(Tile((id - 1) / 10 * 10 + (event.key.code - sf::Keyboard::Num0) + 1));
	else if (event.key.code >= sf::Keyboard::Numpad1 && event.key.code <= sf::Keyboard::Numpad4)
		ctx->game->setSelected(Tile(id % 10 + (event.key.code - sf::Keyboard::Numpad1 + (id % 10 ? 0 : 1)) * 10));

	else
		switch (event.key.code)
		{
			case sf::Keyboard::Left:
				ctx->left = true;
				break;
			case sf::Keyboard::Right:
				ctx->right = true;
				break;
			case sf::Keyboard::Up:
				ctx->up = true;
				break;
			case sf::Keyboard::Down:
				ctx->down = true;
				break;
			case sf::Keyboard::Escape:
				ctx->fw->get_window().close();
				break;
			case sf::Keyboard::Numpad0:
				ctx->game->setSelected(Tile());
				break;
			default: break;
		}
}

/**
 * Handles the keyboard's key releases (Event::KeyRelease)
 * 
 * @note	This was handled this way rather than using IsKeyPressed since on OSX,
 * 			it tends to be super annoying with permissions requests
 * 
 * @param	event: Event handle which has the information stored
 * @param	ctx: Context of the current target window
 * */
void key_release(const sf::Event &event, Context *&ctx)
{
	switch(event.key.code)
	{
		case sf::Keyboard::Left:
			ctx->left = false;
			break;
		case sf::Keyboard::Right:
			ctx->right = false;
			break;
		case sf::Keyboard::Up:
			ctx->up = false;
			break;
		case sf::Keyboard::Down:
			ctx->down = false;
			break;
		default: break;
	}
}

/**
 * Handles the mouse button presses (Event::MousePressed)
 * 
 * @param	ctx: Context of the current target window
 * @param	win: Window which handle the current input event
 * */
void mouse_press(const sf::Event &event, Context *&ctx)
{
	if (event.mouseButton.button == sf::Mouse::Left)
		ctx->mouse_L = true;
	else if (event.mouseButton.button == sf::Mouse::Middle)
		ctx->mouse_M = true;
	else if (event.mouseButton.button == sf::Mouse::Right)
		ctx->mouse_R = true;
}

/**
 * Handles the mouse button releases (Event::MouseReleased)
 * 
 * @param	ctx: Context of the current target window
 * @param	win: Window which handle the current input event
 * */
void mouse_release(const sf::Event &event, Context *&ctx)
{
	if (event.mouseButton.button == sf::Mouse::Left)
		ctx->mouse_L = false;
	else if (event.mouseButton.button == sf::Mouse::Middle)
		ctx->mouse_M = false;
	else if (event.mouseButton.button == sf::Mouse::Right)
		ctx->mouse_R = false;
}

/**
 * Cycles events endlessly until the window closes
 * 
 * @param	ctx: Context of the target instance
 * */
void event_unit(Context *&ctx)
{
	sf::RenderWindow	&win = ctx->fw->get_window();
	sf::Event			event;

	while (win.isOpen() && win.pollEvent(event))
		switch (event.type)
		{
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::KeyPressed:
				key_press(event, ctx);
				break;
			case sf::Event::KeyReleased:
				key_release(event, ctx);
				break;
			case sf::Event::MouseButtonPressed:
				mouse_press(event, ctx);
				break;
			case sf::Event::MouseButtonReleased:
				mouse_release(event, ctx);
			default: break;
		}
}
