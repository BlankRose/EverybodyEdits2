/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - CommonTiles.hpp                    */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Saturday, July 15, 2023 11:52 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

// Empty tile ID, where no tile is present
#define _TILEID_EMPTY Tile::id_type(0)

// Spawn tile ID, designing which tile is the spawn where players will spawn
// when they join the world (picked randonmly if multiple spawn tiles are present)
#define _TILEID_SPAWN 1

// Gravity tile ID, which enforce a gravity direction on players (Left)
#define _TILEID_LEFT 2

// Gravity tile ID, which enforce a gravity direction on players (Up)
#define _TILEID_UP 3

// Gravity tile ID, which enforce a gravity direction on players (Right)
#define _TILEID_RIGHT 4

// Gravity tile ID, which enforce a gravity direction on players (Down)
#define _TILEID_DOWN 5

// Selection tile ID, which is not a tile itself but rather a decorative box
// around a tile, used to show which tile is selected
#define _TILEID_SELECTION 65535

// Default tile ID, used as first pick and new worlds borders
#define _TILEID_DEFAULT 11
