/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Player.cpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Saturday, July 15, 2023 11:11 PM       */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/Player.hpp"

#include "base/Assets.hpp"
#include "utils/Settings.hpp"

using power_type = Player::power_type;
using duration_type = Player::duration_type;
using raw_type = Player::raw_type;

Player::Player():
	_status(0), _player(sf::Quads, 4), _aura(sf::Quads, 4), _buffs(sf::Quads, 0)
{
	// Set the player's vertices
	_player[0].position = sf::Vector2f(0, 0);
	_player[1].position = sf::Vector2f(TILE_WIDTH, 0);
	_player[2].position = sf::Vector2f(TILE_WIDTH, TILE_HEIGHT);
	_player[3].position = sf::Vector2f(0, TILE_HEIGHT);

	// Set the player's texture coordinates
	Assets::size_type size = Assets::get_size();
	_player[0].texCoords = sf::Vector2f(0, 0);
	_player[1].texCoords = sf::Vector2f(size.x, 0);
	_player[2].texCoords = sf::Vector2f(size.x, size.y);
	_player[3].texCoords = sf::Vector2f(0, size.y);

	// Set the player's aura vertices
	const float aura_scale = 1.5f;
	_aura[0].position = sf::Vector2f(-(aura_scale * TILE_WIDTH), -(aura_scale * TILE_HEIGHT));
	_aura[1].position = sf::Vector2f(TILE_WIDTH + (aura_scale * TILE_WIDTH), -(aura_scale * TILE_HEIGHT));
	_aura[2].position = sf::Vector2f(TILE_WIDTH + (aura_scale * TILE_WIDTH), TILE_HEIGHT + (aura_scale * TILE_HEIGHT));
	_aura[3].position = sf::Vector2f(-(aura_scale * TILE_WIDTH), TILE_HEIGHT + (aura_scale * TILE_HEIGHT));

	// Set the player's aura texture coordinates
	size = Assets::get_aurasize();
	_aura[0].texCoords = sf::Vector2f(0, 0);
	_aura[1].texCoords = sf::Vector2f(size.x, 0);
	_aura[2].texCoords = sf::Vector2f(size.x, size.y);
	_aura[3].texCoords = sf::Vector2f(0, size.y);
}

Player::~Player() {}

void Player::toggle_godmode()
{
	if (has_status(Status::GOD))
		remove_status(Status::GOD);
	else
		add_status(Status::GOD, 1, 0);
}

void Player::add_status(const Status &status, const power_type &power, const duration_type &)
{
	// Keep only the 3 bits of the power and sign bit as 4th bit
	// Also keep in bounds of 0x00 to 0x0F (-7 to 7)
	power_type i = power < 0 ? 0x08 : 0x00;
	i |= power >= -0x07 && power <= 0x07 ? power & 0x07 : 0x07;

	// Set the status (clear the 4 bits, then set the 4 bits)
	// (PATTERN: 4 bits for power, if value is 0 then means its disabled)
	_status &= ~(0x0F << status);
	_status |= (i << status);

	// Add the buff icon
	// TODO: Add the buff icon
}

void Player::remove_status(const Status &status)
{
	// Clear the status (clear the 4 bits)
	_status &= ~(0x0F << status);

	// Remove the buff icon
	// TODO: Remove the buff icon
}

void Player::clear_status()
{
	_status = 0x00;
	_buffs.resize(0);
}

bool Player::has_status(const Status &status) const
	{ return (_status & (0x0F << status)) != 0x00; }

power_type Player::get_status_power(const Status &status) const
	{ return (_status & (0x0F << status)) >> status; }

duration_type Player::get_status_duration(const Status &) const
	{ return -1; }

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Draw the player and align to center since view is focused on player
	// (Also draw the aura if the player has the GOD status)
	states.transform.translate(target.getView().getCenter() - sf::Vector2f(TILE_WIDTH / 2, TILE_HEIGHT / 2));
	if (has_status(Status::GOD))
	{
		states.texture = &Assets::get_aura();
		target.draw(_aura, states);
	}
	states.texture = &Assets::get_player();
	target.draw(_player, states);

	// Draw the buffs
	target.draw(_buffs, states);
}
