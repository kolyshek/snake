#ifndef SNAKE_H
#define SNAKE_H

#include "libraries.hpp"

#include "IGridInfo.hpp"
#include "ITileInfo.hpp"

namespace kp
{
	class Food;
	class PlayingField;

	class Snake
		: public IBase, public IGridInfo, public ITileInfo
	{
	private:
		void initOfBaseTypes();
		void initHead();
		void initBodyPart();
		void initBodyPartsIndex();
		void initSupportedKeys();
	protected:
		sf::RenderWindow* m_window;

		sf::RectangleShape* m_head;
		sf::RectangleShape* m_bodyPart;

		std::vector<sf::Vector2u*> m_BodyPartsIndex;

		int16_t m_score;

		float m_dT;
		float m_delay;

		std::map<std::string, sf::Keyboard::Key> m_supportedKeys;
		sf::Keyboard::Key m_direction;

		void chooseDirection();
		void moveHead();
		void moveBodyParts();

		void addBodyPartIndex();
	public:
		Snake(sf::RenderWindow* window);

		virtual void setTileSize(sf::Vector2f tileSize);
		virtual void setTileIndex(sf::Vector2u tileIndex);
		virtual void setGridSize(sf::Vector2u gridSize);
		virtual void setTilePositions(kp::tilePositions_t tilePositions);

		virtual sf::Vector2f getTileSize() const;
		virtual sf::Vector2u getTileIndex() const;
		virtual sf::Vector2u getGridSize() const;
		virtual kp::tilePositions_t getTilePositions() const;
		int16_t getScore() const;

		bool isEating(sf::Vector2u foodIndex);
		bool isDead();
		bool isCollideWithMyself();

		virtual void chooseRandomIndex();
		void restart();

		virtual void update(float dT);
		virtual void render();

		~Snake();
	};
}

#endif // !SNAKE_H