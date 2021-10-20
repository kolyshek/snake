#ifndef FOOD_H
#define FOOD_H

#include "libraries.hpp"

#include "IGridInfo.hpp"
#include "ITileInfo.hpp"

namespace kp
{
	class PlayingField;

	class Food
		: public IBase, public IGridInfo, public ITileInfo
	{
	private:
		void initFood();
	protected:
		sf::RenderWindow* m_window;
		sf::RectangleShape* m_foodPart;

		float m_dT;

		void pulsationSize();
	public:
		Food(sf::RenderWindow* window);

		virtual void setTileSize(sf::Vector2f tileSize);
		virtual void setTileIndex(sf::Vector2u tileIndex);
		virtual void setGridSize(sf::Vector2u gridSize);
		virtual void setTilePositions(kp::tilePositions_t tilePositions);

		virtual sf::Vector2f getTileSize() const;
		virtual sf::Vector2u getTileIndex() const;
		virtual sf::Vector2u getGridSize() const;
		virtual kp::tilePositions_t getTilePositions() const;

		virtual void chooseRandomIndex();

		virtual void update(float dT);
		virtual void render();

		~Food();
	};
}

#endif // !FOOD_H