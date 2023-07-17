/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Settings.hpp                       */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 17, 2023 8:36 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

// Toggles debug features
//////////////////////////////

#ifdef DEBUG_MODE
// DEBUG Features Enabled
# define __DEBUG(x) x
# include <chrono>
# define __TIME_INIT \
	std::chrono::steady_clock clock; \
	std::chrono::steady_clock::time_point start, end;
# define __TIME_TEST(label, x) \
	start = clock.now(); \
	x; \
	end = clock.now(); \
	Logging::info(label + std::string(" took ") + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()) + "us");

#else
// DEBUG Features Disabled
# define __DEBUG(x)
# define __TIME_TEST(label, x) x;
# define __TIME_INIT
#endif

// World Settings
//////////////////////////////

#ifndef TILES_PER_BUFFER
// Defines the tiles for the read-write buffer in world loading and saving
# define TILES_PER_BUFFER 1000000
#endif

// Camera Settings
//////////////////////////////

#ifndef SCROLL_PADDING
// Defines how much extra tiles the camera should calculate beyong the view
// (Usually 2 tiles is enough, to cover the tiles that is half off the screen)
# define SCROLL_PADDING 2
#endif

#ifndef TILE_WIDTH
// Defines the width of a tile in pixels
# define TILE_WIDTH 32.f
#endif

#ifndef TILE_HEIGHT
// Defines the height of a tile in pixels
# define TILE_HEIGHT 32.f
#endif

#ifndef SCALE_SELECTOR
// Defines the scale of the tile selector
# define SCALE_SELECTOR 1.5f
#endif

// Player Settings
//////////////////////////////

#ifndef MOVE_SPD_GOD
// Defines the amount of tiles the player moves per frame (while in god mode)
# define MOVE_SPD_GOD .7f
#endif

#ifndef MOVE_SPD_NORMAL
// Defines the amount of tiles the player moves per frame (while walking)
# define MOVE_SPD_NORMAL .5f
#endif

#ifndef MOVE_SPD_FALL
// Defines the amount of tiles the player moves per frame (while falling)
# define MOVE_SPD_FALL 1.f
#endif

// COMPLEX SETTINGS
// (Constructed from other settings)
//////////////////////////////

#ifndef _MOVE_SPD_GOD_WIDTH
// Defines the amount of pixels the player moves per frame (while in god mode)
# define _MOVE_SPD_GOD_WIDTH (MOVE_SPD_GOD * TILE_WIDTH)
#endif

#ifndef _MOVE_SPD_NORMAL_WIDTH
// Defines the amount of pixels the player moves per frame (while walking)
# define _MOVE_SPD_NORMAL_WIDTH (MOVE_SPD_NORMAL * TILE_WIDTH)
#endif

#ifndef _MOVE_SPD_FALL_WIDTH
// Defines the amount of pixels the player moves per frame (while falling)
# define _MOVE_SPD_FALL_WIDTH (MOVE_SPD_FALL * TILE_WIDTH)
#endif

#ifndef _MOVE_SPD_GOD_HEIGHT
// Defines the amount of pixels the player moves per frame (while in god mode)
# define _MOVE_SPD_GOD_HEIGHT (MOVE_SPD_GOD * TILE_HEIGHT)
#endif
