#ifndef PLAYING_FIELD_H
#define PLAYING_FIELD_H

#include "libraries.hpp"

#include "IGridInfo.hpp"

namespace kp
{
	class PlayingField
		: public IBase, public IGridInfo
	{
	private:
		void initGridSize();
		void initTile();
		void initTilePositions();
	protected:
		sf::RenderWindow* m_window;

		sf::RectangleShape* m_tile;
	public:
		PlayingField(sf::RenderWindow* window);

		virtual void setGridSize(sf::Vector2u gridSize);
		virtual void setTilePositions(kp::tilePositions_t tilePositions);

		virtual sf::Vector2u getGridSize() const;
		virtual kp::tilePositions_t getTilePositions() const;
		sf::Vector2f getTileSize() const;

		virtual void update(float dT);
		virtual void render();

		~PlayingField();
	};
}

#endif // !PLAYING_FIELD_H