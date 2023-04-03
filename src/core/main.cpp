/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - main.cpp                    */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Sun Apr  2 21:06:10 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "EverybodyEdits2.hpp"

/**
 * EVERYBODY EDITS 2
 * 
 * A game that revolves around sandbox features
 * inside of a 2D tiled world with online features
 * and the ability of being cross-plateform!
 * 
 * It is originally a flash game which had died
 * with the end of flash support by Adobe themself.
 * 
 * LICENSE: MIT License
 * */
int main(int, char *[], char *[])
{
	Framework	*fw;
	World		*map;

	if (!configure("configs/settings.json")
		|| !get_ready(fw, map))
		return FAILURE;
	draw_loop(fw, map);

	unload(fw, map);
	Configs::save_configs();
	Logging::info("Software ended!");

	return SUCCESS;
}
