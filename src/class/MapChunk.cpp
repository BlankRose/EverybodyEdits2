/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - MapChunk.cpp                */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Mar 31 18:24:01 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/MapChunk.hpp"
#include <limits>

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using size_type = MapChunk::size_type;

const size_type		MapChunk::WIDTH = 255;
const size_type		MapChunk::HEIGHT = 255;
size_type			MapChunk::_tile_size = 50;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

MapChunk::MapChunk()
{
	_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	_vertices.resize(WIDTH * HEIGHT * 4);

	for (size_type x = 0; x < WIDTH; x++)
	{
		for (size_type y = 0; y < HEIGHT; y++)
		{
			sf::Vertex	*quad = &_vertices[(x + y * WIDTH) * 4];

			quad[0].position = sf::Vector2f(x * _tile_size, y * _tile_size);				// Upper Left
			quad[1].position = sf::Vector2f((x + 1) * _tile_size, y * _tile_size);			// Upper Right
			quad[2].position = sf::Vector2f((x + 1) * _tile_size, (y + 1) * _tile_size);	// Lower Right
			quad[3].position = sf::Vector2f(x * _tile_size, (y + 1) * _tile_size);			// Lower Left

			Assets::rect_type coords = Assets::get_tile_coords(0, 0);

			quad[0].texCoords = sf::Vector2f(coords.x.x, coords.x.y);
			quad[1].texCoords = sf::Vector2f(coords.y.x, coords.x.y);
			quad[2].texCoords = sf::Vector2f(coords.y.x, coords.y.y);
			quad[3].texCoords = sf::Vector2f(coords.x.x, coords.y.y);
		}
	}
}

MapChunk::~MapChunk() {}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

void				MapChunk::set_tilesize(const size_type &size) /* STATIC */ 
	{ _tile_size = size; }

size_type			&MapChunk::get_tilesize() /* STATIC */
	{ return _tile_size; }

sf::Vertex			&MapChunk::get_tilevertex(const size_type &x, const size_type &y)
	{ return _vertices[(x + y * WIDTH) * 4]; }

const sf::Vertex	&MapChunk::get_tilevertex(const size_type &x, const size_type &y) const
	{ return _vertices[(x + y * WIDTH) * 4]; }

void				MapChunk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &Assets::get_tilemap();

	target.draw(_vertices, states);
}