/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - EverybodyEdits2.hpp         */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Mon Apr  3 14:55:53 CEST 2023     */
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
# include "class/World.hpp"

	/** ---------------------- **/
	/*         SETUP.CPP        */
	/** ---------------------- **/

bool		configure(const std::string &path);
bool		get_ready(Framework *&fw, World *&map);
void		unload(Framework *&fw, World *&map);

	/** ---------------------- **/
	/*        DRAWING.CPP       */
	/** ---------------------- **/

void		draw_loop(Framework *&fw, World *&map);

#endif /* __EVERYBODY_EDITS_2__ */