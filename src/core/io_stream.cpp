/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - io_stream.cpp               */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Wed Mar 29 18:40:54 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "core/generic.hpp"
#include "core/more_types.hpp"

#define CASE(reason, msg)\
	case reason:\
		std::cout << msg;\
		break;

#define DEFAULT(msg)\
	default:\
		std::cout << msg;\
		break;

void	print_error(const err_code &err_code, const std::string &context, const bool &quit)
{
	switch (err_code)
	{
		CASE(ALLOC_FAILURE, "Memory allocation failed")
		DEFAULT("An unknown error occured")
	}
	if (context.empty())
		std::cout << ": " << context << std::endl;
	else
		std::cout << "!" << std::endl;
	if (quit)
	{
		std::cout << "System Aborting..." << std::endl;
		exit(err_code);
	}
}