/* ************************************************************************** */
/*          .-.                                                               */
/*    __   /   \   __                                                         */
/*   (  `'.\   /.'`  )   EverybodyEdits2 - Selector.cpp                       */
/*    '-._.(;;;)._.-'                                                         */
/*    .-'  ,`"`,  '-.                                                         */
/*   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)             */
/*       //\   /         Last Updated: Monday, July 10, 2023 1:57 PM          */
/*      ||  '-'                                                               */
/* ************************************************************************** */

#include "game/Selector.hpp"
#include "utils/Settings.hpp"
#include "base/Assets.hpp"

Selector::Selector():
	Selector(Tile()) {}

Selector::Selector(const Tile::id_type &id):
	Selector(Tile(id)) {}

Selector::Selector(const Tile &tile):
	_vertices(sf::Quads, 4), _texture(nullptr), _tile(tile)
{
	_vertices[0].position = sf::Vector2f(0, 0);
	_vertices[1].position = sf::Vector2f(TILE_WIDTH * 2, 0);
	_vertices[2].position = sf::Vector2f(TILE_WIDTH * 2, TILE_HEIGHT * 2);
	_vertices[3].position = sf::Vector2f(0, TILE_HEIGHT * 2);

	Assets::size_type texSize = Assets::get_size();
	_vertices[0].texCoords = sf::Vector2f(0, 0);
	_vertices[1].texCoords = sf::Vector2f(texSize.x, 0);
	_vertices[2].texCoords = sf::Vector2f(texSize.x, texSize.y);
	_vertices[3].texCoords = sf::Vector2f(0, texSize.y);

	_texture = &Assets::get_texture(_tile.get_id());
}

Selector::~Selector() {}

Selector &Selector::operator=(const Selector &src)
{
	_tile = src._tile;
	_texture = src._texture;
	return *this;
}

Selector &Selector::operator=(const Tile &tile)
{
	_tile = tile;
	_texture = &Assets::get_texture(_tile.get_id());
	return *this;
}

void Selector::setTile(const Tile &tile)
	{ *this = tile; }

const Tile &Selector::getTile() const
	{ return _tile; }

void Selector::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// First Step: Anchor the selector to the upper-left corner of the view.
	sf::View view = target.getView();
	states.transform *= sf::Transform().translate(
		view.getCenter() - view.getSize() / 2.f
	);

	// Second Step: Apply texture and draw the vertices.
	states.texture = _texture;
	target.draw(_vertices, states);
}
