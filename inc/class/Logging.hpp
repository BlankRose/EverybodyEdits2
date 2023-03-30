/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Logging.hpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Mar 30 14:10:59 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef LOGGING_HPP
# define LOGGING_HPP

# include <string>
namespace Logging
{
			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef const std::string		message_type;
		typedef const unsigned int		level_type;

		const static std::string		DEFAULT_FORMAT = std::string("%TIME% [%LEVEL%] %MSG%");
		const static std::string		STDOUT = std::string("STDOUT");
		const static std::string		STDERR = std::string("STDERR");

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		void		init(const std::string &output = STDOUT, const std::string &format = DEFAULT_FORMAT);
		void		destroy();

			/** ---------------------- **/
			/*         SETTINGS         */
			/** ---------------------- **/

		void		set_output(const std::string &output);

		void		add_level(level_type &level, const std::string &title);
		void		del_level(level_type &level);

			/** ---------------------- **/
			/*          OUTPUT          */
			/** ---------------------- **/

		void		log(level_type &level, message_type &msg);
		void		debug(message_type &msg);
		void		info(message_type &msg);
		void		warn(message_type &msg);
		void		error(message_type &msg);
		void		critical(message_type &msg);
};

#endif /* LOGGING_HPP */