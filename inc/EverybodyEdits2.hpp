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
# include "class/Interface.hpp"

# include <iostream>

	/** ---------------------- **/
	/*          CONTEXT         */
	/** ---------------------- **/

struct Context
{
	Context();
	Context(const Context &other);
	~Context();

	Context		&operator=(const Context &other);

	bool	up, down, right, left;
	bool	mouse_L, mouse_R, mouse_M;

	Framework	*fw;
	World		*map;
	Interface	*ui;
};

	/** ---------------------- **/
	/*         FUNCTIONS        */
	/** ---------------------- **/

bool		configure(const std::string &path);
bool		get_ready(Context *&ctx);
void		unload(Context *&ctx);

void		draw_loop(Context *&ctx);
void		event_cycle(Context *&ctx);

#endif /* __EVERYBODY_EDITS_2__ */