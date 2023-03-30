/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Framework.hpp               */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Mar 30 19:59:25 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef FRAMEWORK_HPP
# define FRAMEWORK_HPP

# include <SFML/Graphics.hpp>
# include <string>

class Framework
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef unsigned int		size_type;

		static const std::string	TITLE;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		Framework();
		Framework(const size_type &width, const size_type &height);
		~Framework();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		bool				is_ready() const;
		bool				is_open() const;
		bool				is_focus() const;

		sf::RenderWindow	&get_window() const;
		sf::View			&get_view() const;
		size_type			get_width() const;
		size_type			get_height() const;

		void				set_view(const sf::View &view);

	private:

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		sf::RenderWindow	*_window;
		sf::View			*_view;

		size_type			_width;
		size_type			_height;
};

#endif /* FRAMEWORK_HPP */