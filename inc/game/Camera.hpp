/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Camera.hpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Sunday, July 9, 2023 5:32 PM           */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#pragma once

#include <deque>
#include <SFML/Graphics.hpp>
#include "World.hpp"

/**
 * Camera
 * << MVC (Game's View) >>
 * 
 * Handles the camera, using a scrolling style for rendering.
 * Far tiles are moved to the front of the queue, and are recalculated
 * thus keeping only the visible tiles in the queue and without having to
 * recalculate the entire view every frame.
 * */
class Camera:
	public sf::Drawable
{

	Camera() = delete;
	public:

		typedef World::size_type size_type;
		typedef std::deque<std::deque<sf::VertexArray>> vertices_type;
		typedef sf::Rect<int32_t> scale_type;

		Camera(const sf::View &view);
		~Camera();

		void move(const sf::View &view);
		void redefine(const sf::View &view);

		void setReference(World *world);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:

		vertices_type _fg_vertices; // The vertices to draw
		scale_type _current; // The current view position, relative to the world
		World *_reference; // The world to use as reference

};
