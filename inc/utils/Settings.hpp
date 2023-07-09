/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Settings.hpp                       */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Sunday, July 9, 2023 6:17 PM           */
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
