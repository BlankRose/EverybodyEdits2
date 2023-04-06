/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - drawing.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Apr  6 21:23:49 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * Just a basic loading screen drawing function
 * 
 * @param	win: Target window to display the loading screen on
 * */
void	loading_screen(sf::RenderWindow &win)
{
	sf::Vector2f		center = win.getView().getCenter();
	sf::Vector2f		size = win.getView().getSize();
	sf::VertexArray		arr(sf::Quads, 4);
	sf::Texture			screen = Assets::get_loadscreen();
	sf::RenderStates	states = sf::RenderStates::Default;

	arr[0].position = sf::Vector2f(center.x - size.x / 2, center.y - size.y / 2);
	arr[1].position = sf::Vector2f(center.x + size.x / 2, center.y - size.y / 2);
	arr[2].position = sf::Vector2f(center.x + size.x / 2, center.y + size.y / 2);
	arr[3].position = sf::Vector2f(center.x - size.x / 2, center.y + size.y / 2);

	arr[0].texCoords = sf::Vector2f(0, 0);
	arr[1].texCoords = sf::Vector2f(screen.getSize().x, 0);
	arr[2].texCoords = sf::Vector2f(screen.getSize().x, screen.getSize().y);
	arr[3].texCoords = sf::Vector2f(0, screen.getSize().y);

	states.texture = &screen;
	win.draw(arr, states);
}

/**
 * Drawing loop, which handles all of the
 * SFML drawings elements onto the target window
 * 
 * @param	ctx: Context of the target instance
 * */
void	draws_unit(Context *&ctx)
{
	sf::RenderWindow	&win = ctx->fw->get_window();

	win.clear();
	switch (ctx->display)
	{
		case Context::LOADING:
			loading_screen(win);
			break;
		case Context::WORLD:
			ctx->map->render(ctx->fw);
			ctx->ui->render(ctx->fw);
			break;
	}
	win.display();
}
