/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - EverybodyEdits2.hpp         */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Sun Apr  2 20:35:58 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef __EVERYBODY_EDITS_2__
# define __EVERYBODY_EDITS_2__

	/** ---------------------- **/
	/*         INCLUDES         */
	/** ---------------------- **/

# include "core/generic.hpp"
# include "core/more_types.hpp"

# include "class/Configs.hpp"
# include "class/Framework.hpp"
# include "class/Logging.hpp"

# include "class/Assets.hpp"
# include "class/MapChunk.hpp"
# include "class/TileMap.hpp"

	/** ---------------------- **/
	/*         SETUP.CPP        */
	/** ---------------------- **/

bool		configure(const std::string &path);
bool		get_ready(Framework *&fw, TileMap *&map);
void		unload(Framework *&fw, TileMap *&map);

	/** ---------------------- **/
	/*        DRAWING.CPP       */
	/** ---------------------- **/

void		draw_loop(Framework *&fw, TileMap *&map);

#endif /* __EVERYBODY_EDITS_2__ */