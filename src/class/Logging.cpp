/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Logging.cpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, June 27, 2023 7:57 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "class/Logging.hpp"

#include <map>
#include <ctime>

#include <iomanip>
#include <iostream>
#include <fstream>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using level_type = Logging::level_type;
using message_type = Logging::message_type;

typedef void (*printer_type)(const std::string &msg, const level_type &level);
typedef std::map<level_type, std::string>		level_map;
typedef std::map<std::string, printer_type>		format_map;
typedef level_map::value_type					level_pair;
typedef format_map::value_type					format_pair;

static level_map		_level_map;
static format_map		_format_map;
static std::ofstream	_file;

static level_type		_level_min = 0;
static std::string		_target = Logging::STDOUT;
static std::string		_format = Logging::DEFAULT_FORMAT;
static std::string		_time_format = Logging::DEFAULT_TIME_FORMAT;

	/** ---------------------- **/
	/*      PRIVATE METHODS     */
	/** ---------------------- **/

static void		print_message(const std::string &msg, const level_type &)
{
	if (_file.is_open())
		_file << msg;
	else if (_target == Logging::STDERR)
		std::cerr << msg;
	else
		std::cout << msg;
}

static void		print_level(const std::string &, const level_type &level)
{
	std::string		value;
	if (_level_map.find(level) != _level_map.end())
		value = _level_map.at(level);
	print_message(value, level);
}

static void		print_time(const std::string &, const level_type &)
{
	time_t	time = std::time(nullptr);
	tm		tz = *std::localtime(&time);
	auto	out = std::put_time(&tz, _time_format.c_str());

	if (_file.is_open())
		_file << out;
	else if (_target == Logging::STDERR)
		std::cerr << out;
	else
		std::cout << out;
}

static void		first_init()
{
	// PREVENT REDO
	static bool		is_ready = false;
	if (is_ready) return;
	is_ready = true;

	// PREPARE FORMAT MAPPING
	_format_map.insert(format_pair("TIME", print_time));
	_format_map.insert(format_pair("LEVEL", print_level));
	_format_map.insert(format_pair("LVL", print_level));
	_format_map.insert(format_pair("MESSAGE", print_message));
	_format_map.insert(format_pair("MSG", print_message));

	// PREPARE LEVEL MAPPING
	_level_map.insert(level_pair(Logging::DEBUG, "DEBUG"));
	_level_map.insert(level_pair(Logging::INFO, "INFO"));
	_level_map.insert(level_pair(Logging::WARN, "WARN"));
	_level_map.insert(level_pair(Logging::ERROR, "ERROR"));
	_level_map.insert(level_pair(Logging::CRITICAL, "CRITICAL"));
	_level_map.insert(level_pair(Logging::FATAL, "FATAL"));
}

static bool		check_format(const std::string &format)
{
	first_init();

	// BASIC VERIFICATION
	if (format.empty() || format.find_first_not_of("\t\n\v\f\r ") == format.npos)
	{
		std::cerr << "Warning: Format for logging cannot be empty!" << std::endl;
		return false;
	}

	// DEEP VERIFICATION
	for (std::string::size_type i = 0, j = 0; format[i]; i = ++j)
	{
		// STEP A: Verify if no more % is encountered
		i = format.find('%', i);
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
			std::cerr << "Warning: '%' is not closed in the given format: \"" << format << "\" (at position " << i - 1 << ")" << std::endl;
			return false;
		}

		// STEP C: Verify if the content is valid
		std::string tmp = format.substr(i, j - i);
		if (_format_map.find(tmp) == _format_map.end())
		{
			std::cerr << "Warning: '" << tmp << "' is not valid in the given format: \"" << format << "\" (at position " << i << ")" << std::endl;
			return false;
		}
	}
	return true;
}

	/** ---------------------- **/
	/*         SETTINGS         */
	/** ---------------------- **/

void	Logging::init(
	const std::string &output, const level_type &minimum_level,
	const std::string &format, const std::string &time_format)
{
	set_output(output);
	set_format(format);
	set_minimum_level(minimum_level);
	set_time_format(time_format);
}

void	Logging::reset()
{
	_format = DEFAULT_FORMAT;
	_target = STDOUT;
	if (_file.is_open())
		_file.close();
}

void	Logging::set_output(const std::string &output)
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
}

void	Logging::set_format(const std::string &format)
{
	if (check_format(format))
		_format = format;
	else
		_format = DEFAULT_FORMAT;
}

void	Logging::set_minimum_level(const level_type &level)
	{ _level_min = level; }

void	Logging::set_time_format(const std::string &time_format)
{
	if (time_format.empty() || time_format.find_first_not_of("\t\n\v\f\r ") == time_format.npos)
	{
		std::cerr << "Warning: Cannot set empty time format!" << std::endl;
		_time_format = Logging::DEFAULT_TIME_FORMAT;
	}
	else
		_time_format = time_format;
}

void	Logging::add_level(const level_type &level, const std::string &title)
{
	first_init();

	if (_level_map.find(level) != _level_map.end())
		std::cerr << "Warning: Trying to add level " << level << " for logging but it is already defined!" << std::endl;
	else if (title.empty() || title.find_first_not_of("\t\n\v\f\r ") == title.npos)
		std::cerr << "Warning: Trying to add level " << level << " but the title is empty!" << std::endl;
	else
		_level_map.insert(level_pair(level, title));
}

void	Logging::set_level(const level_type &level, const std::string &title)
{
	first_init();

	if (_level_map.find(level) == _level_map.end())
		std::cerr << "Warning: Trying to modify level " << level << " but it does not exists!" << std::endl;
	else if (title.empty() || title.find_first_not_of("\t\n\v\f\r ") == title.npos)
		std::cerr << "Warning: Trying to modify level " << level << " but the new title is empty!" << std::endl;
	else
		_level_map.at(level) = title;
}

void	Logging::del_level(const level_type &level)
{
	if (level == DEBUG || level == INFO || level == WARN
		|| level == ERROR || level == CRITICAL || level == FATAL)
		std::cerr << "Warning: Cannot remove level " << level << " for logging since it is a system implementated level!" << std::endl;
	else if (_level_map.find(level) == _level_map.end())
		std::cerr << "Warning: Trying to remove level " << level << " but it does not exists (yet)!" << std::endl;
	else
		_level_map.erase(_level_map.find(level));
}

	/** ---------------------- **/
	/*          OUTPUT          */
	/** ---------------------- **/

void	Logging::log(const level_type &level, message_type &msg)
{
	if (msg.empty() || level < _level_min)
		return;
	first_init();

	for (std::string::size_type i = 0, j = 0;; i = ++j)
	{
		j = _format.find('%', i);
		if (j != _format.npos)
			print_message(_format.substr(i, j - i), level);
		else
		{
			print_message(_format.substr(i, _format.length() - i) + "\n", level);
			return;
		}

		i = j + 1;
		j = _format.find('%', i);
		if (j == _format.npos)
			j = _format.length();
		_format_map.at(_format.substr(i, j - i))(msg, level);
	}
}

void	Logging::debug(message_type &msg)
	{ Logging::log(DEBUG, msg); }

void	Logging::info(message_type &msg)
	{ Logging::log(INFO, msg); }

void	Logging::warn(message_type &msg)
	{ Logging::log(WARN, msg); }

void	Logging::error(message_type &msg)
	{ Logging::log(ERROR, msg); }

void	Logging::critical(message_type &msg)
	{ Logging::log(CRITICAL, msg); }

void	Logging::fatal(message_type &msg)
	{ Logging::log(FATAL, msg); }
