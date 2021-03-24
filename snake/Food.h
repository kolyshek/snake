#ifndef FOOD_H
#define FOOD_H

#include "libraries.h"
#include "PlayingField.h"

class Snake;

class Food
{
private:
	sf::RenderWindow& m_window;

	sf::CircleShape m_food;

	void render();
public:
	Food(sf::RenderWindow& window);

	void init();

	void setRandomPosition(const PlayingField& playingfield, Snake& snake);

	float getRadius() const;
	sf::Vector2f getPosition() const;

	void update();
};

#endif // !FOOD_H