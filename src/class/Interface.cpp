/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Interface.cpp               */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Fri Apr  7 17:51:44 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#include "class/Interface.hpp"
#include "class/MapChunk.hpp"
#include "class/Framework.hpp"

	/** ---------------------- **/
	/*        ATTRIBUTES        */
	/** ---------------------- **/

using vertex_type = Interface::vertex_type;
using texture_type = Interface::texture_type;

	/** ---------------------- **/
	/*       CONSTRUCTORS       */
	/** ---------------------- **/

Interface::Interface()
{
	_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	_vertices.resize(4);

	MapChunk::size_type		size = MapChunk::get_tilesize() * 2;
	sf::Vertex				*quad = &_vertices[0];

	quad[0].position = sf::Vector2f(0, 0);			// Upper Left
	quad[1].position = sf::Vector2f(size, 0);		// Upper Right
	quad[2].position = sf::Vector2f(size, size);	// Lower Right
	quad[3].position = sf::Vector2f(0, size);		// Lower Left

	_selected = Tile(MapChunk::position_type(0, 0), quad, 1, Assets::BASIC);
}

Interface::~Interface() {}

	/** ---------------------- **/
	/*          METHODS         */
	/** ---------------------- **/

const Tile	&Interface::get_selected() const
	{ return _selected; }

void		Interface::set_selected(const Tile &tile)
{
	sf::Vertex	*tquad = tile.get_vertex();

	for (uint8_t i = 0; i < 4; i++)
		_vertices[i].texCoords = tquad[i].texCoords;
	_selected = tile;
}

void		Interface::set_selected(const id_type &id, const group_type &group)
{
	_selected.set_id(id, group);
	set_selected(_selected);
}

void		Interface::render(Framework *&fw)
{
	sf::Vector2f	pos = fw->get_view().getCenter();
	sf::Vector2f	size = fw->get_view().getSize();

	this->setPosition(pos.x - size.x / 2, pos.y - size.y / 2);
	fw->get_window().draw(*this);
}

void		Interface::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &Assets::get_tilemap();

	target.draw(_vertices, states);
}
