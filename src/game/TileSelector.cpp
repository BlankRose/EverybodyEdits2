/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - TileSelector.cpp                   */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 17, 2023 11:27 PM         */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/TileSelector.hpp"
#include "utils/CommonTiles.hpp"
#include "utils/Settings.hpp"
#include "base/Assets.hpp"

TileSelector::TileSelector():
	_target(0)
{
	for (int i = 0; i < __MAXTILE_SELECTOR_ + 1; i++)
	{
		_vertices[i] = sf::VertexArray(sf::Quads, 4);

		_vertices[i][0].position = sf::Vector2f(i * (TILE_WIDTH * SCALE_SELECTOR), 0);
		_vertices[i][1].position = sf::Vector2f((i + 1) * (TILE_WIDTH * SCALE_SELECTOR), 0);
		_vertices[i][2].position = sf::Vector2f((i + 1) * (TILE_WIDTH * SCALE_SELECTOR), (TILE_HEIGHT * SCALE_SELECTOR));
		_vertices[i][3].position = sf::Vector2f(i * (TILE_WIDTH * SCALE_SELECTOR), (TILE_HEIGHT * SCALE_SELECTOR));

		Assets::size_type texSize = Assets::get_size();
		_vertices[i][0].texCoords = sf::Vector2f(0, 0);
		_vertices[i][1].texCoords = sf::Vector2f(texSize.x, 0);
		_vertices[i][2].texCoords = sf::Vector2f(texSize.x, texSize.y);
		_vertices[i][3].texCoords = sf::Vector2f(0, texSize.y);

		if (i < __MAXTILE_SELECTOR_)
		{
			_tile[i] = Tile(i + 10);
			_bg[i] = false;
		}
	}
}

TileSelector::~TileSelector() {}

TileSelector &TileSelector::operator=(const TileSelector &src)
{
	for (int i = 0; i < __MAXTILE_SELECTOR_; i++)
	{
		_tile[i] = src._tile[i];
		_bg[i] = src._bg[i];
	}
	return *this;
}

void TileSelector::setTile(const Tile &tile, const bool &bg)
{
	// If already in the selector, then just change the tile.
	for (int i = 0; i < __MAXTILE_SELECTOR_; i++)
		if (_tile[i] == tile && _bg[i] == bg)
		{
			_target = i;
			return;
		}

	_tile[_target] = tile;
	_bg[_target] = bg;
}

const Tile &TileSelector::getTile() const
	{ return _tile[_target]; }

const bool &TileSelector::isBackground() const
	{ return _bg[_target]; }

/**
 * Quickly pick a given pack of tiles and set them to the selector.
 * If the pack is too big, it will only pick the first __MAXTILE_SELECTOR_ tiles.
 * If the pack is too small, it will leave the remaining tiles as they are.
 * 
 * @param	pack: The pack of tiles to pick from.
 * @param	bg: Whether or not the tiles are background tiles.
 * */
void TileSelector::quickPick(const char *pack,  const bool &bg)
{
	const Assets::AssetsPack &p = Assets::search_pack(pack, bg);

	for (int i = 0; i < __MAXTILE_SELECTOR_ && i < p.begin + p.range; i++)
	{
		_tile[i] = Tile(i + p.begin);
		_bg[i] = bg;
	}
}

/**
 * Takes the window, and retrieve the mouse position relative to the window and
 * its view. Then, it checks if the mouse is within the bounds of the selector.
 * If so, it will choose the tile that the mouse is hovering over.
 * 
 * @param	window: The window to check for mouse position.
 * 
 * @return	True if interaction has occurred, false otherwise.
 * */
bool TileSelector::interact(const sf::RenderWindow &win)
{
	// First Step: Get the mouse position relative to the window and its view.
	sf::Vector2i mouse = sf::Mouse::getPosition(win);
	sf::View view = win.getView();

	// Retrieve mouse position into the view.
	mouse.x = (mouse.x * view.getSize().x) / win.getSize().x + view.getCenter().x - (view.getSize().x / 2);
	mouse.y = (mouse.y * view.getSize().y) / win.getSize().y + view.getCenter().y - (view.getSize().y / 2);

	// Pre-calculate the corner of the selector.
	sf::Vector2f corner(
		view.getCenter().x - (TILE_WIDTH * SCALE_SELECTOR * __MAXTILE_SELECTOR_) / 2,
		view.getCenter().y + (view.getSize().y / 2) - (TILE_HEIGHT * SCALE_SELECTOR * 1.2f)
	);

	// Avoids checking if the mouse is outside of the whole selector.
	if (mouse.x < corner.x || mouse.x > corner.x + (TILE_WIDTH * SCALE_SELECTOR * __MAXTILE_SELECTOR_)
		|| mouse.y < corner.y || mouse.y > corner.y + (TILE_HEIGHT * SCALE_SELECTOR))
		return false;

	// Check if the mouse is within the bounds of any of the tiles.
	// If so, set the target to that tile.
	for (int i = 0; i < __MAXTILE_SELECTOR_; i++)
		if (mouse.x >= corner.x + (i * (TILE_WIDTH * SCALE_SELECTOR))
			&& mouse.x <= corner.x + ((i + 1) * (TILE_WIDTH * SCALE_SELECTOR))
			&& mouse.y >= corner.y
			&& mouse.y <= corner.y + (TILE_HEIGHT * SCALE_SELECTOR))
		{
			_target = i;
			return true;
		}

	return false;
}

