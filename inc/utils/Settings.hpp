/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Settings.hpp                       */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Wednesday, July 5, 2023 6:59 PM        */
/*      ||  '-'                                                               */
/* ************************************************************************** */

// Toggles debug features
//////////////////////////////

#ifdef DEBUG
// DEBUG Features Enabled
# define __DEBUG(x) x
#else
// DEBUG Features Disabled
# define __DEBUG(x)
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
