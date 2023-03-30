/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Logging.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Mar 30 14:34:59 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/Logging.hpp"

#include <map>
#include <iostream>
#include <fstream>
#include <chrono>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

typedef void (*printer_type)(const std::string &);
static std::map<std::string, printer_type> _format_map;

static std::string		_target = Logging::STDOUT;
static std::string		_format = Logging::DEFAULT_FORMAT;
static std::ofstream	_file;

	/** ---------------------- **/
	/*      PRIVATE METHODS     */
	/** ---------------------- **/

static bool		check_format(const std::string &format)
{
	// BASIC VERIFICATION
	if (format.empty())
	{
		std::cerr << "Warning: Format for logging cannot be empty!" << std::endl;
		return false;
	}
	else if(format == Logging::DEFAULT_FORMAT)
		return true;

	// DEEP VERIFICATION
	for (std::string::size_type i = format.find('%', 0), j = 0; format[i]; i = ++j)
	{
		// STEP A: Verify if no more % is encountered
		if (i == format.npos)
			i = format.length();
		if (!format[i])
			return true;

		// STEP B: Verify if the previous % is closed
		j = format.find('%', ++i);
		if (j == format.npos)
			j = format.length();
		if (!format[j])
		{
			std::cerr << "Warning: '%' is not closed in the given format: \"" << format << "\" (at position " << i << ")" << std::endl;
			return false;
		}

		// STEP C: Verify if the content is valid
		std::string tmp = format.substr(i, j - i);
	}
	return true;
}

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

void	Logging::init(const std::string &output, const std::string &format)
{

	_target = output;
	if (output != STDOUT && output != STDERR)
	{
		if (_file.is_open())
			_file.close();
		_file.open(output);
		if (!_file.is_open())
		{
			std::cerr << "Warning: Couldn't open file " << output << " for logging!" << std::endl;
			_target = STDOUT;
		}
	}
	else if (_file.is_open())
		_file.close();

	if (check_format(format))
		_format = format;
	else
		_format = DEFAULT_FORMAT;
}

void	Logging::destroy()
{
	if (_file.is_open())
		_file.close();
}

	/** ---------------------- **/
	/*         SETTINGS         */
	/** ---------------------- **/

// void	Logging::set_output(const std::string &output)
// 	{}

// void	Logging::add_level(level_type &level, const std::string &title)
// 	{}

// void	Logging::del_level(level_type &level)
// 	{}

	/** ---------------------- **/
	/*          OUTPUT          */
	/** ---------------------- **/

void	Logging::log(level_type &, message_type &msg)
{
	if (msg.empty())
		return;
}

void	Logging::debug(message_type &msg)
	{ Logging::log(10, msg); }

void	Logging::info(message_type &msg)
	{ Logging::log(20, msg); }

void	Logging::warn(message_type &msg)
	{ Logging::log(30, msg); }

void	Logging::error(message_type &msg)
	{ Logging::log(40, msg); }

void	Logging::critical(message_type &msg)
	{ Logging::log(50, msg); }
