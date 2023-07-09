/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Camera.cpp                         */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Sunday, July 9, 2023 5:52 PM           */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/Camera.hpp"
#include "utils/Settings.hpp"
#include "base/Assets.hpp"

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

/**
 * View Constructor: Initializes the camera, using the given view
 * 
 * @param	view: The view to use
 * */
Camera::Camera(const sf::View &view)
	{ redefine(view); }

/**
 * Destructor: Destroys the camera
 * */
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

	/** ---------------------- **/
	/*          MOVING          */
	/** ---------------------- **/

/**
 * Move the camera towards the new view.
 * It cycles the vertices, moving the farthest ones to the front of the queue,
 * using move semantics to avoid copying the vertices, and then recalculates
 * the position of the vertices whose position has changed.
 * 
 * @param	view: The new view to move to
 * */
void Camera::move(const sf::View &view)
{
	// Retrieve the coordinates of tiles on the very edge of the view still
	// visible, even if they are only partially visible.
	sf::Vector2f	center = view.getCenter();
	sf::Vector2f	size = view.getSize();
	sf::FloatRect	origin(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);

	// (Back to front when moving left, front to back when moving right)
	// (Top to bottom when moving up, bottom to top when moving down)

	// STEP A: Calculate shift amount and direction
	// (The amount of tiles to shift by)
	int32_t
		// The amount of tiles to shift on the x-axis
		sx = (origin.left / TILE_WIDTH) - _current.left,
		// The amount of tiles to shift on the y-axis
		sy = (origin.top / TILE_HEIGHT) - _current.top;

	// If there's too much to shift or the size of the view has changed,
	// recalculate the entire view. Shifting would be too much costly.
	if (abs(sx) > abs(_current.width / 2)
		|| abs(sy) > abs(_current.height / 2)
		|| (int) (size.x / TILE_WIDTH + 1) != _current.width
		|| (int) (size.y / TILE_HEIGHT + 1) != _current.height)
	{
		redefine(view);
		return;
	}

	// Skips the rest of the function if there is no need to shift at all
	if (sx == 0 && sy == 0)
		return;
	_current.left += sx;
	_current.top += sy;

	// STEP C: Shift the vertices on the x-axis
	if (sx > 0)
		// Shift the vertices on the x-axis to the right
		for (size_type x = 0; x < sx; ++x)
		{
			// Move the vertices on the x-axis
			_fg_vertices.push_back(std::move(_fg_vertices.front()));
			_fg_vertices.pop_front();

			// Calculate the x position of the tile
			float x_align = (_current.left + _current.width - 1) * TILE_WIDTH;

			// Update the position of the vertices on the x-axis
			for (size_type y = 0; y < _current.height; ++y)
			{
				// Get the vertex array of the current tile
				sf::VertexArray &va = _fg_vertices.back()[y];

				// Update the position of each vertex
				va[0].position.x = x_align;
				va[1].position.x = x_align + TILE_WIDTH;
				va[2].position.x = x_align + TILE_WIDTH;
				va[3].position.x = x_align;
			}
		}
	else if (sx < 0)
		// Shift the vertices on the x-axis to the left
		for (size_type x = 0; x < -sx; ++x)
		{
			// Move the vertices on the x-axis
			_fg_vertices.push_front(std::move(_fg_vertices.back()));
			_fg_vertices.pop_back();

			// Calculate the x position of the tile
			float x_align = _current.left * TILE_WIDTH;

			// Update the position of the vertices on the x-axis
			for (size_type y = 0; y < _current.height; ++y)
			{
				// Get the vertex array of the current tile
				sf::VertexArray &va = _fg_vertices.front()[y];

				// Update the position of each vertex
				va[0].position.x = x_align;
				va[1].position.x = x_align + TILE_WIDTH;
				va[2].position.x = x_align + TILE_WIDTH;
				va[3].position.x = x_align;
			}
		}

	// STEP D: Shift the vertices on the y-axis
	if (sy > 0)
		// Shift the vertices on the y-axis down
		for (size_type y = 0; y < sy; ++y)
		{
			// Move the vertices on the y-axis
			for (auto &fgx : _fg_vertices)
			{
				fgx.push_back(std::move(fgx.front()));
				fgx.pop_front();
			}

			// Calculate the y position of the tile
			float y_align = (_current.top + _current.height - 1) * TILE_HEIGHT;

			// Update the position of the vertices on the y-axis
			for (size_type x = 0; x < _current.width; ++x)
			{
				// Get the vertex array of the current tile
				sf::VertexArray &va = _fg_vertices[x].back();

				// Update the position of each vertex
				va[0].position.y = y_align;
				va[1].position.y = y_align;
				va[2].position.y = y_align + TILE_HEIGHT;
				va[3].position.y = y_align + TILE_HEIGHT;
			}
		}
	else if (sy < 0)
		// Shift the vertices on the y-axis
		for (size_type y = 0; y < -sy; ++y)
		{
			// Move the vertices on the y-axis up
			for (auto &fgx : _fg_vertices)
			{
				fgx.push_front(std::move(fgx.back()));
				fgx.pop_back();
			}

			// Calculate the y position of the tile
			float y_align = _current.top * TILE_HEIGHT;

			// Update the position of the vertices on the y-axis
			for (size_type x = 0; x < _current.width; ++x)
			{
				// Get the vertex array of the current tile
				sf::VertexArray &va = _fg_vertices[x].front();

				// Update the position of each vertex
				va[0].position.y = y_align;
				va[1].position.y = y_align;
				va[2].position.y = y_align + TILE_HEIGHT;
				va[3].position.y = y_align + TILE_HEIGHT;
			}
		}
}

/**
 * Recreates the vertices from scratch from a given view.
 * (Might be useful when the camera is far away from the old view, where
 * moving the vertices would be more expensive than recreating them)
 * 
 * @param	view: The new view to move to
 * */
void Camera::redefine(const sf::View &view)
{
	// Retrieve the coordinates of tiles on the very edge of the view still
	// visible, even if they are only partially visible.
	sf::Vector2f	center = view.getCenter();
	sf::Vector2f	size = view.getSize();
	sf::FloatRect	origin(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);

	_current = scale_type(
		origin.left / TILE_WIDTH,
		origin.top / TILE_HEIGHT,
		origin.width / TILE_WIDTH + 1,
		origin.height / TILE_HEIGHT + 1
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

	/** ---------------------- **/
	/*          DRAWING         */
	/** ---------------------- **/

/**
 * Defines the world that the camera is referencing to.
 * 
 * @param	world: The world that the camera is referencing to.
 * */
void Camera::setReference(World *world)
	{ _reference = world; }

/**
 * Draws the world that the camera is referencing to on the target.
 * It will uses the reference world to retrieve which assets it needs to draw
 * according to the given tile indices.
 * 
 * @param	target: The target to draw on.
 * @param	states: The states to draw with.
 * */
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

	// Skips the first tiles if negative, for iterators
	ptrdiff_t
		ix = _current.left < 0 ? -_current.left : 0,
		iy = _current.top < 0 ? -_current.top : 0;

	// Draw the vertices
	auto fgx = _fg_vertices.begin() + ix;
	for (uint32_t x = sx; x < ex; ++x, ++fgx)
	{
		auto fgy = fgx->begin() + iy;
		for (uint32_t y = sy ; y < ey; ++y, ++fgy)
		{
			states.texture = &Assets::get_texture(
				_reference->get_fg_tile(x, y).get_id());
			target.draw(*fgy, states);

			//states.texture = &Assets::get_texture(
			//	_reference->get_bg_tile(sx, sy).get_id());
			//target.draw(*bgy, states);
		}
	}
}
