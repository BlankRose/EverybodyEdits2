/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Framework.hpp                      */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, June 27, 2023 9:36 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/**
 * Framework
 * 
 * This class serves as a wrapper for the SFML's basic rendering features.
 * */
class Framework
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef uint32_t			size_type;
		typedef sf::RenderWindow	window_type;
		typedef sf::View			view_type;

		static const std::string	TITLE;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		Framework();
		Framework(const size_type &width, const size_type &height);
		~Framework();

			/** ---------------------- **/
			/*         OVERLOADS        */
			/** ---------------------- **/

		explicit operator bool() const;

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		bool				is_ready() const;
		bool				is_open() const;
		bool				is_focus() const;

		window_type			&get_window() const;
		size_type			get_width() const;
		size_type			get_height() const;
		const view_type		get_view() const;

		void				set_view(const view_type &view);
		void				set_framelimit(const size_type &limit);

			/** ---------------------- **/
			/*          DELETED         */
			/** ---------------------- **/

		Framework(const Framework &) = delete;
		Framework(Framework &&) = delete;

		Framework			&operator=(const Framework &) = delete;
		Framework			&operator=(Framework &&) = delete;

	private:

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		window_type			*_window;
		size_type			_width;
		size_type			_height;
};
