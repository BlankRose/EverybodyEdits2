/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Configs.hpp                        */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, June 27, 2023 8:02 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Configs
{
			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef nlohmann::json			json_type;
		typedef std::string				path_type;
		typedef uint32_t				key_type;

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		struct graphics
		{
			static uint32_t		framerate;
			static path_type	textures;
			static uint32_t		tilesize;
			private: graphics();
		};

		struct audio
		{
			static float		music;
			static float		sound;
			private: audio();
		};

		struct keybinds
		{
			static key_type		move_left;
			static key_type		move_right;
			static key_type		move_up;
			static key_type		move_down;
			static key_type		exit;
			private: keybinds();
		};

		struct misc
		{
			static path_type	save_file;
			static path_type	log_file;
			static uint32_t		log_level;
			static uint32_t		test_width;
			static uint32_t		test_height;
			private: misc();
		};

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		bool		load_default();
		bool		load_configs(const std::string &path);
		bool		load_configs(const json_type &json);

		bool		save_configs(const std::string &path, const json_type &json);
		bool		save_configs(const std::string &path);
		bool		save_configs(const json_type &json);
		bool		save_configs();

		bool		is_ready();
		json_type	&get_configs();
		json_type	get_default();
}
