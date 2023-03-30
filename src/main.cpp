/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - main.cpp                    */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Mar 30 20:04:32 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

int main(int, char *[], char *[])
{
	Logging::set_output("logs/current.log");
	Logging::debug("Hello World");

	Framework	*fw = new Framework();
	if (!fw)
		return FAILURE;
	else if (!fw->is_ready())
		return FAILURE;

	Logging::debug("Ready!");

	sf::RenderWindow	&win = fw->get_window();
	while (win.isOpen())
	{
		sf::Event	event;
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				win.close();
		}

		win.clear();
		win.display();
	}

	delete fw;
	return SUCCESS;
}
