/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - WorldSelector.hpp                  */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 10, 2023 7:45 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include <filesystem>
#include <SFML/Graphics.hpp>

/**
 * WorldSelector
 * 
 * Serves as an interface for the user to select worlds, and also to create
 * newly named worlds.
 * */
class WorldSelector:
	public sf::Drawable
{
	public:

		WorldSelector();
		~WorldSelector();

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:

		sf::VertexArray _vertices;
		sf::Texture *_texture;
};
