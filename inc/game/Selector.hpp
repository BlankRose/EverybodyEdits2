/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Selector.hpp                       */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 10, 2023 12:49 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include "Tile.hpp"
#include <SFML/Graphics.hpp>

/**
 * Selector
 * 
 * Serves as the game's internal selector, as an interface for the user to
 * select tiles, thus allowing them to place them.
 * */
class Selector:
	public sf::Drawable
{
	public:

		Selector();
		Selector(const Tile::id_type &id);
		Selector(const Tile &tile);
		~Selector();

		Selector &operator=(const Selector &src);
		Selector &operator=(const Tile &tile);

		void setTile(const Tile &tile);
		const Tile &getTile() const;

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:

		sf::VertexArray _vertices;
		sf::Texture *_texture;

		Tile _tile;
};
