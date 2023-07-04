/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Camera.cpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Tuesday, July 4, 2023 10:01 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/Camera.hpp"
#include "utils/Settings.hpp"
#include "base/Assets.hpp"

Camera::Camera(const sf::View &view)
{
	// Retrieve the coordinates of tiles on the very edge of the view still
	// visible, even if they are only partially visible.
	sf::Vector2f	center = view.getCenter();
	sf::Vector2f	size = view.getSize();
	sf::FloatRect	origin(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);

	_current = scale_type(
		origin.left / TILE_WIDTH,
		origin.top / TILE_HEIGHT,
		origin.width / TILE_WIDTH,
		origin.height / TILE_HEIGHT
	);

	// Resize the vertices array to fit the view
	_fg_vertices.resize(_current.width);
	auto fgx = _fg_vertices.begin();
	Assets::size_type texture_size = Assets::get_size();
	for (size_type x = 0; x < _current.width; ++x, ++fgx)
	{
		fgx->resize(_current.height);
		auto fgy = fgx->begin();
		for (size_type y = 0; y < _current.height; ++y, ++fgy) {

			// Create and assign the vertex array of each tiles
			*fgy = sf::VertexArray(sf::Quads, 4);
			sf::VertexArray &va = *fgy;

			// Set the position of each vertex at the position relative to the view
			va[0].position = sf::Vector2f(x * TILE_WIDTH, y * TILE_HEIGHT); // Top Left
			va[1].position = sf::Vector2f((x + 1) * TILE_WIDTH, y * TILE_HEIGHT); // Top Right
			va[2].position = sf::Vector2f((x + 1) * TILE_WIDTH, (y + 1) * TILE_HEIGHT); // Bottom Right
			va[3].position = sf::Vector2f(x * TILE_WIDTH, (y + 1) * TILE_HEIGHT); // Bottom Left

			// Set the texture coordinates of each vertex
			va[0].texCoords = sf::Vector2f(0, 0); // Top Left
			va[1].texCoords = sf::Vector2f(texture_size.x, 0); // Top Right
			va[2].texCoords = sf::Vector2f(texture_size.x, texture_size.y); // Bottom Right
			va[3].texCoords = sf::Vector2f(0, texture_size.y); // Bottom Left
		}
	}
}

Camera::~Camera()
{
	for (auto &fgx : _fg_vertices)
	{
		for (auto &fgy : fgx)
			fgy.clear();
		fgx.clear();
	}
	_fg_vertices.clear();
}

/**
 * Move the camera by the given offset.
 * It cycles the vertices, moving the farthest ones to the front of the queue,
 * using move semantics to avoid copying the vertices, and then recalculates
 * the position of the vertices whose position has changed.
 * 
 * @param	offset: The offset to move the camera by.
 * */
void Camera::move(const sf::Vector2f &offset)
{
	// TODO: Implement this later
	(void) offset;
}

void Camera::setReference(World *world)
	{ _reference = world; }

void Camera::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Get the actual start and end loop indices
	// (Also prevents the loop from going out of bounds)
	uint32_t
		// The start and end indices of the x-axis
		sx = _current.left < 0 ? 0 : _current.left,
		ex = _current.left + _current.width > _reference->get_width() ?
			_reference->get_width() : _current.left + _current.width,
		// The start and end indices of the y-axis
		sy = _current.top < 0 ? 0 : _current.top,
		ey = _current.top + _current.height > _reference->get_height() ?
			_reference->get_height() : _current.top + _current.height;

	// Draw the vertices
	auto fgx = _fg_vertices.begin();
	for (uint32_t x = sx; x < ex; ++x, ++fgx)
	{
		auto fgy = fgx->begin();
		for (uint32_t y = sy ; y < ey; ++y, ++fgy)
		{
			states.texture = &Assets::get_texture(
				_reference->get_fg_tile(x, y).get_id());;
			target.draw(*fgy, states);

			//states.texture = &Assets::get_texture(
			//	_reference->get_bg_tile(sx, sy).get_id());
			//target.draw(*bgy, states);
		}
	}
}
