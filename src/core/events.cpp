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
	if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9
		&& id != _TILEID_EMPTY && id != _TILEID_SPAWN)
		ctx->game->setSelected(Tile(id / 10 * 10 + (event.key.code - sf::Keyboard::Num0)));
	else if (event.key.code >= sf::Keyboard::Numpad1 && event.key.code <= sf::Keyboard::Numpad4)
		ctx->game->setSelected(Tile(id % 10 + (event.key.code - sf::Keyboard::Numpad0) * 10));

	else
		switch (event.key.code)
		{
			// Movements Keybinds
			//////////////////////

			case sf::Keyboard::Left:
			case sf::Keyboard::A:
				ctx->enableFlag(Context::LEFT);
				break;
			case sf::Keyboard::Right:
			case sf::Keyboard::D:
				ctx->enableFlag(Context::RIGHT);
				break;
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				ctx->enableFlag(Context::UP);
				break;
			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				ctx->enableFlag(Context::DOWN);
				break;
			case sf::Keyboard::Space:
				ctx->enableFlag(Context::SPACE);
				break;

			// Gravity Keybinds
			// (Requires: Gravity Status)
			////////////////////

			case sf::Keyboard::I:
				ctx->setGravityUp();
				break;
			case sf::Keyboard::K:
				ctx->setGravityDown();
				break;
			case sf::Keyboard::J:
				ctx->setGravityLeft();
				break;
			case sf::Keyboard::L:
				ctx->setGravityRight();
				break;

			// Modifiers Keybinds
			//////////////////////

			case sf::Keyboard::G:
				ctx->toggleFlag(Context::GOD);
				ctx->game->getPlayer()->toggle_godmode();
				break;
			case sf::Keyboard::Numpad0:
				ctx->game->setSelected(Tile(_TILEID_EMPTY));
				break;
			case sf::Keyboard::Numpad5:
				ctx->game->setSelected(Tile(_TILEID_SPAWN));
				break;
			case sf::Keyboard::Numpad6:
				ctx->game->setSelected(Tile(_TILEID_UP));
				break;
			case sf::Keyboard::Numpad7:
				ctx->game->setSelected(Tile(_TILEID_LEFT));
				break;
			case sf::Keyboard::Numpad8:
				ctx->game->setSelected(Tile(_TILEID_RIGHT));
				break;
			case sf::Keyboard::Numpad9:
				ctx->game->setSelected(Tile(_TILEID_DOWN));
				break;
			case sf::Keyboard::Escape:
				ctx->fw->get_window().close();
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
		case sf::Keyboard::A:
			ctx->disableFlag(Context::LEFT);
			break;
		case sf::Keyboard::Right:
		case sf::Keyboard::D:
			ctx->disableFlag(Context::RIGHT);
			break;
		case sf::Keyboard::Up:
		case sf::Keyboard::W:
			ctx->disableFlag(Context::UP);
			break;
		case sf::Keyboard::Down:
		case sf::Keyboard::S:
			ctx->disableFlag(Context::DOWN);
			break;
		case sf::Keyboard::Space:
			ctx->disableFlag(Context::SPACE);
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
		ctx->enableFlag(Context::MOUSE_L);
	else if (event.mouseButton.button == sf::Mouse::Middle)
		ctx->enableFlag(Context::MOUSE_M);
	else if (event.mouseButton.button == sf::Mouse::Right)
		ctx->enableFlag(Context::MOUSE_R);
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
		ctx->disableFlag(Context::MOUSE_L);
	else if (event.mouseButton.button == sf::Mouse::Middle)
		ctx->disableFlag(Context::MOUSE_M);	
	else if (event.mouseButton.button == sf::Mouse::Right)
		ctx->disableFlag(Context::MOUSE_R);
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
