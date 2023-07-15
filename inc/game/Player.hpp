/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Player.hpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Saturday, July 15, 2023 9:56 PM        */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include <SFML/Graphics.hpp>

/**
 * Player
 * 
 * Handles the player's position, status, and rendering.
 * */
class Player:
	public sf::Drawable
{
	public:

		typedef int8_t power_type;
		typedef uint32_t duration_type;
		typedef uint32_t raw_type;
		typedef sf::Vector2f acceleration_type;

		Player();
		~Player();

		enum Status {
			GOD = 0x00,
			GRAVITRON = 0x04,
			SPEED = 0x08,
			JUMP = 0x0C,
		};

		void toggle_godmode();

		void add_status(const Status &status, const power_type &power = 1, const duration_type &duration = -1);
		void remove_status(const Status &status);
		void clear_status();

		bool has_status(const Status &status) const;
		power_type get_status_power(const Status &status) const;
		duration_type get_status_duration(const Status &status) const;

		void set_acceleration(const float &x, const float &y);
		void apply_acceleration(const float &x, const float &y);
		const acceleration_type &get_acceleration() const;

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:

		acceleration_type _acceleration; // The player's acceleration
		uint32_t _status; // Raw status data (4 bits per status) (Total Status: 8)
		sf::VertexArray _player; // The player's body vertices
		sf::VertexArray _aura; // The player's aura vertices (Only if GOD status is active)
		sf::VertexArray _buffs; // The player's buffs icons
};
