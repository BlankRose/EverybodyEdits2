/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - TileSelector.hpp                   */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 17, 2023 11:16 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include "Tile.hpp"
#include <SFML/Graphics.hpp>

// Defines the maximum slot count for the TileSelector
#define __MAXTILE_SELECTOR_ 10

/**
 * TileSelector
 * 
 * Serves as the game's internal selector, as an interface for the user to
 * select tiles, thus allowing them to place them.
 * */
class TileSelector:
	public sf::Drawable
{
	public:

		TileSelector();
		~TileSelector();

		TileSelector &operator=(const TileSelector &src);

		void setTile(const Tile &tile, const bool &bg = false);
		const Tile &getTile() const;
		const bool &isBackground() const;

		bool interact(const sf::RenderWindow &window);
		const bool &isBackground(const int32_t &index) const;

		void setTile(const int32_t &index, const Tile &tile, const bool &bg = false);
		const Tile &pickTile(const int32_t &index);
		const Tile &getTile(const int32_t &index) const;
		void quickPick(const char *pack, const bool &bg = false);

		void shiftTile();
		void shiftTile(const int32_t &index);
		void shiftAll();

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:

		int _target;
		sf::VertexArray _vertices[__MAXTILE_SELECTOR_ + 1];
		Tile _tile[__MAXTILE_SELECTOR_];
		bool _bg[__MAXTILE_SELECTOR_];
};
