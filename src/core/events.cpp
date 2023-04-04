/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - events.cpp                  */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Sun Apr  2 12:52:28 CEST 2023     */
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
void	key_press(sf::Event event, Context *&ctx)
{
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
		case sf::Keyboard::Num1:
		case sf::Keyboard::Numpad1:
			ctx->ui->set_selected(0);
			break;
		case sf::Keyboard::Num2:
		case sf::Keyboard::Numpad2:
			ctx->ui->set_selected(1);
			break;
		case sf::Keyboard::Num3:
		case sf::Keyboard::Numpad3:
			ctx->ui->set_selected(2);
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
void	key_release(sf::Event event, Context *&ctx)
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
void	mouse_press(sf::Event event, Context *&ctx)
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
void	mouse_release(sf::Event event, Context *&ctx)
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
void	event_cycle(Context *&ctx)
{
	sf::RenderWindow	&win = ctx->fw->get_window();
	sf::Event			event;

	while (win.pollEvent(event))
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