/**
 * Defines the tile at the given index (if negative, goes from the end).
 * 
 * @param	index: The index of the tile to define.
 * @param	tile: The tile to define.
 * @param	bg: Whether the tile is a background tile.
 * */
void TileSelector::setTile(const int32_t &index, const Tile &tile, const bool &bg)
{
	_tile[index < 0 ? __MAXTILE_SELECTOR_ + index : index] = tile;
	_bg[index < 0 ? __MAXTILE_SELECTOR_ + index : index] = bg;
}

/**
 * Picks the tile at the given index (if negative, goes from the end).
 * Also returns the tile that was picked.
 * 
 * @param	index: The index of the tile to pick.
 * 
 * @return	The tile that was picked.
 * */
const Tile &TileSelector::pickTile(const int32_t &index)
{
	_target = index < 0 ? __MAXTILE_SELECTOR_ + index : index;
	return _tile[_target];
}

/**
 * Retrieves the tile at given index (if negative, goes from the end).
 * 
 * @param	index: The index of the tile to retrieve.
 * 
 * @return	The tile at the given index.
 * */
const Tile &TileSelector::getTile(const int32_t &index) const
	{ return _tile[index < 0 ? __MAXTILE_SELECTOR_ + index : index]; }

/**
 * Checks whether the tile at the given index is a background tile.
 * 
 * @param	index: The index of the tile to check.
 * 
 * @return	True if the tile is a background tile, false otherwise.
 * */
const bool &TileSelector::isBackground(const int &index) const
	{ return _bg[index < 0 ? __MAXTILE_SELECTOR_ + index : index]; }

/**
 * Shift the currently selected tile between foreground and background if available.
 * */
void TileSelector::shiftTile()
{
	if (Assets::has_inverse(_tile[_target].get_id()))
		_bg[_target] = !_bg[_target];
}

/**
 * Shift the target tile between foreground and background if available.
 * 
 * @param	index: The index of the tile to shift.
 * */
void TileSelector::shiftTile(const int32_t &index)
{
	int32_t i = index < 0 ? __MAXTILE_SELECTOR_ + index : index;
	if (Assets::has_inverse(_tile[i].get_id()))
		_bg[i] = !_bg[i];
}

/**
 * Shift all tiles between foreground and background if available.
 * */
void TileSelector::shiftAll()
{
	for (int i = 0; i < __MAXTILE_SELECTOR_; i++)
		if (Assets::has_inverse(_tile[i].get_id()))
			_bg[i] = !_bg[i];
}

/**
 * Draws the tile selector to the given target.
 * 
 * @param	target: The target to draw to.
 * @param	states: The states to draw with.
 * */
void TileSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// First Step: Anchor the selector to the bottom-middle of the screen.
	sf::View view = target.getView();
	states.transform *= sf::Transform().translate(
		view.getCenter().x - (TILE_WIDTH * SCALE_SELECTOR * __MAXTILE_SELECTOR_) / 2,
		view.getCenter().y + (view.getSize().y / 2) - (TILE_HEIGHT * SCALE_SELECTOR * 1.2f)
	);

	// Second Step: Apply texture and draw the vertices.
	for (int i = 0; i < __MAXTILE_SELECTOR_; i++)
	{
		states.texture = &Assets::get_texture(_tile[i].get_id(), _bg[i]);
		target.draw(_vertices[i], states);
	}

	// Third Step: Draw the target selector, move it to the target tile.
	states.texture = &Assets::get_texture(_TILEID_SELECTION, true);
	states.transform *= sf::Transform().translate((_target - __MAXTILE_SELECTOR_) * (TILE_WIDTH * SCALE_SELECTOR), 0);
	target.draw(_vertices[__MAXTILE_SELECTOR_], states);
}
