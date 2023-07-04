/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Context.hpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, July 4, 2023 8:51 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

class Framework;
class GameController;

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

		Context			&operator=(const Context &other);

		bool			up, down, right, left;
		bool			mouse_L, mouse_R, mouse_M;
		Displays		display;

		Framework		*fw;
		GameController	*game;
};
