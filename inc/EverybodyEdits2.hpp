/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - EverybodyEdits2.hpp         */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Apr  6 19:38:00 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef __EVERYBODY_EDITS_2__
# define __EVERYBODY_EDITS_2__

	/** ---------------------- **/
	/*         INCLUDES         */
	/** ---------------------- **/

# include "core/generic.hpp"
# include "core/more_types.hpp"

# include "class/Context.hpp"
# include "class/Configs.hpp"
# include "class/Framework.hpp"
# include "class/Logging.hpp"

# include "class/Assets.hpp"
# include "class/MapChunk.hpp"
# include "class/World.hpp"
# include "class/Interface.hpp"

# include <SFML/System.hpp>
# include <iostream>

	/** ---------------------- **/
	/*         FUNCTIONS        */
	/** ---------------------- **/

bool		configure(const std::string &path);
bool		get_ready(Context *&ctx);
void		unload(Context *&ctx);

void		threads_unit(Context *&ctx);
void		event_unit(Context *&ctx);
void		logic_unit(Context *&ctx);
void		draws_unit(Context *&ctx);

#endif /* __EVERYBODY_EDITS_2__ */