/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Context.hpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Thursday, July 13, 2023 12:09 AM       */
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

		// Enums of flags, each reprensenting their corresponding
		// position within the flags variable
		enum Flags
		{
			BG = 0, GOD,
			UP, DOWN, RIGHT, LEFT,
			MOUSE_L, MOUSE_R, MOUSE_M
		};

		Context();
		Context(const Context &other);
		Context(Context &&other);
		~Context();

		Context			&operator=(const Context &other);
		Context			&operator=(Context &&other);

		// Enables a given flag (within flags variable)
		inline void		enableFlag(const Flags &target)
			{ flags |= (1UL << target); }

		// Disables a given flag (within flags variable)
		inline void		disableFlag(const Flags &target)
			{ flags &= ~(1UL << target); }

		// Flips a given flag (within flags variable)
		inline void		toggleFlag(const Flags &target)
			{ flags ^= (1UL << target); }

		// Toggles a given flag (within flags variable)
		inline void		setFlag(const Flags &target, const bool &value)
			{ value ? enableFlag(target) : disableFlag(target); }

		// Retrieves a given flag (within flags variable)
		inline bool		getFlag(const Flags &target) const
			{ return (flags >> target) & 1U; }

		int				flags;
		Displays		display;

		Framework		*fw;
		GameController	*game;
};
