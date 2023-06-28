/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Context.hpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, June 28, 2023 4:58 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include <cstdint>

class Framework;
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
};
