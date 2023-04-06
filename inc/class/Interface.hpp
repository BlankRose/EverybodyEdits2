/* ********************************************************************* */
/*          .-.                                                          */
/*    __   /   \   __                                                    */
/*   (  `'.\   /.'`  )   Everybody Edits 2 - Interface.hpp               */
/*    '-._.(;;;)._.-'                                                    */
/*    .-'  ,`"`,  '-.                                                    */
/*   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        */
/*       //\   /         Last Updated: Thu Apr  6 14:24:36 CEST 2023     */
/*      ||  '-'                                                          */
/* ********************************************************************* */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Tiles.hpp"
class Framework;

class Interface:
	public sf::Drawable,
	public sf::Transformable
{
	public:

			/** ---------------------- **/
			/*     TYPE DEFINITIONS     */
			/** ---------------------- **/

		using Tile = Tile;
		using id_type = Tile::id_type;
		using group_type = Tile::group_type;

		typedef sf::VertexArray		vertex_type;
		typedef sf::Texture			texture_type;
		typedef std::vector<Tile>	tiles_type;

			/** ---------------------- **/
			/*       CONSTRUCTORS       */
			/** ---------------------- **/

		Interface();
		~Interface();

			/** ---------------------- **/
			/*          METHODS         */
			/** ---------------------- **/

		const Tile			&get_selected() const;
		void				set_selected(const Tile &tile);
		void				set_selected(const id_type &id, const group_type &group);
		void				render(Framework *&fw);

	private:

		virtual void		draw(sf::RenderTarget &target, sf::RenderStates states) const;

			/** ---------------------- **/
			/*        ATTRIBUTES        */
			/** ---------------------- **/

		vertex_type			_vertices;
		Tile				_selected;
};

#endif /* PLAYER_HPP */