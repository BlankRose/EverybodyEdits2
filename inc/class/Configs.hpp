/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Configs.hpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Sun Apr  2 19:32:46 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef CONFIGS_HPP
# define CONFIGS_HPP

# include <nlohmann/json_fwd.hpp>

namespace Configs
{
			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		typedef nlohmann::json			json_type;
		typedef uint32_t				key_type;

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		namespace graphics
		{
			static std::string	textures;
		}

		namespace audio
		{
			static float		music;
			static float		sound;
		}

		namespace keybinds
		{
			static key_type		move_left;
			static key_type		move_right;
			static key_type		move_up;
			static key_type		move_down;
			static key_type		exit;
		}

		namespace misc
		{
			static std::string	log_file;
			static uint32_t		log_level;
		}

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

#endif /* CONFIGS_HPP */