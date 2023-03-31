/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - drawing.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Mar 31 21:27:39 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

void	draw_loop(Framework *&fw, TileMap *&map)
{
	sf::RenderWindow	&win = fw->get_window();
	sf::Event			event;

	while (win.isOpen())
	{
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				win.close();
		}

		win.clear();
		win.draw(*map);
		win.display();
	}
}
