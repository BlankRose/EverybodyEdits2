/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Context.hpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Apr  6 20:30:09 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include <cstdint>

class Framework;
class Interface;
class World;

class Context
{
	public:

		enum Displays
		{
			LOADING = 0,
			WORLD = 1
		};

		Context();
		Context(const Context &other);
		~Context();

		Context		&operator=(const Context &other);

		bool		up, down, right, left;
		bool		mouse_L, mouse_R, mouse_M;
		Displays	display;

		Framework	*fw;
		World		*map;
		Interface	*ui;
};

#endif /* CONTEXT_HPP */