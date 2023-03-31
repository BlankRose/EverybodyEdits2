/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Logging.hpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Mar 30 17:29:07 CEST 2023     */
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
		typedef unsigned int			level_type;

		const static std::string		DEFAULT_FORMAT = std::string("%TIME% [%LEVEL%] %MSG%");
		const static std::string		DEFAULT_TIME_FORMAT = std::string("%d-%m-%Y %H:%M:%S");
		const static std::string		STDOUT = std::string("STDOUT");
		const static std::string		STDERR = std::string("STDERR");

		const static level_type			DEBUG = 10;
		const static level_type			INFO = 20;
		const static level_type			WARN = 30;
		const static level_type			ERROR = 40;
		const static level_type			CRITICAL = 50;
		const static level_type			FATAL = 60;

			/** ---------------------- **/
			/*         SETTINGS         */
			/** ---------------------- **/

		void		init(const std::string &output = STDOUT,
						const level_type &minimum_level = DEBUG,
						const std::string &format = DEFAULT_FORMAT,
						const std::string &time_format = DEFAULT_TIME_FORMAT);
		void		reset();

		void		set_output(const std::string &output);
		void		set_format(const std::string &format);
		void		set_minimum_level(const level_type &level);
		void		set_time_format(const std::string &time_format);

		void		add_level(const level_type &level, const std::string &title);
		void		del_level(const level_type &level);

			/** ---------------------- **/
			/*          OUTPUT          */
			/** ---------------------- **/

		void		log(const level_type &level, message_type &msg);
		void		debug(message_type &msg);
		void		info(message_type &msg);
		void		warn(message_type &msg);
		void		error(message_type &msg);
		void		critical(message_type &msg);
		void		fatal(message_type &msg);
}

#endif /* LOGGING_HPP */