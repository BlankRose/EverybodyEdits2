/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Context.hpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 17, 2023 3:38 PM          */
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
			BG = 0, GOD, BACKGROUND,
			UP, DOWN, RIGHT, LEFT, SPACE,
			MOUSE_L, MOUSE_R, MOUSE_M,
			GRAVITY_SIDE, GRAVITY_FLIP, FORCED_GRAVITY,
			FORCED_GRAVITY_SIDE, FORCED_GRAVITY_FLIP,
		};

		Context();
		Context(const Context &other);
		Context(Context &&other);
		~Context();

		Context &operator=(const Context &other);
		Context &operator=(Context &&other);

		// Enables a given flag (within flags variable)
		inline void enableFlag(const Flags &target)
			{ flags |= (1UL << target); }

		// Disables a given flag (within flags variable)
		inline void disableFlag(const Flags &target)
			{ flags &= ~(1UL << target); }

		// Flips a given flag (within flags variable)
		inline void toggleFlag(const Flags &target)
			{ flags ^= (1UL << target); }

		// Toggles a given flag (within flags variable)
		inline void setFlag(const Flags &target, const bool &value)
			{ value ? enableFlag(target) : disableFlag(target); }

		// Retrieves a given flag (within flags variable)
		inline bool getFlag(const Flags &target) const
			{ return (flags >> target) & 1U; }

		// Sets gravity to down (default)
		inline void setGravityDown()
			{ setFlag(GRAVITY_SIDE, false); setFlag(GRAVITY_FLIP, false); }

		// Sets gravity to up (upside-down)
		inline void setGravityUp()
			{ setFlag(GRAVITY_SIDE, false); setFlag(GRAVITY_FLIP, true); }

		// Sets gravity to left (default sideways)
		inline void setGravityLeft()
			{ setFlag(GRAVITY_SIDE, true); setFlag(GRAVITY_FLIP, true); }

		// Sets gravity to right (upside-down sideways)
		inline void setGravityRight()
			{ setFlag(GRAVITY_SIDE, true); setFlag(GRAVITY_FLIP, false); }

		short			flags;
		Displays		display;

		Framework		*fw;
		GameController	*game;
};
