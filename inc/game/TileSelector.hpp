/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - TileSelector.hpp                   */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 10, 2023 7:39 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include "Tile.hpp"
#include <SFML/Graphics.hpp>

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
		TileSelector(const Tile::id_type &id);
		TileSelector(const Tile &tile);
		~TileSelector();

		TileSelector &operator=(const TileSelector &src);
		TileSelector &operator=(const Tile &tile);

		void setTile(const Tile &tile);
		const Tile &getTile() const;

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:

		sf::VertexArray _vertices;
		sf::Texture *_texture;

		Tile _tile;
};
