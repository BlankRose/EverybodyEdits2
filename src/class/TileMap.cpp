/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - TileMap.cpp                 */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Mar 31 17:38:16 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/TileMap.hpp"

TileMap::TileMap(const size_type &tile_size, const size_type &width, const size_type &height):
	_tile_size(tile_size), _width(width), _height(height)
{
	_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	_vertices.resize((size_t) width * (size_t) height * 4);

	for (size_type x = 0; x < width; x++)
	{
		for (size_type y = 0; y < height; y++)
		{
			sf::Vertex	*quad = &_vertices[(x + y * width) * 4];

			quad[0].position = sf::Vector2f(x * tile_size, y * tile_size);				// Upper Left
			quad[1].position = sf::Vector2f((x + 1) * tile_size, y * tile_size);		// Upper Right
			quad[2].position = sf::Vector2f((x + 1) * tile_size, (y + 1) * tile_size);	// Lower Right
			quad[3].position = sf::Vector2f(x * tile_size, (y + 1) * tile_size);		// Lower Left

			Assets::rect_type coords = Assets::get_tile_coords(0, 0);

			quad[0].texCoords = sf::Vector2f(coords.x.x, coords.x.y);
			quad[1].texCoords = sf::Vector2f(coords.y.x, coords.x.y);
			quad[2].texCoords = sf::Vector2f(coords.y.x, coords.y.y);
			quad[3].texCoords = sf::Vector2f(coords.x.x, coords.y.y);
		}
	}
}

TileMap::~TileMap() {}

void		TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &Assets::get_tilemap();

	target.draw(_vertices, states);
}