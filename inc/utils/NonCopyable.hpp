/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - NonCopyable.hpp                    */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Thursday, June 29, 2023 1:32 PM        */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

/**
 * NonCopyable
 * 
 * Classes inheriting from this class cannot be copied.
 * */
class NonCopyable
{

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

	protected:

		NonCopyable() = default;
		~NonCopyable() = default;

			/** ---------------------- **/
			/*          DELETED         */
			/** ---------------------- **/

	public:

		NonCopyable(const NonCopyable &) = delete;
		NonCopyable &operator=(const NonCopyable &) = delete;

		NonCopyable(NonCopyable &&) = delete;
		NonCopyable &operator=(NonCopyable &&) = delete;
};
