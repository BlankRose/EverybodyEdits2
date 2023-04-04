/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - EverybodyEdits2.hpp         */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Tue Apr  4 14:40:26 CEST 2023     */
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

# include <iostream>

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
void		input_handle(sf::RenderWindow &win, sf::Event event);
void		mouse_handle(sf::RenderWindow &win, sf::Event event, World *&map);

#endif /* __EVERYBODY_EDITS_2__ */