/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Framework.hpp               */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Wed Mar 29 15:21:13 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef FRAMEWORK_HPP
# define FRAMEWORK_HPP

# include <SFML/Graphics.hpp>

class Framework
{
	public:

		Framework();
		~Framework();

	private:

		sf::RenderWindow	*_window;
};

#endif /* FRAMEWORK_HPP */